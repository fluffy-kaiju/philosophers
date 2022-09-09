/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:58:39 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/09 14:48:48 by mahadad          ###   ########.fr       */
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

void	arg_init(int ac, char **av, t_data *data);
void	philo_link_contructor(int nb, t_data *data);

/**
 * Step 1:
 *        Will init all data structure with `arg_init`. First check if all
 *        input are only positif numeric then storing in a linked list.
 */
int	main(int ac, char **av)
{
	t_data	data;

	arg_init(ac, av, &data);
	//TODO store all arg in t_data;
	philo_link_contructor(2, &data);
	philo_exit(EXIT_SUCCESS, NULL, &data);
}
