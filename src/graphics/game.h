/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:16:34 by okraus            #+#    #+#             */
/*   Updated: 2025/03/06 17:22:11 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GAME_H
# define GAME_H

#include "defines.h"

#ifdef LIB
    #if LIB == 1
        #include "SDL.h"
    #else
        #include "mlx.h"
    #endif
#endif

// utils
void	put_error(char const *const str);
void	put_str(char const *const str);

#endif /* GAME_H */
