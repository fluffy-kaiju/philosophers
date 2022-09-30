/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:41:52 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/30 11:38:17 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
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

void	philo_free(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->data_rw);
	pthread_mutex_destroy(&data->print_stdout);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->table[i].fork);
		i++;
	}
	free (data->table);
}
