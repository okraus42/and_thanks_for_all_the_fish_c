/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:03:00 by okraus            #+#    #+#             */
/*   Updated: 2025/03/09 17:32:54 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> //for free
#include "defines.h"
#include "game.h"

#if LIB == 1
    #include "SDL.h"

    int game(t_game *g)
    {
        (void)g;
        put_str("Game SDL test\n");
    
        // Initialize SDL Video subsystem
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            put_error("Game SDL is missing\n");
            return 1;
        }
    
        // Create SDL Window
        SDL_Window *window = SDL_CreateWindow("SDL Window",
                                              SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              800, 600,
                                              SDL_WINDOW_SHOWN);
        if (!window)
        {
            put_error("Failed to create SDL window\n");
            SDL_Quit();  // Ensure global SDL cleanup
            return 1;
        }
    
        SDL_Event event;
        int running = 1;
        while (running)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                    running = 0;
                else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                    running = 0;
            }
        }
    
        // Cleanup resources
        SDL_DestroyWindow(window);  // Clean up the window
        // Quit SDL subsystems and then SDL itself
        SDL_Quit();
    
        return 0;
    }

#elif LIB == 0

#include "mlx.h"
#include <stdlib.h>


// Define key codes
#ifdef __APPLE__
    #define ESC_KEY 53
    #define LEFT_KEY 123
    #define RIGHT_KEY 124
    #define UP_KEY 126
    #define DOWN_KEY 125
#else
    #define ESC_KEY 65307
    #define LEFT_KEY 65361
    #define RIGHT_KEY 65363
    #define UP_KEY 65362
    #define DOWN_KEY 65364
#endif

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define SQUARE_SIZE 50
#define MOVE_SPEED 1


// Function to draw a blue square
void draw_square(t_game *g)
{
    int i, j;
    int color = 0x0000FF; // Blue color

    for (i = g->x; i < g->x + SQUARE_SIZE; i++)
    {
        for (j = g->y; j < g->y + SQUARE_SIZE; j++)
        {
            mlx_pixel_put(g->mlx, g->win, i, j, color);
        }
    }
}

// Function to clear the screen
void clear_screen(t_game *g)
{
    mlx_clear_window(g->mlx, g->win);
}

// Close window function
int close_window_esc(void *param)
{
    t_game *g = (t_game *)param;

    if (g->mlx && g->win) // Ensure pointers are valid
    {
        mlx_destroy_window(g->mlx, g->win);
        g->win = NULL;  // Mark the window as destroyed
    }

    mlx_loop_end(g->mlx); // Explicitly end the mlx_loop
    return 0; // Return 0 to indicate the handler has finished
}

int close_window_x(void *param)
{
    t_game *g = (t_game *)param;

    // if (g->mlx && g->win) // Ensure pointers are valid
    // {
    //     mlx_destroy_window(g->mlx, g->win);
    //     g->win = NULL;  // Mark the window as destroyed
    // }
    mlx_loop_end(g->mlx); // Explicitly end the mlx_loop
    return 0; // Return 0 to indicate the handler has finished
}

// Key press event handler (set key state)
int key_press(int keycode, void *param)
{
    t_game *g = (t_game *)param;

    if (keycode == ESC_KEY)
    {
        close_window_esc(g); // Close the window
        return (0);
    }

    if (keycode >= 0 && keycode < 65536)
        g->keys[keycode] = true; // Mark key as pressed

    return (0);
}

// Key release event handler (unset key state)
int key_release(int keycode, void *param)
{
    t_game *g = (t_game *)param;

    if (keycode >= 0 && keycode < 65536)
        g->keys[keycode] = false; // Mark key as released

    return (0);
}


// Update function for continuous movement
int update_game(void *param)
{
    t_game *g = (t_game *)param;
    bool moved = false;
    if (g->keys[LEFT_KEY] && g->x > 0)
    {
        g->x -= MOVE_SPEED;
        moved = true;
    }
    if (g->keys[RIGHT_KEY] && g->x < WIN_WIDTH - SQUARE_SIZE)
    {
        g->x += MOVE_SPEED;
        moved = true;
    }
    if (g->keys[UP_KEY] && g->y > 0)
    {
        g->y -= MOVE_SPEED;
        moved = true;
    }
    if (g->keys[DOWN_KEY] && g->y < WIN_HEIGHT - SQUARE_SIZE)
    {
        g->y += MOVE_SPEED;
        moved = true;
    }
    if (moved)
    {
        clear_screen(g);
        draw_square(g);
    }
    return (0);
}

// Main game loop
int game(t_game *g)
{
    g->mlx = mlx_init();
    if (!g->mlx)
    {
        put_error("MiniLibX initialization failed.\n");
        return 1;
    }

    g->win = mlx_new_window(g->mlx, WIN_WIDTH, WIN_HEIGHT, "Move the Square");
    if (!g->win)
    {
        put_error("Failed to create MiniLibX window.\n");
        return 1;
    }

    // Create an array to store mlx and win pointers to pass in key press handler
    g->x = WIN_WIDTH / 2 - SQUARE_SIZE / 2;
    g->y = WIN_HEIGHT / 2 - SQUARE_SIZE / 2;
    
    draw_square(g);

    mlx_hook(g->win, 2, 1L << 0, key_press, g);   // Handle key press
    mlx_hook(g->win, 3, 1L << 1, key_release, g); // Handle key release
    mlx_hook(g->win, 17, 0, close_window_x, g);     // Handle window close event
    mlx_loop_hook(g->mlx, update_game, g);        // Continuous movement check

    // Enter the main event loop
    mlx_loop(g->mlx); // This will run until mlx_loop_end() is called
    if (g->mlx && g->win) // Ensure pointers are valid
    {
        mlx_destroy_window(g->mlx, g->win);
        g->win = NULL;  // Mark the window as destroyed
    }
    mlx_destroy_display(g->mlx); // Clean up any resources related to the display
    free(g->mlx);
    g->mlx = NULL;
    return 0; // This will never be reached unless the loop ends
}


#else
    #error "LIB must be defined as either 0 (MiniLibX) or 1 (SDL)"
#endif