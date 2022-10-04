/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:57:53 by mahadad           #+#    #+#             */
/*   Updated: 2022/10/04 13:53:09 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "ph_debug.h"

long	gettime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	set_death_date(t_philo *me)
{
	long			time;

	time = gettime();
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
int	is_death(t_philo *me, long override)
{
	long			time;
	int				ret;

	if (!override)
		time = gettime();
	else
		time = override;
	if (!time || pthread_mutex_lock(&me->data->data_rw))
		return (EXIT_FAILURE);
	ret = 0;
	if (me->data->philo_die)
			ret += EXIT_FAILURE;
	if (!ret && time >= me->death_date)
	{
		if (!me->data->philo_die)
			printf("%lu %d %s\n", time - me->start_date, me->num, PH_DEATH);
		me->data->philo_die = 1;
		ret += EXIT_FAILURE;
	}
	if (pthread_mutex_unlock(&me->data->data_rw))
		return (EXIT_FAILURE);
	return (ret);
}

int	ph_print(char *msg, t_philo *me)
{
	long			time;

	time = gettime();
	if (!time)
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(&me->data->data_rw))
		return (EXIT_FAILURE);
	if (!me->data->philo_die)
		printf("%lu %d %s\n", time - me->start_date, me->num, msg);
	if (pthread_mutex_unlock(&me->data->data_rw))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	msleep(int ms, t_philo *me, int check_death)
{
	long			end_time;
	long			time;

	end_time = gettime();
	end_time += (ms);
	while (1)
	{
		usleep(100);
		time = gettime();
		if (time > end_time - 1)
			break ;
		if (!time || (check_death && is_death(me, time)))
		{
			if (PH_DEBUG)
				printf("INFO: %lu %d ms:%d die in sleep\n",
					time - me->start_date, me->num, ms);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
