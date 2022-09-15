/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:58:39 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/15 15:41:11 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Warn, is only a exemple, the code is note safe !
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include "philo.h"

int parser(int ac, char **av, t_data *data);
int	init_data(int ac, char **av, t_data *data);
int	run(t_data *data);

/**
 * @brief Will set all the memory block of a struct to `0` bit.
 */
static void	struct_to_null(void *data, int size)
{
	memset((char *)data, 0, size);
}

/**
 * Step 1:
 *        Will init all data structure with `parser`. First check if all
 *        input are only positif numeric then storing in a linked list.
 * Step 2:
 *        Init all the mutex for each `t_philo->fork` and `t_philo->thread`.
 */
int	main(int ac, char **av)
{
	t_data	data;

	ac--;
	av++;
	struct_to_null(&data, sizeof(t_data));
	if (parser(ac, av, &data) || init_data(ac, av, &data) || run(&data))
	{
		philo_exit(EXIT_SUCCESS, NULL, &data);
		return (EXIT_FAILURE);
	}
	philo_exit(EXIT_SUCCESS, NULL, &data);
	return (EXIT_SUCCESS);
}
