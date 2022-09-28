/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:30:59 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/28 15:23:12 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

// static int	take_fork(t_philo *me, pthread_mutex_t *ph_fork)
// {
// 	if (pthread_mutex_lock(ph_fork) || ph_print(PH_FORK, me))
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

/**
 * Condition `if (&me->fork == me->next)` will be true only i there is
 * one thread.
 * 
 */
static int	run(t_philo *me)
{
	ph_print("test", me);
	msleep(1000, me, 0);
	pthread_mutex_lock(&me->data->data_rw);//TODO
	me->data->philo_die = 1;
	pthread_mutex_unlock(&me->data->data_rw);//TODO

	return (EXIT_FAILURE);
}

void	*philo_routine(void *this)
{
	t_philo	*me;
	struct timeval t;

	me = this;
	while (1)
		if (gettime(&t) >= me->time_start)
			break ;
	
	if (/*pthread_mutex_lock(&me->start) || */set_death_date(me))
		return (NULL);
	while (1)
	{
		if (run(me))
		{
			printf("BREAK while[%d][%lu\n", me->num, me->time_start);
			break ;
		}
	}
	pthread_mutex_unlock(&me->start);
	printf("EXIT [%d]\n", me->num);
	return (NULL);
}
