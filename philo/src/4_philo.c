/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:30:59 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/26 16:18:42 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

static long	msec_constructor(long sec, int usec)
{
	return (sec * 1000) + (usec / 1000);
}

static long	gettime(struct timeval *time)
{
	if (gettimeofday(time, NULL))
		return (0);
	return (msec_constructor(time->tv_sec, time->tv_usec));
}

static int	msleep(int ms)
{
	long 			end_time;
	long 			time;
	struct timeval	t;

	end_time = gettime(&t);
	if (!end_time)
		return (EXIT_FAILURE);
	end_time += (ms);
	if (usleep((ms * 1000) * 0.8))
		return (EXIT_FAILURE);
	time = gettime(&t);
	if (!time)
		return (EXIT_FAILURE);
	while (time < end_time)
	{
		usleep(100);
		time = gettime(&t);
		if (!time)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	*philo_routine(void *this)
{
	t_philo *me;

	me = this;
	pthread_mutex_lock(&me->start);
	set_death_date(me);
	return (EXIT_SUCCESS);
}