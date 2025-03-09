/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:40:01 by okraus            #+#    #+#             */
/*   Updated: 2025/03/09 15:50:55 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stddef.h>
#include <stdint.h>

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

void *ok_memset(void *ptr, int value, size_t num)
{
    uint64_t fill = (unsigned char)value;
    fill |= fill << 8;
    fill |= fill << 16;
    fill |= fill << 32;
    
    uint64_t *p64 = (uint64_t *)ptr;
    while (num >= 8) {
        *p64++ = fill;
        num -= 8;
    }
    
    unsigned char *p8 = (unsigned char *)p64;
    while (num--) {
        *p8++ = (unsigned char)value;
    }
    return ptr;
}

void *ok_bzero(void *ptr, size_t num) 
{
    uint64_t *p64 = (uint64_t *)ptr;
    while (num >= 8) {
        *p64++ = 0;
        num -= 8;
    }
    
    unsigned char *p8 = (unsigned char *)p64;
    while (num--) {
        *p8++ = 0;
    }
    return ptr;
}