/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:31:09 by okraus            #+#    #+#             */
/*   Updated: 2025/03/04 18:39:40 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char *argv[])
{
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	if (argc < 1 || argv[0] == NULL)
	{
		exit_status = EXIT_FAILURE;
	}
	put_error("Game is missing\n");
	return (exit_status);
}
