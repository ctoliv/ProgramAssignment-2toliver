#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include "logic.h"


// Window and grid constants
const int WIDTH = 640;
const int HEIGHT = 640;
const int ROWS = 5;
const int COLS = 5;
const int CELL_SIZE = 128;

void draw_grid();
void draw_cards(GameLogic& gameLogic);
void draw_shape(int shape, int centerX, int centerY);
void draw_status(GameLogic& gameLogic, ALLEGRO_FONT* font);

int main()
{
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_FONT* font = NULL;
    ALLEGRO_TIMER* timer = NULL;

    bool done = false;

    GameLogic gameLogic;

    // Used to wait 5 seconds before hiding non-matching cards
    bool waitingToHide = false;
    double hideStartTime = 0;

    // Initialize Allegro
    if (!al_init())
    {
        fprintf(stderr, "Failed to initialize Allegro.\n");
        return -1;
    }

    // Create the game window
    display = al_create_display(WIDTH, HEIGHT);

    if (!display)
    {
        fprintf(stderr, "Failed to create display.\n");
        return -1;
    }

    // Mouse input 
    al_install_mouse();

    // Initialize primitives
    al_init_primitives_addon();
    al_init_font_addon();

    font = al_create_builtin_font();

    // Create and register the event queue
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60.0);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_start_timer(timer);
    // Draw the starting grid
    al_clear_to_color(al_map_rgb(0, 0, 0));
    draw_grid();
    al_flip_display();

    while (!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        // Close the program if the window is closed
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            // Convert mouse position into board position
            int col = ev.mouse.x / CELL_SIZE;
            int row = ev.mouse.y / CELL_SIZE;

            if (gameLogic.selectCard(row, col))
            {
                // Start the 5-second timer if the selected pair does not match
                if (gameLogic.hasPendingNonMatch())
                {
                    waitingToHide = true;
                    hideStartTime = al_get_time();
                }
            }
        }

        else if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            // Timer event keeps the game updating even when the mouse is not moving
        }
        // Hide non-matching cards after 5 seconds
        if (waitingToHide && al_get_time() - hideStartTime >= 5.0)
        {
            gameLogic.hideNonMatch();
            waitingToHide = false;
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));
        draw_grid();
        draw_cards(gameLogic);
        draw_status(gameLogic, font);
        al_flip_display();
    }
    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);

    return 0;
}

// Draws the 5x5 board grid
void draw_grid()
{
    for (int i = 0; i <= ROWS; i++)
    {
        al_draw_line(0, i * CELL_SIZE, WIDTH, i * CELL_SIZE,
            al_map_rgb(255, 255, 255), 2);
    }

    for (int i = 0; i <= COLS; i++)
    {
        al_draw_line(i * CELL_SIZE, 0, i * CELL_SIZE, HEIGHT,
            al_map_rgb(255, 255, 255), 2);
    }
}

// Draws all currently revealed or matched cards
void draw_cards(GameLogic& gameLogic)
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (row == 4 && col == 4)
            {
                continue;
            }

            int left = col * CELL_SIZE;
            int top = row * CELL_SIZE;
            int centerX = left + CELL_SIZE / 2;
            int centerY = top + CELL_SIZE / 2;

            // Only matched cards get the red X
            if (gameLogic.isMatched(row, col))
            {
                al_draw_line(left + 10, top + 10,
                    left + CELL_SIZE - 10, top + CELL_SIZE - 10,
                    al_map_rgb(255, 0, 0), 4);

                al_draw_line(left + CELL_SIZE - 10, top + 10,
                    left + 10, top + CELL_SIZE - 10,
                    al_map_rgb(255, 0, 0), 4);
            }
            // Revealed but not matched cards should show the shape
            else if (gameLogic.isRevealed(row, col))
            {
                int shape = gameLogic.getShape(row, col);
                draw_shape(shape, centerX, centerY);
            }
        }
    }
}

void draw_status(GameLogic& gameLogic, ALLEGRO_FONT* font)
{
    int left = 4 * CELL_SIZE;
    int top = 4 * CELL_SIZE;

    // Status box uses the bottom-right square
    al_draw_filled_rectangle(left, top, WIDTH, HEIGHT,
        al_map_rgb(40, 80, 40));

    // Display matched pairs
    al_draw_textf(font, al_map_rgb(255, 255, 255),
        left + 10, top + 30, 0,
        "Matched: %d", gameLogic.getMatchedPairs());

    // Display remaining pairs
    al_draw_textf(font, al_map_rgb(255, 255, 255),
        left + 10, top + 60, 0,
        "Left: %d", gameLogic.getRemainingPairs());
    if (gameLogic.isGameOver())
    {
        al_draw_text(font, al_map_rgb(255, 255, 0),
            left + 10, top + 90, 0,
            "You win!");
    }
}

// Draws a primitive shape based on the hidden shape ID
void draw_shape(int shape, int centerX, int centerY)
{
    if (shape == 1)
    {
        // Red circle
        al_draw_filled_circle(centerX, centerY, 30, al_map_rgb(255, 0, 0));
    }
    else if (shape == 2)
    {
        // Blue circle
        al_draw_filled_circle(centerX, centerY, 30, al_map_rgb(0, 120, 255));
    }
    else if (shape == 3)
    {
        // Green square
        al_draw_filled_rectangle(centerX - 30, centerY - 30,
            centerX + 30, centerY + 30, al_map_rgb(0, 255, 0));
    }
    else if (shape == 4)
    {
        // Purple square
        al_draw_filled_rectangle(centerX - 30, centerY - 30,
            centerX + 30, centerY + 30, al_map_rgb(150, 0, 255));
    }
    else if (shape == 5)
    {
        // Yellow triangle
        al_draw_filled_triangle(centerX, centerY - 35,
            centerX - 35, centerY + 30,
            centerX + 35, centerY + 30,
            al_map_rgb(255, 255, 0));
    }
    else if (shape == 6)
    {
        // Orange triangle
        al_draw_filled_triangle(centerX, centerY - 35,
            centerX - 35, centerY + 30,
            centerX + 35, centerY + 30,
            al_map_rgb(255, 120, 0));
    }
    else if (shape == 7)
    {
        // Cyan oval
        al_draw_filled_ellipse(centerX, centerY, 35, 25,
            al_map_rgb(0, 255, 255));
    }
    else if (shape == 8)
    {
        // Pink oval
        al_draw_filled_ellipse(centerX, centerY, 35, 25,
            al_map_rgb(255, 0, 180));
    }
    else if (shape == 9)
    {
        // White diamond
        al_draw_filled_triangle(centerX, centerY - 35,
            centerX - 35, centerY,
            centerX, centerY + 35,
            al_map_rgb(255, 255, 255));

        al_draw_filled_triangle(centerX, centerY - 35,
            centerX + 35, centerY,
            centerX, centerY + 35,
            al_map_rgb(255, 255, 255));
    }
    else if (shape == 10)
    {
        // Gray diamond
        al_draw_filled_triangle(centerX, centerY - 35,
            centerX - 35, centerY,
            centerX, centerY + 35,
            al_map_rgb(150, 150, 150));

        al_draw_filled_triangle(centerX, centerY - 35,
            centerX + 35, centerY,
            centerX, centerY + 35,
            al_map_rgb(150, 150, 150));
    }
    else if (shape == 11)
    {
        // Red outlined circle
        al_draw_circle(centerX, centerY, 35, al_map_rgb(255, 0, 0), 5);
        al_draw_filled_circle(centerX, centerY, 12, al_map_rgb(255, 0, 0));
    }
    else if (shape == 12)
    {
        // Blue outlined circle
        al_draw_circle(centerX, centerY, 35, al_map_rgb(0, 120, 255), 5);
        al_draw_filled_circle(centerX, centerY, 12, al_map_rgb(0, 120, 255));
    }
}