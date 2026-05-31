#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

// Window and grid constants
const int WIDTH = 640;
const int HEIGHT = 640;
const int ROWS = 5;
const int COLS = 5;
const int CELL_SIZE = 128;

void draw_grid();

int main()
{
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;

    bool done = false;

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

    // Initialize primitive drawing
    al_init_primitives_addon();

    // Create and register the event queue
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));

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
    }

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