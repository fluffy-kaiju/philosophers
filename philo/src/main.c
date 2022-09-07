/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:58:39 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/07 12:04:31 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Warn, is only a exemple, the code is note safe !
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include "philo.h"

void	check_pthread(int error)
{
	if (error)
	{
		printf("Error pthread_mutex_lock : %s\n", strerror(error));
		exit (EXIT_FAILURE);
	}
}

void	philo_link_contructor(int nb, t_data *data)
{
	(void)nb;
	(void)data;
	//todo alloc all philo
}

void	struct_init_to_null(t_data *data)
{
	memset(data, 0, sizeof(t_data));
}

void	check_arg(int ac, char **av, t_data *data)
{
	if (ac < 4 || ac > 5)
		philo_exit(EXIT_FAILURE, PH_BADARG1 PH_BADARG2, data);
	(void)av;
}

int	main(int ac, char **av)
{
	t_data	data;

	//TODO check arg
	check_arg(ac, av, &data);
	struct_init_to_null(&data);
	//TODO store all arg in t_data;
	philo_link_contructor(2, &data);
	philo_exit(EXIT_SUCCESS, NULL, &data);
}
