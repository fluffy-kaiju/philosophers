/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:01:22 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/26 15:46:28 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ph_debug.h"
#include <stdlib.h>
#include <stdio.h>

int	ft_isdigit(int c);

/**
 * @brief Check if all input are positif number, if not will exit with a error
 *        message.
 */
static int	arg_check(int ac, char **av)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < ac)
	{
		while (av[x][y])
		{
			if (!ft_isdigit(av[x][y]))
			{
				ph_exit_msg(EXIT_FAILURE, "non digit character or "
					"negative number in arg.\n");
				return (EXIT_FAILURE);
			}
			y++;
		}
		y = 0;
		x++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Will skip the first `ac` and `av` arg. Check if the args are only
 *        digit character and populate the data struct.
 */
int	parser(int ac, char **av)
{
	if (!(ac == 4 || ac == 5))
	{
		ph_exit_msg(EXIT_FAILURE, PH_BADARG1 PH_BADARG2);
		return (EXIT_FAILURE);
	}
	if (arg_check(ac, av))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
