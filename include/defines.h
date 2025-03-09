/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:11:13 by okraus            #+#    #+#             */
/*   Updated: 2025/03/09 17:15:31 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef DEFINES_H
# define DEFINES_H

# ifndef LIB
#  define LIB 0 // minilibx
# endif

# define MINILIBX	0
# define SDL		1
# define MAX_MAP_SIZE	65536U
# define MAX_KEY_SIZE	65536U

# include <stdbool.h>
# include <stdint.h>
# include <stddef.h>

// Reset colour
#define ANSI_RESET      "\x1b[0m"

// 16 RGB colour definitions
#define ANSI_COLOUR_BLACK       	"\x1b[38;2;0;0;0m"        // Black
#define ANSI_COLOUR_RED         	"\x1b[38;2;255;0;0m"      // Red
#define ANSI_COLOUR_GREEN       	"\x1b[38;2;0;255;0m"      // Green
#define ANSI_COLOUR_YELLOW      	"\x1b[38;2;255;255;0m"    // Yellow
#define ANSI_COLOUR_BLUE        	"\x1b[38;2;0;0;255m"      // Blue
#define ANSI_COLOUR_MAGENTA     	"\x1b[38;2;255;0;255m"    // Magenta
#define ANSI_COLOUR_CYAN        	"\x1b[38;2;0;255;255m"    // Cyan
#define ANSI_COLOUR_WHITE       	"\x1b[38;2;255;255;255m"  // White

// Gray and Gold colours
#define ANSI_COLOUR_GRAY        	"\x1b[38;2;169;169;169m"	// Gray (light)
#define ANSI_COLOUR_GOLD        	"\x1b[38;2;255;215;0m"		// Gold

#define ANSI_COLOUR_BLUE_LIGHT  	"\x1b[38;2;100;100;255m"  // Light Blue
#define ANSI_COLOUR_BLUE_MEDIUM 	"\x1b[38;2;0;0;200m"      // Medium Blue
#define ANSI_COLOUR_BLUE_DARK   	"\x1b[38;2;0;0;139m"      // Dark Blue

#define ANSI_COLOUR_GREEN_LIGHT  	"\x1b[38;2;144;238;144m"  // Light Green
#define ANSI_COLOUR_GREEN_MEDIUM	"\x1b[38;2;0;255;0m"      // Medium Green
#define ANSI_COLOUR_GREEN_DARK   	"\x1b[38;2;0;128;0m"      // Dark Green


// 16 RGB background color definitions
#define ANSI_BG_BLACK       "\x1b[48;2;0;0;0m"         // Black background
#define ANSI_BG_RED         "\x1b[48;2;255;0;0m"       // Red background
#define ANSI_BG_GREEN       "\x1b[48;2;0;255;0m"       // Green background
#define ANSI_BG_YELLOW      "\x1b[48;2;255;255;0m"     // Yellow background
#define ANSI_BG_BLUE        "\x1b[48;2;0;0;255m"       // Blue background
#define ANSI_BG_MAGENTA     "\x1b[48;2;255;0;255m"     // Magenta background
#define ANSI_BG_CYAN        "\x1b[48;2;0;255;255m"     // Cyan background
#define ANSI_BG_WHITE       "\x1b[48;2;255;255;255m"   // White background

// Gray and Gold background colors
#define ANSI_BG_GRAY        "\x1b[48;2;169;169;169m"   // Gray background
#define ANSI_BG_GOLD        "\x1b[48;2;255;215;0m"     // Gold background

#define ANSI_BG_BLUE_LIGHT  "\x1b[48;2;100;100;255m"   // Light Blue background
#define ANSI_BG_BLUE_MEDIUM "\x1b[48;2;0;0;200m"       // Medium Blue background
#define ANSI_BG_BLUE_DARK   "\x1b[48;2;0;0;139m"       // Dark Blue background

#define ANSI_BG_GREEN_LIGHT "\x1b[48;2;144;238;144m"   // Light Green background
#define ANSI_BG_GREEN_MEDIUM "\x1b[48;2;0;255;0m"     // Medium Green background
#define ANSI_BG_GREEN_DARK  "\x1b[48;2;0;128;0m"       // Dark Green background

enum	e_tiles
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
    uint32_t	m[MAX_MAP_SIZE];
    uint32_t	width;
    uint32_t	height;
	//player
	//collectibles
	//enemies
} t_map;

// Structure to hold game data
typedef struct s_game
{
    void		*mlx;
    void		*win;
    int32_t		x;
    int32_t		y;
    bool		keys[MAX_KEY_SIZE]; // Large enough to store all keycodes
	t_map		map;
} t_game;

#endif /* DEFINES_H */
