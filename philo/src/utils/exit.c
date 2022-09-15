/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:41:52 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/15 12:01:44 by mahadad          ###   ########.fr       */
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
 */
static void	philo_free(t_data *data)
{
	(void)data;
	free (data->table);
	//free all alloc in t_data;
}

/**
 * @brief 
 * 
 * @param error 
 * @param msg 
 * @param data 
 */
void	philo_exit(int error, char *msg, t_data *data)
{
	//TODO join all init thread
	//TODO destroy all mutex
	philo_free(data);
	if (error)
	{
		if (msg)
		{
			write(STDERR_FILENO, "Error: ", 8);
			write(STDERR_FILENO, msg, strlen_protect(msg));
		}
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}