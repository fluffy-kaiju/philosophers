/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_run.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:26:33 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/16 13:42:22 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ph_debug.h"
#include <stdlib.h>
#include <stdio.h>

void	*philo_routine(void *this);

static int	create_thread(t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, &philo_routine, philo))
	{
		philo_exit(EXIT_FAILURE, "phtread_create fail !", philo->data);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
/**
 * @brief Lunch philo thread. If `odd` == `0` start all even philo
 *        and if `odd` == `1` all odd philo.
 */
static int	luncher(t_data *data, int odd)
{
	int	i;
	i = 0;
	while (i < data->nb_philo)
	{
		if ((i % 2) == odd)
		{
			printf("INFO: try to create philo[%d] thread\n", i);
			if (create_thread(&data->table[i]))
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	run(t_data *data)
{
	int i;

	if (luncher(data, 1) || luncher(data, 0))
	{
		philo_exit(EXIT_FAILURE, "create_thread fail !\n", data);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < data->nb_philo)//TODO check if we use join or detach thread
	{
		if (pthread_detach(data->table[i].thread))
		{
			philo_exit(EXIT_FAILURE, "pthread_join fail !\n", data);
			return (EXIT_FAILURE);
		}
		i++;
	}
	while (!data->philo_die)
	{
		
	}
	
	return (EXIT_SUCCESS);
}
