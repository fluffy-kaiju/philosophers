/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_run.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:26:33 by mahadad           #+#    #+#             */
/*   Updated: 2022/10/04 12:50:45 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ph_debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	*philo_routine(void *this);

static int	create_thread(t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, &philo_routine, philo))
	{
		ph_exit_msg(EXIT_FAILURE, "phtread_create fail !\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Lunch all philo thread.
 */
static int	start_philo(t_data *data)
{
	int				i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (PH_DEBUG)
			printf("INFO: try to start philo[%d] thread\n", i + 1);
		if (create_thread(&data->table[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	run(t_data *data)
{
	if (start_philo(data))
	{
		ph_exit_msg(EXIT_FAILURE, "create_thread fail !\n");
		return (EXIT_FAILURE);
	}
	while (1)
	{
		usleep(500);
		if (pthread_mutex_lock(&data->data_rw))
			return (EXIT_FAILURE);
		if (data->philo_die || data->nb_eat == data->nb_philo)
			break ;
		if (pthread_mutex_unlock(&data->data_rw))
			return (EXIT_FAILURE);
	}
	if (pthread_mutex_unlock(&data->data_rw))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
