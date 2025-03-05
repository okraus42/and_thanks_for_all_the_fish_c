/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:31:09 by okraus            #+#    #+#             */
/*   Updated: 2025/03/05 19:00:47 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include <stdio.h>

#ifdef USE_SDL
# include "SDL.h"

int main(void)
{
    put_error("Game SDL is missing\n");

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        put_error("Game SDL is missing\n");
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window)
    {
        put_error("Game SDL is missing\n");
        SDL_Quit();
        return 1;
    }
    SDL_Delay(2000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

#else
# include "mlx.h"

int main(void)
{
    put_error("Minilbx is missing\n");

    void *mlx = mlx_init();
    if (!mlx)
    {
        put_error("Minilbx is missing\n");
        return 1;
    }
    void *win = mlx_new_window(mlx, 800, 600, "MiniLibX Window");
	(void)win;
    mlx_loop(mlx);
    return 0;
}

#endif
