/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:30:59 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/19 14:02:42 by mahadad          ###   ########.fr       */
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
		return (EXIT_SUCCESS);
	return (msec_constructor(time->tv_sec, time->tv_usec));
}

static int	ph_print(char *msg, t_philo *me)
{
	long ret;

	ret = gettime(&me->time);
	if (!ret)
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(&me->data->data_rw))
		return (EXIT_FAILURE);
	if (!me->data->philo_die)
	{
		if (pthread_mutex_lock(&me->data->print_stdout))
			return (EXIT_FAILURE);
		printf("%lu %d %s\n", ret, me->num, msg);
		if (pthread_mutex_unlock(&me->data->print_stdout))
			return (EXIT_FAILURE);
	}
	if (pthread_mutex_unlock(&me->data->data_rw))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ph_sleep(int ms)
{
	return (usleep(ms * 1000));
}

static int	get_death_date(t_philo *me)
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
	if (pthread_mutex_lock(ph_fork))
		return (EXIT_FAILURE);
	if (ph_print(PH_FORK, me))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ph_death(t_philo *me)
{
	if (pthread_mutex_lock(&me->data->data_rw))
		return (EXIT_FAILURE);
	me->data->philo_die = 1;
	write(1, "====== DEATH =======\n", 22);//TODO REMOVE
	if (pthread_mutex_unlock(&me->data->data_rw))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_death_date(t_philo *me)
{
	long	time;

	time = gettime(&me->time);
	if (!time)
		return (EXIT_FAILURE);
	if (time > me->death_date)
		if (ph_death(me))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ph_eat(t_philo *me)
{
	
	if (ph_print(PH_EAT, me) || ph_sleep(me->time_eat))
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(&me->fork) || pthread_mutex_unlock(me->next))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	*philo_routine(void *this)
{
	t_philo *me;

	me = this;
	while (1)
	{
		// write(1, "DEBUG1\n", 7);

		if (get_death_date(me))
			return (NULL);
		
		// write(1, "DEBUG2\n", 7);
		
		if (ph_print(PH_THINK, me) || take_fork(me, &me->fork))
			return (NULL);
		
		// write(1, "DEBUG3\n", 7);
		
		if (check_death_date(me))
			return (NULL);
		
		// write(1, "DEBUG4\n", 7);
		
		if (take_fork(me, me->next))
			return (NULL);
		
		// write(1, "DEBUG5\n", 7);
		
		if (check_death_date(me))
			return (NULL);
		
		// write(1, "DEBUG6\n", 7);
		
		if (ph_eat(me))
			return (NULL);
		
		// write(1, "DEBUG7\n", 7);
		
		if (check_death_date(me))
			return (NULL);
		
		// write(1, "DEBUG8\n", 7);
		
		if (ph_print(PH_SLEEP, me) || ph_sleep(me->time_eat))
			return (NULL);
		
		// write(1, "DEBUG9\n", 7);
		
		if (check_death_date(me))
			return (NULL);
		
		// write(1, "DEBUG10\n", 6);
	}
	return (EXIT_SUCCESS);
}