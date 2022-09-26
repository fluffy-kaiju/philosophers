/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:30:59 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/26 16:11:49 by mahadad          ###   ########.fr       */
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

static int	ph_death(t_philo *me, long time)
{
	if (pthread_mutex_lock(&me->data->data_rw))
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(&me->data->print_stdout))
		return (EXIT_FAILURE);
	if (!me->data->philo_die)
		printf("%lu %d %s\n", time, me->num, PH_DEATH);
	me->data->philo_die = 1;
	if (pthread_mutex_unlock(&me->data->print_stdout))
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(&me->data->data_rw))
		return (EXIT_FAILURE);
	return (EXIT_FAILURE);
}

static int check_philo_die(t_philo *me)
{
	int	tmp;

	if (pthread_mutex_lock(&me->data->data_rw))
		return (EXIT_FAILURE);
	tmp = me->data->philo_die;
	if (pthread_mutex_unlock(&me->data->data_rw))
		return (EXIT_FAILURE);
	return (tmp);
}

static int	ph_print(char *msg, t_philo *me)
{
	long ret;

	ret = gettime(&me->time);
	if (!ret)
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(&me->data->print_stdout))
		return (EXIT_FAILURE);
	if (!check_philo_die(me))
		printf("%lu %d %s\n", ret, me->num, msg);
	if (pthread_mutex_unlock(&me->data->print_stdout))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_death(t_philo *me)
{
	long	time;

	time = gettime(&me->time);
	if (!time)
		return (EXIT_FAILURE);
	if (check_philo_die(me) || time > me->death_date)
		if (ph_death(me, time))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
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

static int	set_death_date(t_philo *me)
{
	long ret;

	ret = gettime(&me->time);
	if (!ret)
		return (EXIT_FAILURE);
	me->death_date = ret + me->time_die;
	return (EXIT_SUCCESS);
}

static int take_fork(t_philo *me, pthread_mutex_t *ph_fork)
{
	if (check_death(me)
		|| pthread_mutex_lock(ph_fork)
		|| check_death(me)
		|| ph_print(PH_FORK, me))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ph_think(t_philo *me)
{
	if (check_death(me)
		|| ph_print(PH_THINK, me)
		|| take_fork(me, &me->fork)
		|| check_death(me)
		|| take_fork(me, me->next)
		|| check_death(me))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ph_eat(t_philo *me)
{
	if (check_death(me)
		|| ph_print(PH_EAT, me)
		|| msleep(me->time_eat)
		|| check_death(me)
		|| pthread_mutex_unlock(&me->fork)
		|| pthread_mutex_unlock(me->next)
		|| set_death_date(me))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


static int	ph_sleep(t_philo *me)
{
	if (check_death(me)
		|| ph_print(PH_SLEEP, me)
		|| msleep(me->time_sleep)
		|| check_death(me))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	*philo_routine(void *this)
{
	t_philo *me;

	me = this;
	pthread_mutex_lock(&me->start);
	set_death_date(me);
	while (1)
		if (ph_think(me) || ph_eat(me) || ph_sleep(me))
			return (NULL);
	return (EXIT_SUCCESS);
}