/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:01:22 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/13 15:16:42 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ph_debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	ft_atoi(const char *str);

/**
 * @brief Create link list for all philo.
 */
static void	philo_data_constructor(int nb, t_data *data)
{
	t_philo	*tmp;

	//NOTE if the code arrived here `nb` need to not be `0`.
	// nb--;
	data->table = malloc(sizeof(t_philo));
	if (!data->table)
		philo_exit(EXIT_FAILURE, "t_philo alloc fail.\n", data);
	tmp = data->table;
	if (PH_DEBUG)
		printf("INFO: alloc t_philo [%d][%p]\n", nb, tmp);
	while (nb > 0)
	{
		tmp->num = nb;
		if (PH_DEBUG)
			printf("INFO: alloc t_philo [%d][%p]->next[%p]\n", nb, tmp,
				tmp->next);
		tmp->next = malloc(sizeof(t_philo));
		if (!tmp->next)
			philo_exit(EXIT_FAILURE, "t_philo alloc fail.\n", data);
		tmp = tmp->next;
		nb--;
	}
	tmp->next = data->table;
}

/**
 * @brief Will set all the memory block of a struct to `0` bit.
 */
static void	struct_to_null(void *data, int size)
{
	memset((char *)data, 0, size);
}

int	ft_isdigit(int c);

/**
 * @brief Check if all input are positif number, if not will exit with a error
 *        message.
 */
static void	arg_check(int ac, char **av, t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < ac)
	{
		while (av[x][y])
		{
			if (!ft_isdigit(av[x][y]))
				philo_exit(EXIT_FAILURE, "non digit character or "
					"negative number in arg.\n", data);
			y++;
		}
		y = 0;
		x++;
	}
}

/**
 * @brief //TODO check special case like `nb_philo` = `0`.
 */
static void	set_data(int ac, char **av, t_data *data)
{
	struct_to_null(data, sizeof(t_data));
	data->nb_philo = ft_atoi(av[0]);
	data->time_die = ft_atoi(av[1]);
	data->time_eat = ft_atoi(av[2]);
	data->time_sleep = ft_atoi(av[3]);
	if (ac == 5)
		data->nb_must_eat = ft_atoi(av[4]);
	//TODO make behaviour for the `0` case
	if (PH_DEBUG)
	{
		printf("nb_philo    [%d]\ntime_die    [%d]\n"
			"time_sleep  [%d]\nnb_must_eat [%d]\n",
			data->nb_philo, data->time_die, data->time_sleep,
			data->nb_must_eat);
	}
}

/**
 * @brief Will skip the first `ac` and `av` arg. Check if the args are only
 *        digit character and populate the data struct.
 */
void	arg_init(int ac, char **av, t_data *data)
{
	ac--;
	av++;
	if (!(ac == 4 || ac == 5))
		philo_exit(EXIT_FAILURE, PH_BADARG1 PH_BADARG2, data);
	arg_check(ac, av, data);
	set_data(ac, av, data);
	philo_data_constructor(data->nb_philo, data);
}
