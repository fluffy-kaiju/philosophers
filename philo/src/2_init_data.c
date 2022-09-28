/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:04:38 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/28 15:19:39 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ph_debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int		ft_atoi_strict(const char *str, int *ptr);
void	*ft_calloc(size_t size);

static int	mutex_init(t_data *data)
{
	int		x;

	x = 0;
	while (x < data->nb_philo)
	{
		if (PH_DEBUG)
			printf("INFO: init mutext for t_philo [%d]\n", x);
		if (pthread_mutex_init(&data->table[x].fork, NULL))
		{
			ph_exit_msg(EXIT_FAILURE, PH_MUTALLOC);
			return (EXIT_FAILURE);
		}
		if (pthread_mutex_init(&data->table[x].start, NULL))
		{
			ph_exit_msg(EXIT_FAILURE, PH_MUTALLOC);
			return (EXIT_FAILURE);
		}
		x++;
	}
	return (EXIT_SUCCESS);
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
static int	philo_data_constructor(int nb, t_data *data)
{
	int				i;
	t_philo			*table;
	long			time;
	struct timeval	t;

	time = gettime(&t);
	data->table = ft_calloc(sizeof(t_philo) * nb);
	if (!data->table)
	{
		ph_exit_msg(EXIT_FAILURE, "data->table alloc fail.\n");
		return (EXIT_FAILURE);
	}
	table = data->table;
	i = 0;
	while (i < nb)
	{
		if (PH_DEBUG)
			printf("INFO: init data->table[%d] philo[%d]\n", i, i+1);
		table[get_index(i, nb)].next = &table[get_index(i + 1, nb)].fork;
		table[get_index(i, nb)].num = i + 1;
		table[get_index(i, nb)].data = data;
		table[get_index(i, nb)].time_start = time + 2000;
		table[get_index(i, nb)].time_die = data->time_die;
		table[get_index(i, nb)].time_eat = data->time_eat;
		table[get_index(i, nb)].time_sleep = data->time_sleep;
		table[get_index(i, nb)].nb_must_eat = data->nb_must_eat;
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Use ft_atoi_strict to convert, will return a error if one value will
 *        overflow `int`.
 */
int	argtoint(int ac, char **av, t_data *data)
{
	int	overflow;

	overflow = ft_atoi_strict(av[0], &data->nb_philo);
	overflow += ft_atoi_strict(av[1], &data->time_die);
	overflow += ft_atoi_strict(av[2], &data->time_eat);
	overflow += ft_atoi_strict(av[3], &data->time_sleep);
	if (ac == 5)
		overflow += ft_atoi_strict(av[4], &data->nb_must_eat);
	if (overflow)
	{
		ph_exit_msg(EXIT_FAILURE, PH_ORVERFLO);
		return (EXIT_FAILURE);
	}
	if (data->nb_philo < 1)
	{
		ph_exit_msg(EXIT_FAILURE, PH_ONEPHILO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief
 */
int	init_data(int ac, char **av, t_data *data)
{
	if (argtoint(ac, av, data))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&data->data_rw, NULL))
	{
		ph_exit_msg(EXIT_FAILURE, PH_MUTALLOC);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&data->print_stdout, NULL))
	{
		ph_exit_msg(EXIT_FAILURE, PH_MUTALLOC);
		return (EXIT_FAILURE);
	}
	if (PH_DEBUG)
	{
		printf("nb_philo    [%d]\ntime_die    [%d]\n"
			"time_sleep  [%d]\ntime_eat [%d]\nnb_must_eat [%d]\n",
			data->nb_philo, data->time_die, data->time_sleep, data->time_eat,
			data->nb_must_eat);
	}
	if (philo_data_constructor(data->nb_philo, data))
		return (EXIT_FAILURE);
	if (mutex_init(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
