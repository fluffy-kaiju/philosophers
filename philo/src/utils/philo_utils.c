/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:57:53 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/28 13:35:58 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "ph_debug.h"

long	gettime(struct timeval *time)
{
	if (gettimeofday(time, NULL))
		return (0);
	return ((time->tv_sec * 1000) + (time->tv_usec / 1000));
}

int	set_death_date(t_philo *me)
{
	long			time;
	struct timeval	t;

	time = gettime(&t);
	if (!time)
	{
		if (PH_DEBUG)
			printf("INFO: philo[%d]: set_death_date: gettime fail !\n", me->num);
		return (EXIT_FAILURE);
	}
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
int	is_death(t_philo *me, long override)
{
	long			time;
	struct timeval	t;
	int				ret;

	if (!override)
		time = gettime(&t);
	else
		time = override;
	if (!time || pthread_mutex_lock(&me->data->data_rw))
		return (EXIT_FAILURE);
	ret = 0;
	if (me->data->philo_die)
			ret += EXIT_FAILURE;
	if (!ret && time > me->death_date)
	{
		// if (pthread_mutex_lock(&me->data->print_stdout))
			// return (EXIT_FAILURE);
		if (!me->data->philo_die)
			printf("is_death: %lu %d %s\n", time, me->num, PH_DEATH);
		me->data->philo_die = 1;
		// if (pthread_mutex_unlock(&me->data->print_stdout))
			// return (EXIT_FAILURE);
		ret += EXIT_FAILURE;
	}
		if (pthread_mutex_unlock(&me->data->data_rw))
			return (EXIT_FAILURE);
	return (ret);
}

int	ph_print(char *msg, t_philo *me)
{
	long			time;
	struct timeval	t;

	time = gettime(&t);
	if (!time)
		return (EXIT_FAILURE);
	// if (pthread_mutex_lock(&me->data->print_stdout))
		// return (EXIT_FAILURE);
	if (pthread_mutex_lock(&me->data->data_rw))
		return (EXIT_FAILURE);
	if (!me->data->philo_die)
		printf("%lu %d %s\n", time, me->num, msg);
	if (pthread_mutex_unlock(&me->data->data_rw))
		return (EXIT_FAILURE);
	// if (pthread_mutex_unlock(&me->data->print_stdout))
		// return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	msleep(int ms, t_philo *me, int check_death)
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
		if (!time || (check_death && is_death(me, time)))
		{
			if (PH_DEBUG)
				printf("philo[%d] ms:%d die from msleep\n", me->num, ms);
			return (EXIT_FAILURE);
		}
		if (time > end_time)
			break ;
	}
	return (EXIT_SUCCESS);
}
