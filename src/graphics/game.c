/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:03:00 by okraus            #+#    #+#             */
/*   Updated: 2025/03/23 16:02:09 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "defines.h"
#include <stdio.h>	//for debug
#include <stdlib.h> //for free
#include <X11/Xlib.h>  // Needed for X11 functions

#if LIB == 1
# include "SDL.h"

int game(t_game* g)
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
	SDL_Window* window =
		SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED,
						 SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	if (!window)
	{
		put_error("Failed to create SDL window\n");
		SDL_Quit(); // Ensure global SDL cleanup
		return 1;
	}

	SDL_Event event;
	int		  running = 1;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = 0;
			else if (event.type == SDL_KEYDOWN &&
					 event.key.keysym.sym == SDLK_ESCAPE)
				running = 0;
		}
	}

	// Cleanup resources
	SDL_DestroyWindow(window); // Clean up the window
	// Quit SDL subsystems and then SDL itself
	SDL_Quit();

	return 0;
}

#elif LIB == 0

# include "mlx.h"
# include <stdlib.h>

// Function to draw a blue square
void draw_square(t_game* g)
{
	int y, x;

	for (y = g->y; y < g->y + SQUARE_SIZE; y++)
	{
		for (x = g->x; x < g->x + SQUARE_SIZE; x++)
		{
			// mlx_pixel_put(g->mlx, g->win, i, j, color);
			g->screen.data[y * WIN_WIDTH + x] = CLR_BLUE;
		}
	}
}

// Function to copy the screen
void copy_screen(t_game* g)
{
	//possibly optimise with uint64_t
	uint32_t	x;
	uint32_t	y;
	uint32_t	*data;
	int bpp, size_line, endian;

	y = 0;
	data = (uint32_t *)mlx_get_data_addr(g->img, &bpp, &size_line, &endian);
	(void)bpp;
	(void)size_line;
	(void)endian;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			data[y * WIN_WIDTH + x] = g->screen.data[y * WIN_WIDTH + x];
			x++;
		}
		y++;
	}
}

// Function to clear the screen
void clear_screen(t_game* g)
{
	//possibly optimise with uint64_t
	uint32_t	x;
	uint32_t	y;
	int bpp, size_line, endian;

	y = 0;
	(void)bpp;
	(void)size_line;
	(void)endian;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			g->screen.data[y * WIN_WIDTH + x] = CLR_BLACK;
			// g->screen.data[y * WIN_WIDTH + x] = CLR_GRAY_5;
			x++;
		}
		y++;
	}
	// mlx_clear_window(g->mlx, g->win);
}

// Close window function

int close_window(void* param)
{
	t_game* g = (t_game*)param;
	mlx_loop_end(g->mlx); // Explicitly end the mlx_loop
	return 0;			  // Return 0 to indicate the handler has finished
}

// Key press event handler (set key state)
int key_press(int keycode, void* param)
{
	t_game* g = (t_game*)param;

	if (keycode == KEY_ESC)
	{
		close_window(g); // Close the window
		return (0);
	}
	else
	{
		printf("key %i\n", keycode);
	}

	if (keycode >= 0 && keycode < 65536)
		g->keys[keycode] = true; // Mark key as pressed

	return (0);
}

// Key release event handler (unset key state)
int key_release(int keycode, void* param)
{
	t_game* g = (t_game*)param;

	if (keycode >= 0 && keycode < 65536)
		g->keys[keycode] = false; // Mark key as released

	return (0);
}

# define IMG_PATH "assets/img/test2.xpm"

// Update function for continuous movement
int update_game(void* param)
{
	t_game* g = (t_game*)param;
	bool	moved = false;
	if (g->keys[KEY_LEFT] && g->x > 0)
	{
		g->x -= MOVE_SPEED;
		moved = true;
	}
	if (g->keys[KEY_RIGHT] && g->x < WIN_WIDTH - SQUARE_SIZE)
	{
		g->x += MOVE_SPEED;
		moved = true;
	}
	if (g->keys[KEY_UP] && g->y > 0)
	{
		g->y -= MOVE_SPEED;
		moved = true;
	}
	if (g->keys[KEY_DOWN] && g->y < WIN_HEIGHT - SQUARE_SIZE)
	{
		g->y += MOVE_SPEED;
		moved = true;
	}
	// printf("hi\n");
	if (moved)
	{
		clear_screen(g);
		draw_square(g);
		copy_screen(g);
		// mlx_put_image_to_window(g->mlx, g->win, g->image.img, 100, 100);
		mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	}
	return (0);
}

//crop iamge function

// Main game loop
int game(t_game* g)
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

	// Create an array to store mlx and win pointers to pass in key press handler....
	g->x = WIN_WIDTH / 2 - SQUARE_SIZE / 2;
	g->y = WIN_HEIGHT / 2 - SQUARE_SIZE / 2;

	g->image.img =
		mlx_xpm_file_to_image(g->mlx, IMG_PATH, &g->image.width, &g->image.height);
	if (!g->image.img)
	{
		put_error("Failed to load sprite sheet\n");
		return (1);
	}

	g->img = mlx_new_image(g->mlx, WIN_WIDTH, WIN_HEIGHT);
	draw_square(g);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);	  // Handle key press
	mlx_hook(g->win, 3, 1L << 1, key_release, g); // Handle key release
	mlx_hook(g->win, 17, 0, close_window, g);	  // Handle window close event
	mlx_expose_hook(g->win, update_game, g);
	mlx_loop_hook(g->mlx, update_game, g);		  // Continuous movement check

	// Enter the main event loop
	mlx_loop(g->mlx);		  // This will run until mlx_loop_end() is called
	if (g->mlx && g->image.img && g->img) // Ensure pointers are valid
	{
		mlx_destroy_image(g->mlx, g->image.img);
		g->image.img = NULL; // Mark the image as destroyed
		mlx_destroy_image(g->mlx, g->img);
		g->img = NULL; // Mark the image as destroyed
	}
	if (g->mlx && g->win) // Ensure pointers are valid
	{
		mlx_destroy_window(g->mlx, g->win);
		g->win = NULL; // Mark the window as destroyed
	}
	mlx_destroy_display(
		g->mlx); // Clean up any resources related to the display
	free(g->mlx);
	g->mlx = NULL;
	return 0; // This will never be reached unless the loop ends
}

#else
# error "LIB must be defined as either 0 (MiniLibX) or 1 (SDL)"
#endif