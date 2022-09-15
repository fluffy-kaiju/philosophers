/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:30:59 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/15 15:26:01 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

static long	time_constructor(long sec, int usec)
{
	return (sec * 1000) + (usec / 1000);
}

static long	gettime(struct timeval *time)
{
	if (gettimeofday(time, NULL))
		return 0;
	return time_constructor(time->tv_sec, time->tv_usec);
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
	usleep(2000000);
	gettimeofday(&me->time, NULL);
	printf("end  [%3d][%lu%d]\n", me->num, me->time.tv_sec, me->time.tv_usec / 1000);
	return 0;
}