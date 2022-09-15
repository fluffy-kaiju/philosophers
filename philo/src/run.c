/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:26:33 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/15 11:24:54 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ph_debug.h"
#include <stdlib.h>
#include <stdio.h>

static void	mutex_init(t_data *data)
{
	int		x;

	x = 0;
	while (x < data->nb_philo)
	{
		if (PH_DEBUG)
			printf("INFO: init mutext for t_philo [%d]\n", x);
		if (pthread_mutex_init(&data->table[x].fork, NULL))
			philo_exit(EXIT_FAILURE, "pthread_mutex_init fail !\n", data);
		x++;
	}
}

void	*philo_routine(void *this)
{
	(void)this;
	t_philo *me;

	me = this;
	printf("Ping [%d]\n", me->num);
	return 0;
}

static void	create_thread(t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, &philo_routine, philo))
		philo_exit(EXIT_FAILURE, "phtread_create fail !", philo->data);
}

void	run(t_data *data)
{
	int	i;
	mutex_init(data);
	i = 0;
	while (i < data->nb_philo)
	{
		if (i % 2)
			create_thread(&data->table[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (!(i % 2))
			create_thread(&data->table[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->table[i].thread, NULL))
			philo_exit(EXIT_FAILURE, "pthread_join fail !", data);
		i++;
	}
}