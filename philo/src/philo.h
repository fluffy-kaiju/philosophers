/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:21:37 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/15 13:35:03 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define PH_BADARG1 "usage: anumber_of_philosophers time_to_die time_to_eat tim"
# define PH_BADARG2 "e_to_sleep [number_of_times_each_philosopher_must_eat]\n"

typedef struct s_data t_data;
typedef struct s_philo
{
	pthread_t			thread;
	int					num;
	pthread_mutex_t		fork;
	int					last_meal;
	int					nb_eat;
	pthread_mutex_t		*next;
	t_data				*data;
}				t_philo;

typedef struct s_data
{
	t_philo			*table;
	long				nb_philo;
	long				time_die;
	long				time_eat;
	long				time_sleep;
	long				nb_must_eat;
	pthread_mutex_t	stdout_print;
}				t_data;

void	philo_exit(int error, char *msg, t_data *data);

#endif /* PHILO_H */
