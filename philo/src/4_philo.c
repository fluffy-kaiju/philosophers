/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:30:59 by mahadad           #+#    #+#             */
/*   Updated: 2022/10/04 14:09:21 by mahadad          ###   ########.fr       */
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
	if (msleep(me->time_eat, me, 1))
		return (PH_DEATH_EXIT);
	me->nb_eat++;
	pthread_mutex_unlock(&me->fork);
	pthread_mutex_unlock(me->next);
	set_death_date(me);
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
		return (PH_DEATH_EXIT);
	if (me->nb_must_eat && me->nb_eat == me->nb_must_eat)
	{
		if (pthread_mutex_lock(&me->data->data_rw))
			return (EXIT_FAILURE);
		me->data->nb_eat++;
		if (pthread_mutex_unlock(&me->data->data_rw))
			return (EXIT_FAILURE);
		return (PH_EAT_EXIT);
	}
	ph_print(PH_SLEEP, me);
	if (msleep(me->time_sleep, me, 1))
		return (PH_DEATH_EXIT);
	ph_print(PH_THINK, me);
	return (EXIT_SUCCESS);
}

void	*philo_routine(void *this)
{
	t_philo	*me;
	int		ret;

	me = this;
	ph_print(PH_THINK, me);
	me->start_date = gettime();
	if (set_death_date(me))
		return (NULL);
	if (me->num % 2)
		msleep(me->time_eat * 0.6, me, 1);
	if (&me->fork == me->next)
		msleep(me->time_die, me, 1);
	while (!is_death(me, 0))
	{
		ret = run(me);
		if (ret == PH_DEATH_EXIT)
		{
			ph_print(PH_DEATH, me);
			break ;
		}
		if (ret == PH_EAT_EXIT || ret == EXIT_FAILURE)
			break ;
	}
	return (NULL);
}
