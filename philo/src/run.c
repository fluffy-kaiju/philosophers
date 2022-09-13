/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:26:33 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/13 15:27:30 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ph_debug.h"
#include <stdlib.h>
#include <stdio.h>

static void	mutex_init(t_data *data)
{
	int		x;
	t_philo	*tmp;

	x = 0;
	tmp = data->table;
	while (x < data->nb_philo)
	{
		if (PH_DEBUG)
			printf("INFO: init mutext for t_philo [%p]\n", tmp);
		if (pthread_mutex_init(&tmp->fork, NULL))
			philo_exit(EXIT_FAILURE, "pthread_mutex_init fail !\n", data);
		tmp = tmp->next;
		x++;
	}
}

// typedef struct s_run
// {
// 	t_data *data;
// 	t_philo *philo;
// }				t_run;


// static void	philo_routine(t_run data)
// {
// 	printf("INFO: philo [%d]:[%p] start\n", num, this);
// }

// static void	create_thread(t_philo *philo, int num)
// {
// 	t_run arg;

// 	arg.data = data;
// 	pthread_create(&philo->thread, NULL, &philo_routine, );
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