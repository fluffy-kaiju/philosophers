/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:30:59 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/27 16:38:53 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

static int	take_fork(t_philo *me, pthread_mutex_t *ph_fork)
{
	if (is_death(me, 0)
		|| pthread_mutex_lock(ph_fork)
		|| is_death(me, 0)
		|| ph_print(PH_FORK, me))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	release_fork(t_philo *me, pthread_mutex_t *ph_fork)//WIP
{
	if (is_death(me, 0)
		|| pthread_mutex_lock(ph_fork)
		|| is_death(me, 0)
		|| ph_print(PH_FORK, me))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * Condition `if (&me->fork == me->next)` will be true only i there is
 * one thread.
 * 
 */
static int	eat(t_philo *me)
{
	ph_print(PH_THINK, me);
	if (&me->fork == me->next)
	{
		if (msleep(me->time_die, me))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (take_fork(me, &me->fork)
		|| is_death(me, 0)
		|| take_fork(me, me->next)
		|| is_death(me, 0)
		|| ph_print(PH_EAT, me)
		|| msleep(me->time_eat, me))
		return (EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}

void	*philo_routine(void *this)
{
	t_philo	*me;

	me = this;
	set_death_date(me);
	pthread_mutex_lock(&me->start);
	while (1)
	{
		if (is_death(me, 0))
			break ;
		if (eat(me))
			break ;
		if (ph_print(PH_SLEEP, me)
			|| msleep(me->time_eat, me))
			break ;
	}
	return (NULL);
}
