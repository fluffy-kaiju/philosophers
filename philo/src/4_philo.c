/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:30:59 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/15 15:04:16 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

long	gettime(struct timeval *time)
{
	gettimeofday(time, NULL);
	return (time->tv_sec * 1000) + (time->tv_usec / 1000);
}

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