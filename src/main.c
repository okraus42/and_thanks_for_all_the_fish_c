/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:31:09 by okraus            #+#    #+#             */
/*   Updated: 2025/03/22 10:45:11 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "main.h"
#include <unistd.h> //for debug
#include <stdlib.h> //for malloc and free

int main(int argc, char *argv[])
{
    t_game	*g;
	int		retVal;

	retVal = 0;
    if (argc == 2)
    {
		g = malloc(sizeof(t_game));
		if (!g)
			return (1);
		ok_bzero(g, sizeof(t_game));
		write(1, "0\n", 2);
        parser(argv[1], g);
		write(1, "1\n", 2);
        print_map(g);
		write(1, "2\n", 2);
		game(g);
		free(g);
    }
	else
		retVal = 1;
	return (retVal);
}
