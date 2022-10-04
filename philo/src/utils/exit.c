/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:41:52 by mahadad           #+#    #+#             */
/*   Updated: 2022/10/04 12:55:53 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_debug.h"
#include "philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * @brief Strlen but dont crash with a NULL pointer.
 */
static size_t	strlen_protect(const char *s)
{
	char	*start;

	start = (char *)s;
	while (s && *s)
		s++;
	return ((size_t)(s - start));
}

/**
 * @brief 
 * 
 * @param error 
 * @param msg 
 * @param data 
 */
void	ph_exit_msg(int error, const char *msg)
{
	if (error)
	{
		if (msg)
		{
			write(STDERR_FILENO, "Error: ", 8);
			write(STDERR_FILENO, msg, strlen_protect(msg));
		}
	}
}

static int	philo_join(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->nb_philo)
	{
		if (PH_DEBUG)
			printf("INFO: try to join philo[%d] thread\n", x + 1);
		if (pthread_join(data->table[x].thread, NULL))
			ph_exit_msg(EXIT_FAILURE, "pthread_join fail !\n");
		x++;
	}
	return (EXIT_SUCCESS);
}

void	philo_free(t_data *data)
{
	int	i;

	if (philo_join(data))
		return ;
	pthread_mutex_destroy(&data->data_rw);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_destroy(&data->table[i].fork))
			write(STDERR_FILENO, "Error: fail to mutex_destroy\n", 30);
		i++;
	}
	free (data->table);
}
