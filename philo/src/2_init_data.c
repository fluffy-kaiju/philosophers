/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:04:38 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/15 14:46:56 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ph_debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int		ft_atoi(const char *str);
void	*ft_calloc(size_t size);

static void	mutex_init(t_data *data)
{
	int		x;

	x = 0;
	while (x < data->nb_philo)
	{
		if (PH_DEBUG)
			printf("INFO: init mutext for t_philo [%d]\n", x);
		if (pthread_mutex_init(&data->table[x].fork, NULL))
			philo_exit(EXIT_FAILURE, "pthread_mutex_init fail !\n", data);
		x++;
	}
}

/**
 * @brief Get the index
 */
int	get_index(int index, int len)
{
	while (index < 0)
		index += len;
	while (index >= len)
		index -= len;
	return (index);
}

/**
 * @brief Create link list for all philo.
 */
static void	philo_data_constructor(int nb, t_data *data)
{
	int				i;
	t_philo			*table;
	//NOTE if the code arrived here `nb` need to not be `0`.
	data->table = ft_calloc(sizeof(t_philo) * nb);
	if (!data->table)
		philo_exit(EXIT_FAILURE, "data->table alloc fail.\n", data);
	table = data->table;
	i = 0;
	while (i < nb)
	{
		if (PH_DEBUG)
			printf("INFO: init data->table[%d] philo[%d]\n", i, i+1);
		table[get_index(i, nb)].next = &table[get_index(i + 1, nb)].fork;
		table[get_index(i, nb)].num = i + 1;
		table[get_index(i, nb)].data = data;
		table[get_index(i, nb)].time_die = data->time_die;
		table[get_index(i, nb)].time_eat = data->time_eat;
		table[get_index(i, nb)].time_sleep = data->time_sleep;
		table[get_index(i, nb)].nb_must_eat = data->nb_must_eat;
		i++;
	}
	//TODO REMOVE DEBUG
	for (int i = 0; i < data->nb_philo; i++)
	{
		printf("[%p]->[%p]\n", &table[i].fork, table[i].next);
	}
}

/**
 * @brief Will set all the memory block of a struct to `0` bit.
 */
static void	struct_to_null(void *data, int size)
{
	memset((char *)data, 0, size);
}

/**
 * @brief //TODO check special case like `nb_philo` = `0`.
 */
void	init_data(int ac, char **av, t_data *data)
{
	struct_to_null(data, sizeof(t_data));
	data->nb_philo = ft_atoi(av[0]);
	if (data->nb_philo < 1)
		philo_exit(EXIT_FAILURE, "need at least one philosopher\n", data);
	data->time_die = ft_atoi(av[1]);
	data->time_eat = ft_atoi(av[2]);
	data->time_sleep = ft_atoi(av[3]);
	if (ac == 5)
		data->nb_must_eat = ft_atoi(av[4]);
	if (pthread_mutex_init(&data->stdout_print, NULL))
		philo_exit(EXIT_FAILURE, "pthread_mutex_init data->stdout_print fail !",
			data);
	//TODO make behaviour for the `0` case
	if (PH_DEBUG)
	{
		printf("nb_philo    [%lu]\ntime_die    [%lu]\n"
			"time_sleep  [%lu]\nnb_must_eat [%lu]\n",
			data->nb_philo, data->time_die, data->time_sleep,
			data->nb_must_eat);
	}
	philo_data_constructor(data->nb_philo, data);
	mutex_init(data);
}
