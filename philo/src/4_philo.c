/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:30:59 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/27 14:01:51 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

static long	msec_constructor(long sec, int usec)
{
	return ((sec * 1000) + (usec / 1000));
}

static long	gettime(struct timeval *time)
{
	if (gettimeofday(time, NULL))
		return (0);
	return (msec_constructor(time->tv_sec, time->tv_usec));
}

static int	set_death_date(t_philo *me)
{
	long			time;
	struct timeval	t;

	time = gettime(&t);
	if (!time)
		return (EXIT_FAILURE);
	me->death_date = time + me->time_die;
	return (EXIT_SUCCESS);
}
/**
 * @brief Compare the actual time with the `me->death_date`, return `1` if the
 *        death_date have been exeeded else return `0`.
 * 
 * @param ovorride if override is true the function will use his value as actual
 *                 time.
 * @return int `EXIT_FAILURE` if the phlilo is death otherwise `EXIT_SUCCESS`.
 */
static int	check_death(t_philo *me, long override)
{
	long			time;
	struct timeval	t;

	if (override)
		time = gettime(&t);
	else
		time = override;
	if (!time)
		return (EXIT_FAILURE);
	if (time > me->death_date)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	msleep(int ms, t_philo *me)
{
	long			end_time;
	long			time;
	struct timeval	t;

	end_time = gettime(&t);
	if (!end_time)
		return (EXIT_FAILURE);
	end_time += (ms);
	while (1)
	{
		usleep(100);
		time = gettime(&t);
		if (!time || check_death(me, time))
			return (EXIT_FAILURE);
		if (time > end_time)
			break ;
	}
	return (EXIT_SUCCESS);
}

void	*philo_routine(void *this)
{
	t_philo	*me;

	me = this;
	set_death_date(me);
	msleep(5000, me);
	pthread_mutex_lock(&me->start);
	printf("philo[%d] running\n", me->num);
	while (1)
	{
		if (check_death(me, 0))
			break ;
	}
	printf("philo[%d] died\n", me->num);
	return (NULL);
}
