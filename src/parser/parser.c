/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:07:47 by okraus            #+#    #+#             */
/*   Updated: 2025/03/16 13:45:49 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <fcntl.h>	// For open()
#include <stdlib.h> // For exit()
#include <unistd.h> // For read(), close()
#include <stdio.h> // For debugging

#include "defines.h"

int parser(char* file, t_game* g)
{
	char	f[MAX_FILE_SIZE]; // Temporary buffer to read the file
	int		fd;
	ssize_t bytes;

	// Open the file in read-only mode
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		put_error("Error opening file\n");
		return -1;
	}

	// Read file contents into f buffer
	bytes = read(fd, f, sizeof(f));
	if (bytes == -1)
	{
		put_error("Error reading file\n");
		close(fd);
		return -1;
	}
	if (bytes == MAX_FILE_SIZE)
	{
		put_error("Map file too big\n");
		close(fd);
		return -1;
	}
	// Close the file
	close(fd);
	//fake split ap to 1024 lines
	// Process the data (example: convert bytes to int values)
	uint32_t w;
	int		 i;
	int		 j;

	j = 0;
	w = 0U;
	i = 0U;
	//read max width
	//fill to max width
	write(1, "0a\n", 3);
	while (i < bytes)
	{
		// g->map.height = 0;
		// write(1, "0l\n", 3);
		// char c = '0' + g->map.height;
		// write(1, &c, 1);
		// write(1, "0l\n", 3);
		if (f[i] == '0')
			g->map.f[g->map.height][j] = '0';
		else if (f[i] == '1')
			g->map.f[g->map.height][j] = '1';
		else if (f[i] == 'P')
			g->map.f[g->map.height][j] = 'P';
		else if (f[i] == 'C')
			g->map.f[g->map.height][j] = 'C';
		else if (f[i] == 'E')
			g->map.f[g->map.height][j] = 'E';
		else if (f[i] == '\n')
		{
			j = 0;
			g->map.height++;
			if (g->map.width != w)
			{
				if (g->map.width == 0)
					g->map.width = w;
				else
				{
					put_error("Map line not the correct length\n");
					return -1;
				}
			}
			w = 0U;
			i++;
			continue;
		}
		w++;
		i++;
		j++;
		// printf("%d\n", g->map.height);
		// write(1, "0l\n", 3);
	}
	if (g->map.width != w && w != 0)
	{
		put_error("Last map line not the correct length\n");
		return -1;
	}
	if (w != 0)
		g->map.height++;
	//check map width and map height
	
	//stuff here
	// make sure the map is valid

	//more parsing
	uint32_t y;
	uint32_t x;
	write(1, "0b\n", 3);
	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			if (g->map.f[y][x] == '0')
			{
				g->map.m[2 * y][2 * x] = M_FLOOR;
				g->map.m[2 * y][2 * x + 1] = M_FLOOR;
				g->map.m[2 * y + 1][2 * x] = M_FLOOR;
				g->map.m[2 * y + 1][2 * x + 1] = M_FLOOR;
			}
				else if (g->map.f[y][x] == '1')
			{
				g->map.m[2 * y][2 * x] = M_WALL;
				g->map.m[2 * y][2 * x + 1] = M_WALL;
				g->map.m[2 * y + 1][2 * x] = M_WALL;
				g->map.m[2 * y + 1][2 * x + 1] = M_WALL;
			}
				else if (g->map.f[y][x] == 'P')
			{
				g->map.m[2 * y][2 * x] = M_ENTRANCE;
				g->map.m[2 * y][2 * x + 1] = M_ENTRANCE;
				g->map.m[2 * y + 1][2 * x] = M_ENTRANCE;
				g->map.m[2 * y + 1][2 * x + 1] = M_ENTRANCE;
			}
				else if (g->map.f[y][x] == 'C')
			{
				g->map.m[2 * y][2 * x] = M_COLLECTIBLE;
				g->map.m[2 * y][2 * x + 1] = M_COLLECTIBLE;
				g->map.m[2 * y + 1][2 * x] = M_COLLECTIBLE;
				g->map.m[2 * y + 1][2 * x + 1] = M_COLLECTIBLE;
			}
				else if (g->map.f[y][x] == 'E')
			{
				g->map.m[2 * y][2 * x] = M_EXIT;
				g->map.m[2 * y][2 * x + 1] = M_EXIT;
				g->map.m[2 * y + 1][2 * x] = M_EXIT;
				g->map.m[2 * y + 1][2 * x + 1] = M_EXIT;
			}
				x++;
		}
		y++;
	}
	g->map.height *= 2;
	g->map.width *= 2;
	write(1, "0c\n", 3);
	//update map to have tiles
	return 0;
}

void print_map(t_game* g)
{
	uint32_t y;
	uint32_t x;

	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			if (g->map.m[y][x] == M_FLOOR)
				put_str(ANSI_BG_BLUE "  " ANSI_RESET);
			else if (g->map.m[y][x] == M_WALL)
				put_str(ANSI_BG_GREEN_DARK "  " ANSI_RESET);
			else if (g->map.m[y][x] == M_ENTRANCE)
				put_str(ANSI_BG_GRAY "  " ANSI_RESET);
			else if (g->map.m[y][x] == M_COLLECTIBLE)
				put_str(ANSI_BG_GOLD "  " ANSI_RESET);
			else if (g->map.m[y][x] == M_EXIT)
				put_str(ANSI_BG_BLUE_DARK "  " ANSI_RESET);
			x++;
		}
		put_str("\n");
		y++;
	}
}
