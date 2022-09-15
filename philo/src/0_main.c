/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:58:39 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/15 14:25:22 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Warn, is only a exemple, the code is note safe !
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include "philo.h"

void	parser(int ac, char **av, t_data *data);
void	init_data(int ac, char **av, t_data *data);
void	run(t_data *data);

/**
 * Step 1:
 *        Will init all data structure with `parser`. First check if all
 *        input are only positif numeric then storing in a linked list.
 * Step 2:
 *        Init all the mutex for each `t_philo->fork` and `t_philo->thread`.
 */
int	main(int ac, char **av)
{
	t_data	data;

	ac--;
	av++;
	parser(ac, av, &data);
	init_data(ac, av, &data);
	run(&data);
	philo_exit(EXIT_SUCCESS, NULL, &data);
}
