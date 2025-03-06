/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:03:00 by okraus            #+#    #+#             */
/*   Updated: 2025/03/06 19:03:33 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <stdlib.h> //for free

#if LIB == 1
    #include "SDL.h"

    int game(void)
    {
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

// Define ESC key based on the OS
#ifdef __APPLE__
    #define ESC_KEY 53
#else
    #define ESC_KEY 65307
#endif


// Close window function
int close_window(void *param)
{
    void **mlx_win = (void **)param; // Unwrap mlx and win

    if (mlx_win[0] && mlx_win[1]) // Ensure pointers are valid
    {
        mlx_destroy_window(mlx_win[0], mlx_win[1]);
    }

    mlx_loop_end(mlx_win[0]); // Explicitly end the mlx_loop
    return 0; // Return 0 to indicate the handler has finished
}

// Key press event handler
int key_press(int keycode, void *param)
{
    void **mlx_win = (void **)param; // Unwrap mlx and win

    if (keycode == ESC_KEY)
    {
        close_window(mlx_win); // Close the window and stop the loop
        return 0; // Return 0 since close_window() will already end the loop
    }
    return 0;
}

// Main game loop
int game(void)
{
    void *mlx = mlx_init();
    if (!mlx)
    {
        put_error("MiniLibX initialization failed.\n");
        return 1;
    }

    void *win = mlx_new_window(mlx, 800, 600, "MiniLibX Window");
    if (!win)
    {
        put_error("Failed to create MiniLibX window.\n");
        return 1;
    }

    // Create an array to store mlx and win pointers to pass in key press handler
    void *mlx_win[2] = {mlx, win};

    // Register key press event
    mlx_key_hook(win, key_press, mlx_win);

    // Register close window function for the "X" button on the window
    mlx_hook(win, 17, 0, close_window, mlx_win);

    // Enter the main event loop
    mlx_loop(mlx); // This will run until mlx_loop_end() is called
    mlx_destroy_display(mlx); // Clean up any resources related to the display
    free(mlx);
    return 0; // This will never be reached unless the loop ends
}


#else
    #error "LIB must be defined as either 0 (MiniLibX) or 1 (SDL)"
#endif