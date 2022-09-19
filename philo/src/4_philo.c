/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:30:59 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/19 11:41:21 by mahadad          ###   ########.fr       */
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

void	ph_print(char *msg, t_philo *me)
{
	pthread_mutex_lock(&me->data->data_rw);
	if (!me->data->print_stdout)
		printf("%lu %d %s\n", gettime(&me->time), me->num, msg);
	pthread_mutex_unlock(&me->data->data_rw);
}

static void	ph_sleep(int sec)
{
	usleep(sec * 1000000);
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
	ph_print(PH_FORK, me);
	gettimeofday(&me->time, NULL);
	// usleep(5000000);
	ph_sleep(5);
	ph_print(PH_DEATH, me);
	write(STDOUT_FILENO, "test\n", 5);
	pthread_mutex_lock(&me->data->data_rw);
	me->data->philo_die = 1;
	me->data->print_stdout = 1;
	pthread_mutex_unlock(&me->data->data_rw);
	return 0;
}