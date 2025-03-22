/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:03:00 by okraus            #+#    #+#             */
/*   Updated: 2025/03/22 15:44:49 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "defines.h"
#include <stdio.h>	//for debug
#include <stdlib.h> //for free

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

// Define key codes
# ifdef __APPLE__
#  define ESC_KEY	53
#  define LEFT_KEY	123
#  define RIGHT_KEY 124
#  define UP_KEY	126
#  define DOWN_KEY	125
# else
#  define KEY_F1		   65470
#  define KEY_F2		   65471
#  define KEY_F3		   65472
#  define KEY_F4		   65473
#  define KEY_F5		   65474
#  define KEY_F6		   65475
#  define KEY_F7		   65476
#  define KEY_F8		   65477
#  define KEY_F9		   65478
#  define KEY_F10		   65479
#  define KEY_F11		   65480
#  define KEY_F12		   65481
#  define KEY_A			   97
#  define KEY_B			   98
#  define KEY_C			   99
#  define KEY_D			   100
#  define KEY_E			   101
#  define KEY_F			   102
#  define KEY_G			   103
#  define KEY_H			   104
#  define KEY_I			   105
#  define KEY_J			   106
#  define KEY_K			   107
#  define KEY_L			   108
#  define KEY_M			   109
#  define KEY_N			   110
#  define KEY_O			   111
#  define KEY_P			   112
#  define KEY_Q			   113
#  define KEY_R			   114
#  define KEY_S			   115
#  define KEY_T			   116
#  define KEY_U			   117
#  define KEY_V			   118
#  define KEY_W			   119
#  define KEY_X			   120
#  define KEY_Y			   121
#  define KEY_Z			   122
#  define KEY_0			   48
#  define KEY_1			   49
#  define KEY_2			   50
#  define KEY_3			   51
#  define KEY_4			   52
#  define KEY_5			   53
#  define KEY_6			   54
#  define KEY_7			   55
#  define KEY_8			   56
#  define KEY_9			   57
#  define KEY_UP		   65362
#  define KEY_DOWN		   65364
#  define KEY_LEFT		   65361
#  define KEY_RIGHT		   65363
#  define KEY_ESC		   65307 // Escape
#  define KEY_TAB		   65289 // Tab
#  define KEY_CAPSLOCK	   65509 // Caps Lock
#  define KEY_SHIFT_L	   65505 // Left Shift
#  define KEY_SHIFT_R	   65506 // Right Shift
#  define KEY_CTRL_L	   65507 // Left Ctrl
#  define KEY_CTRL_R	   65508 // Right Ctrl
#  define KEY_ALT_L		   65513 // Left Alt (Option)
#  define KEY_ALT_R		   65514 // Right Alt (Option)
#  define KEY_SUPER_L	   65515 // Left Super (Windows key / Command key)
#  define KEY_SUPER_R	   65516 // Right Super (Windows key / Command key)
#  define KEY_RIGHT_CLICK  65383 // Right Super (Windows key / Command key)
#  define KEY_SPACE		   32	 // Spacebar
#  define KEY_BACKSPACE	   65288 // Backspace
#  define KEY_ENTER		   65293 // Enter/Return
#  define KEY_DELETE	   65535 // Delete
#  define KEY_INSERT	   65379 // Insert
#  define KEY_HOME		   65360 // Home
#  define KEY_END		   65367 // End
#  define KEY_PAGEUP	   65365 // Page Up
#  define KEY_PAGEDOWN	   65366 // Page Down
#  define KEY_PRINTSCREEN  65377 // Print Screen
#  define KEY_SCROLLLOCK   65300 // Scroll Lock
#  define KEY_PAUSE		   65299 // Pause/Break
#  define KEY_NUM_0		   65438
#  define KEY_NUM_1		   65436
#  define KEY_NUM_2		   65433
#  define KEY_NUM_3		   65435
#  define KEY_NUM_4		   65430
#  define KEY_NUM_5		   65437
#  define KEY_NUM_6		   65432
#  define KEY_NUM_7		   65429
#  define KEY_NUM_8		   65431
#  define KEY_NUM_9		   65434
#  define KEY_NUM_PLUS	   65451
#  define KEY_NUM_MINUS	   65453
#  define KEY_NUM_MULTIPLY 65450
#  define KEY_NUM_DIVIDE   65455
#  define KEY_NUM_ENTER	   65421
#  define KEY_NUM_DOT	   65439
#  define KEY_TILDE		   96 // `
#  define KEY_MINUS		   45 // -
#  define KEY_EQUAL		   61 // =
#  define KEY_LBRACKET	   91 // [
#  define KEY_RBRACKET	   93 // ]
#  define KEY_BACKSLASH	   92 // '\'
#  define KEY_SEMICOLON	   59 // ;
#  define KEY_APOSTROPHE   39 // '
#  define KEY_COMMA		   44 // ,
#  define KEY_DOT		   46 // .
#  define KEY_SLASH		   47 // /
#  define KEY_BACKSLASH2   60

# endif

# define WIN_WIDTH	 800
# define WIN_HEIGHT	 600
# define SQUARE_SIZE 50
# define MOVE_SPEED	 1

// Function to draw a blue square
void draw_square(t_game* g)
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
void clear_screen(t_game* g)
{
	mlx_clear_window(g->mlx, g->win);
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
	if (moved)
	{
		clear_screen(g);
		draw_square(g);
		mlx_put_image_to_window(g->mlx, g->win, g->img.img, 100, 100);
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

	g->img.img =
		mlx_xpm_file_to_image(g->mlx, IMG_PATH, &g->img.width, &g->img.height);
	if (!g->img.img)
	{
		put_error("Failed to load sprite sheet\n");
		return (1);
	}

	draw_square(g);

	mlx_hook(g->win, 2, 1L << 0, key_press, g);	  // Handle key press
	mlx_hook(g->win, 3, 1L << 1, key_release, g); // Handle key release
	mlx_hook(g->win, 17, 0, close_window, g);	  // Handle window close event
	mlx_loop_hook(g->mlx, update_game, g);		  // Continuous movement check

	// Enter the main event loop
	mlx_loop(g->mlx);		  // This will run until mlx_loop_end() is called
	if (g->mlx && g->img.img) // Ensure pointers are valid
	{
		mlx_destroy_image(g->mlx, g->img.img);
		g->img.img = NULL; // Mark the window as destroyed
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