/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:31:58 by okraus            #+#    #+#             */
/*   Updated: 2025/03/09 17:13:42 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>   // For open()
#include <unistd.h>  // For read(), close()
#include <stdlib.h>  // For exit()
#include "defines.h"
#include "parser.h"



int	parser(char *file, t_game *g)
{
    char f[MAX_MAP_SIZE];  // Temporary buffer to read the file
    int fd;
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
    if (bytes == MAX_MAP_SIZE)
    {
        put_error("Map file too big\n");
        close(fd);
        return -1;
    }
    // Close the file
    close(fd);

    // Process the data (example: convert bytes to int values)
    uint32_t w;
    int i;
    int j;

    j = 0;
    w = 0U;
    i = 0U;
    while (i < bytes)
    {
        if (f[i] == '0')
            g->map.m[j] = M_FLOOR;
        else if (f[i] == '1')
            g->map.m[j] = M_WALL;
        else if (f[i] == 'P')
            g->map.m[j] = M_ENTRANCE;
        else if (f[i] == 'C')
            g->map.m[j] = M_COLLECTIBLE;
        else if (f[i] == 'E')
            g->map.m[j] = M_EXIT;
        else if (f[i] == '\n')
        {
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
            continue ;
        }
        w++;
        i++;
        j++;
    }
    if (g->map.width != w && w != 0)
    {
        put_error("Last map line not the correct length\n");
        return -1;
    }
    //more parsing
    return 0;
}

void	print_map(t_game *g)
{
	uint32_t y;
	uint32_t x;

	y = 0;
    while (y < g->map.height)
    {
        x = 0;
        while (x < g->map.width)
        {
            if (g->map.m[y * g->map.width + x] == M_FLOOR)
                put_str(ANSI_BG_BLUE "  " ANSI_RESET);
            else if (g->map.m[y * g->map.width + x] == M_WALL)
                put_str(ANSI_BG_GREEN_DARK "  " ANSI_RESET);
            else if (g->map.m[y * g->map.width + x] == M_ENTRANCE)
                put_str(ANSI_BG_GRAY "  " ANSI_RESET);
            else if (g->map.m[y * g->map.width + x] == M_COLLECTIBLE)
                put_str(ANSI_BG_GOLD "  " ANSI_RESET);
            else if (g->map.m[y * g->map.width + x] == M_EXIT)
                put_str(ANSI_BG_BLUE_DARK "  " ANSI_RESET);
            x++;
        }
        put_str("\n");
        y++;
    }
}
