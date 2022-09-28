/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:30:59 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/28 14:27:54 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

static int	take_fork(t_philo *me, pthread_mutex_t *ph_fork)
{
	if (pthread_mutex_lock(ph_fork) || ph_print(PH_FORK, me))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * Condition `if (&me->fork == me->next)` will be true only i there is
 * one thread.
 * 
 */
static int	run(t_philo *me)
{
	if (is_death(me, 0) || ph_print(PH_THINK, me) || &me->fork == me->next)
	{
		if (msleep(me->time_die, me, 1))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (take_fork(me, &me->fork)
		|| is_death(me, 0)
		|| take_fork(me, me->next)
		|| is_death(me, 0)
		|| ph_print(PH_EAT, me)
		|| msleep(me->time_eat, me, 1)
		|| pthread_mutex_unlock(&me->fork)
		|| pthread_mutex_unlock(me->next)
		|| set_death_date(me)
		|| is_death(me, 0)
		|| ph_print(PH_SLEEP, me)
		|| msleep(me->time_sleep, me, 1))
		{
			return (EXIT_FAILURE);
		}
	return (EXIT_SUCCESS);
}

void	*philo_routine(void *this)
{
	t_philo	*me;

	me = this;
	if (pthread_mutex_lock(&me->start) || set_death_date(me))
		return (NULL);
	while (1)
	{
		if (run(me))
		{
			printf("BREAK while[%d]\n", me->num);
			break ;
		}
	}
	pthread_mutex_unlock(&me->start);
	return (NULL);
}
