/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_run.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:26:33 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/27 14:02:43 by mahadad          ###   ########.fr       */
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
	if (pthread_mutex_lock(&philo->start))
		return (EXIT_FAILURE);
	if (pthread_create(&philo->thread, NULL, &philo_routine, philo))
	{
		ph_exit_msg(EXIT_FAILURE, "phtread_create fail !");
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

static int	philo_join(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->nb_philo)
	{
		if (pthread_join(data->table[x].thread, NULL))
		{
			ph_exit_msg(EXIT_FAILURE, "pthread_join fail !\n");
			return (EXIT_FAILURE);
		}
		printf("INFO: try to join philo[%d] thread\n", x);//TODO REMOVE
		x++;
	}
	return (EXIT_SUCCESS);
}

int	run(t_data *data)
{
	int	tmp;

	if (luncher(data) || start_philo(data, 0) || start_philo(data, 1))
	{
		ph_exit_msg(EXIT_FAILURE, "create_thread fail !\n");
		return (EXIT_FAILURE);
	}
	while (1)
	{
		if (pthread_mutex_lock(&data->data_rw))
			return (EXIT_FAILURE);
		tmp = data->philo_die;
		if (pthread_mutex_unlock(&data->data_rw))//TODO CHECK DEATH
			return (EXIT_FAILURE);
		if (tmp)
			break ;
	}
	if (philo_join(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
