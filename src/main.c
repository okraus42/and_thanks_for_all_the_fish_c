/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:31:09 by okraus            #+#    #+#             */
/*   Updated: 2025/03/16 11:41:40 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "main.h"
#include <unistd.h> //for debug

int main(int argc, char *argv[])
{
    t_game g;
    ok_bzero(&g, sizeof(g));
    if (argc == 2)
    {
		write(1, "0\n", 2);
        parser(argv[1], &g);
		write(1, "1\n", 2);
        print_map(&g);
		write(1, "2\n", 2);
    }
    else
        return (1);
    return (game(&g));
}
