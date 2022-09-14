/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:26:33 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/14 12:24:19 by mahadad          ###   ########.fr       */
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

// static void	philo_routine(t_philo *this)
// {
// 	printf("INFO: philo [%d]:[%p] start\n", this->num, this);
// }

// static void	create_thread(t_philo *philo, int num)
// {
// 	(void)num;
// 	(void)philo;
// 	// pthread_create(&philo->thread, NULL, &philo_routine, );
// }

void	run(t_data *data)
{
	int	i;

	mutex_init(data);
	i = 0;
	while (i < data->nb_philo)
	{
		if (i % 2)
			printf("%d\n", i);
		i++;
	}
	
}