/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_run.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:26:33 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/15 14:31:31 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ph_debug.h"
#include <stdlib.h>
#include <stdio.h>

void	*philo_routine(void *this);

static void	create_thread(t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, &philo_routine, philo))
		philo_exit(EXIT_FAILURE, "phtread_create fail !", philo->data);
}

void	run(t_data *data)
{
	int	i;
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