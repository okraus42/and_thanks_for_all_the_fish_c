/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:40:01 by okraus            #+#    #+#             */
/*   Updated: 2025/03/06 17:07:50 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	put_error(char const *const str)
{
	size_t	len;

	len = 0;
	while (str[len])
	{
		len++;
	}
	(void)write(2, str, len);
}

void	put_str(char const *const str)
{
	size_t	len;

	len = 0;
	while (str[len])
	{
		len++;
	}
	(void)write(1, str, len);
}
