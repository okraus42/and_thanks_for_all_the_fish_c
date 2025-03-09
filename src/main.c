/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:31:09 by okraus            #+#    #+#             */
/*   Updated: 2025/03/09 17:30:38 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "main.h"
// #include <stdlib.h>

int main(int argc, char *argv[])
{
    t_game g;
    ok_bzero(&g, sizeof(g));
    if (argc == 2)
    {
        parser(argv[1], &g);
        print_map(&g);
    }
    else
        return (1);
    return (game(&g));
}
