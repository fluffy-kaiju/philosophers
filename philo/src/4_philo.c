/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:30:59 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/30 14:45:53 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ph_debug.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>


static int	eat(t_philo *me)
{
	pthread_mutex_lock(&me->fork);
	if (is_death(me, 0))
	{
		pthread_mutex_unlock(&me->fork);
		return (EXIT_FAILURE);
	}
	ph_print(PH_FORK, me);
	pthread_mutex_lock(me->next);
	if (is_death(me, 0))
	{
		pthread_mutex_unlock(me->next);
		pthread_mutex_unlock(&me->fork);
		return (EXIT_FAILURE);
	}
	ph_print(PH_FORK, me);
	ph_print(PH_EAT, me);
	msleep(me->time_eat, me, 1);
	pthread_mutex_unlock(&me->fork);
	pthread_mutex_unlock(me->next);
	set_death_date(me);
	ph_print(PH_SLEEP, me);
	msleep(me->time_sleep, me, 1);
	return (EXIT_SUCCESS);
}

/**
 * Condition `if (&me->fork == me->next)` will be true only i there is
 * one thread.
 * 
 */
static int	run(t_philo *me)
{
	if (eat(me))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	*philo_routine(void *this)
{
	t_philo			*me;
	struct timeval	t;

	me = this;
	ph_print(PH_THINK, me);
	me->start_date = gettime(&t);
	if (set_death_date(me))
		return (NULL);
	if (me->num % 2)
		msleep(me->time_eat * 0.6, me, 1);
	while (1)
	{
		if (run(me))
		{
			ph_print(PH_DEATH, me);
			if (PH_DEBUG)
			printf("INFO: BREAK while[%d] run()\n", me->num);
			break ;
		}
		if (is_death(me, 0))
		{
			ph_print(PH_DEATH, me);
			printf("INFO: BREAK while[%d] is_death()\n", me->num);
			break ;
		}
		ph_print(PH_THINK, me);
	}
	printf("EXIT [%d]\n", me->num);
	return (NULL);
}
