/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:11:13 by okraus            #+#    #+#             */
/*   Updated: 2025/03/24 17:42:02 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# ifndef LIB
#  define LIB 0 // minilibx
# endif

# define MINILIBX	   0
# define SDL		   1
# define MAX_MAP_SIDE  1024U
# define MAX_KEY_SIZE  65536U
# define MAX_FILE_SIZE 65536U

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

// Reset colour
# define ANSI_RESET "\x1b[0m"

// 16 RGB colour definitions
# define ANSI_COLOUR_BLACK	 "\x1b[38;2;0;0;0m"		  // Black
# define ANSI_COLOUR_RED	 "\x1b[38;2;255;0;0m"	  // Red
# define ANSI_COLOUR_GREEN	 "\x1b[38;2;0;255;0m"	  // Green
# define ANSI_COLOUR_YELLOW	 "\x1b[38;2;255;255;0m"	  // Yellow
# define ANSI_COLOUR_BLUE	 "\x1b[38;2;0;0;255m"	  // Blue
# define ANSI_COLOUR_MAGENTA "\x1b[38;2;255;0;255m"	  // Magenta
# define ANSI_COLOUR_CYAN	 "\x1b[38;2;0;255;255m"	  // Cyan
# define ANSI_COLOUR_WHITE	 "\x1b[38;2;255;255;255m" // White

// Gray and Gold colours
# define ANSI_COLOUR_GRAY "\x1b[38;2;169;169;169m" // Gray (light)
# define ANSI_COLOUR_GOLD "\x1b[38;2;255;215;0m"   // Gold

# define ANSI_COLOUR_BLUE_LIGHT	 "\x1b[38;2;100;100;255m" // Light Blue
# define ANSI_COLOUR_BLUE_MEDIUM "\x1b[38;2;0;0;200m"	  // Medium Blue
# define ANSI_COLOUR_BLUE_DARK	 "\x1b[38;2;0;0;139m"	  // Dark Blue

# define ANSI_COLOUR_GREEN_LIGHT  "\x1b[38;2;144;238;144m" // Light Green
# define ANSI_COLOUR_GREEN_MEDIUM "\x1b[38;2;0;255;0m"	   // Medium Green
# define ANSI_COLOUR_GREEN_DARK	  "\x1b[38;2;0;128;0m"	   // Dark Green

// 16 RGB background color definitions
# define ANSI_BG_BLACK	 "\x1b[48;2;0;0;0m"		  // Black background
# define ANSI_BG_RED	 "\x1b[48;2;255;0;0m"	  // Red background
# define ANSI_BG_GREEN	 "\x1b[48;2;0;255;0m"	  // Green background
# define ANSI_BG_YELLOW	 "\x1b[48;2;255;255;0m"	  // Yellow background
# define ANSI_BG_BLUE	 "\x1b[48;2;0;0;255m"	  // Blue background
# define ANSI_BG_MAGENTA "\x1b[48;2;255;0;255m"	  // Magenta background
# define ANSI_BG_CYAN	 "\x1b[48;2;0;255;255m"	  // Cyan background
# define ANSI_BG_WHITE	 "\x1b[48;2;255;255;255m" // White background

// Gray and Gold background colors
# define ANSI_BG_GRAY "\x1b[48;2;169;169;169m" // Gray background
# define ANSI_BG_GOLD "\x1b[48;2;255;215;0m"   // Gold background

# define ANSI_BG_BLUE_LIGHT	 "\x1b[48;2;100;100;255m" // Light Blue background
# define ANSI_BG_BLUE_MEDIUM "\x1b[48;2;0;0;200m"	  // Medium Blue background
# define ANSI_BG_BLUE_DARK	 "\x1b[48;2;0;0;139m"	  // Dark Blue background

# define ANSI_BG_GREEN_LIGHT  "\x1b[48;2;144;238;144m" // Light Green background
# define ANSI_BG_GREEN_MEDIUM "\x1b[48;2;0;255;0m" // Medium Green background
# define ANSI_BG_GREEN_DARK	  "\x1b[48;2;0;128;0m" // Dark Green background


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

# define WIN_WIDTH	 1920
# define WIN_HEIGHT	 1080
# define SQUARE_SIZE 50
# define MOVE_SPEED	 1

# define CLR_BLACK      0x000000U
# define CLR_WHITE      0xFFFFFFU

# define CLR_RED        0xFF0000U
# define CLR_LIGHT_RED  0xFF6666U
# define CLR_DARK_RED   0x990000U

# define CLR_GREEN      0x00FF00U
# define CLR_LIGHT_GREEN 0x66FF66U
# define CLR_DARK_GREEN  0x009900U

# define CLR_BLUE       0x0000FFU
# define CLR_LIGHT_BLUE 0x6666FFU
# define CLR_DARK_BLUE  0x000099U

# define CLR_YELLOW      0xFFFF00U
# define CLR_LIGHT_YELLOW 0xFFFF66U
# define CLR_DARK_YELLOW  0x999900U

# define CLR_CYAN       0x00FFFFU
# define CLR_LIGHT_CYAN 0x66FFFFU
# define CLR_DARK_CYAN  0x009999U

# define CLR_MAGENTA       0xFF00FFU
# define CLR_LIGHT_MAGENTA 0xFF66FFU
# define CLR_DARK_MAGENTA  0x990099U

# define CLR_ORANGE      0xFFA500U
# define CLR_LIGHT_ORANGE 0xFFB347U
# define CLR_DARK_ORANGE  0xCC8400U

# define CLR_PURPLE      0x800080U
# define CLR_LIGHT_PURPLE 0xDDA0DDU
# define CLR_DARK_PURPLE  0x4B0082U

# define CLR_BROWN      0x8B4513U
# define CLR_LIGHT_BROWN 0xCD853FU
# define CLR_DARK_BROWN  0x5C2E0FU

# define CLR_PINK       0xFFC0CBU
# define CLR_LIGHT_PINK 0xFFB6C1U
# define CLR_DARK_PINK  0xC71585U

# define CLR_GRAY       0x808080U
# define CLR_LIGHT_GRAY 0xD3D3D3U
# define CLR_DARK_GRAY  0x505050U

# define CLR_GRAY_1  0x222222U  // Very Dark Gray
# define CLR_GRAY_2  0x444444U  // Dark Gray
# define CLR_GRAY_3  0x666666U  // Medium-Dark Gray
# define CLR_GRAY_4  0x888888U  // Mid GRay
# define CLR_GRAY_5  0xAAAAAAU  // Medium-Light GRay
# define CLR_GRAY_6  0xCCCCCCU  // Light GRay
# define CLR_GRAY_7  0xEEEEEEU  // Very Light Gray

# define CLR_GOLD       0xFFD700U
# define CLR_SILVER     0xC0C0C0U
# define CLR_BRONZE     0xCD7F32U

# define CLR_TEAL       0x008080U
# define CLR_LIGHT_TEAL 0x66CCCCU
# define CLR_DARK_TEAL  0x004C4CU

# define CLR_NAVY       0x000080U
# define CLR_LIGHT_NAVY 0x3366CCU
# define CLR_DARK_NAVY  0x00004CU

# define CLR_OLIVE      0x808000U
# define CLR_LIGHT_OLIVE 0xB5B35FU
# define CLR_DARK_OLIVE  0x5A5A00U

# define CLR_MAROON      0x800000U
# define CLR_LIGHT_MAROON 0xB03060U
# define CLR_DARK_MAROON  0x400000U

# define CLR_TURQUOISE      0x40E0D0U
# define CLR_LIGHT_TURQUOISE 0xAFEEEEU
# define CLR_DARK_TURQUOISE  0x008080U


enum e_tiles
{
	M_FLOOR = 0x10U,
	M_WALL = 0x100U,
	M_ENTRANCE = 0x1000U,
	M_EXIT = 0x2000U,
	M_COLLECTIBLE = 0x10000U
};

// Structure to hold game map
typedef struct s_map
{
	uint32_t m[MAX_MAP_SIDE * 2][MAX_MAP_SIDE * 2];
	uint8_t	 f[MAX_MAP_SIDE][MAX_MAP_SIDE];
	uint32_t width;
	uint32_t height;
	//player
	//collectibles
	//enemies
} t_map;

typedef struct s_tile_64x64
{
	uint32_t		data[4096];
} t_tile_64x64;

// works as 64x32 too
typedef struct s_tile_32x64
{
	uint32_t		data[2048];
} t_tile_32x64;

// my screen
typedef struct s_screen
{
	uint32_t		data[WIN_WIDTH * WIN_HEIGHT];
} t_screen;

typedef struct s_img
{
	char		*path;
	void		*img;
	int32_t		width;
	int32_t		height;
	uint8_t		frames;
	int32_t		bpp;
	int32_t		size_line;
	int32_t		endian;
	uint8_t		current_frame;
} t_img;

// Structure to hold game data
typedef struct s_game
{
	void*	mlx;
	void*	win;
	void*	img; //possible can be more for buffered image
	t_screen	screen;
	int32_t x;
	int32_t y;
	bool	keys[MAX_KEY_SIZE]; // Large enough to store all keycodes
	t_map	map;
	t_img	image;
	t_img	bg[16];
	t_tile_64x64	font[128];
	t_tile_64x64	tiles_64x64[256];
	t_tile_32x64	tiles_32x64[256];
} t_game;

#endif
/* DEFINES_H */
