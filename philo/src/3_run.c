/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_run.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:26:33 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/26 15:03:31 by mahadad          ###   ########.fr       */
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
	pthread_mutex_lock(&philo->start);//TODO CHECK RETURN
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
static int	luncher(t_data *data)
{
	int	i;
	i = 0;
	while (i < data->nb_philo)
	{
		printf("INFO: try to create philo[%d] thread\n", i);//TODO REMOVE 
		if (create_thread(&data->table[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Lunch philo thread. If `odd` == `0` start all even philo
 *        and if `odd` == `1` all odd philo.
 */
static int	start_philo(t_data *data, int odd)
{
	int	i;
	i = 0;
	while (i < data->nb_philo)
	{
		if ((i % 2) == odd)
		{
			printf("INFO: try to start philo[%d] thread\n", i);//TODO REMOVE 
			if (pthread_mutex_unlock(&data->table[i].start))
				return (EXIT_FAILURE);
		}
		i++;
	}
	usleep(500);
	return (EXIT_SUCCESS);
}

int	run(t_data *data)
{
	int i;

	i = 0;
	if (luncher(data))
	{
		philo_exit(EXIT_FAILURE, "create_thread fail !\n", data);
		return (EXIT_FAILURE);
	}
	if (start_philo(data, 0) || start_philo(data, 1))
	{
		philo_exit(EXIT_FAILURE, "start_philo fail !\n", data);
		return (EXIT_FAILURE);
	}
	while (1)
	{
		pthread_mutex_lock(&data->data_rw);//TODO CHECK RETURN
		if (data->philo_die)
		{
			pthread_mutex_unlock(&data->data_rw);//TODO CHECK RETURN
			break ;
		}
		pthread_mutex_unlock(&data->data_rw);//TODO CHECK RETURN
	}
	while (i < data->nb_philo)
	{
		if (pthread_join(data->table[i].thread, NULL))
		{
			philo_exit(EXIT_FAILURE, "pthread_join fail !\n", data);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
