/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:30:59 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/16 14:15:33 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
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

// static void	check_death(struct timeval *time)
// {
// 	long	tmp;

// 	tmp = time_constructor(time->tv_sec, time->tv_usec);
// 	gettimeofday
// 	if ( tmp)
// }

void	*philo_routine(void *this)
{
	t_philo *me;

	me = this;
	gettimeofday(&me->time, NULL);
	printf("Ping [%3d][%lu]\n", me->num, gettime(&me->time));
	gettimeofday(&me->time, NULL);
	usleep(5000000);
	pthread_mutex_lock(&me->data->data_rw);
	printf("end  [%3d][%lu]\n", me->num, gettime(&me->time));
	me->data->philo_die = 1;
	pthread_mutex_unlock(&me->data->data_rw);
	return 0;
}