/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_run.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:26:33 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/15 17:06:13 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ph_debug.h"
#include <stdlib.h>
#include <stdio.h>

void	*philo_routine(void *this);

static int	create_thread(t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, &philo_routine, philo))
	{
		philo_exit(EXIT_FAILURE, "phtread_create fail !", philo->data);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	luncher(t_data *data, int odd)
{
	int	i;
	i = 0;
	while (i < data->nb_philo)
	{
		if ((i % 2) == odd)
			if (create_thread(&data->table[i]))
				return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	run(t_data *data)
{
	int i;

	if (luncher(data, -1) || luncher(data, 0))
	{
		philo_exit(EXIT_FAILURE, "create-thread fail !\n", data);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < data->nb_philo)//TODO check if we use join or detach thread
	{
		if (pthread_join(data->table[i].thread, NULL))
		{
			philo_exit(EXIT_FAILURE, "pthread_join fail !\n", data);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

//TODO fix
/**
Error: pthread_join fail !
=================================================================
==32851==ERROR: AddressSanitizer: attempting double-free on 0x61b000000780 in thread T0:
    #0 0x105ba02c6 in wrap_free+0xa6 (libclang_rt.asan_osx_dynamic.dylib:x86_64h+0x492c6)
    #1 0x105b42e2a in philo_free exit.c:37
    #2 0x105b42d7b in philo_exit exit.c:52
    #3 0x105b4155f in main 0_main.c:50
    #4 0x7fff7104ccc8 in start+0x0 (libdyld.dylib:x86_64+0x1acc8)

0x61b000000780 is located 0 bytes inside of 1496-byte region [0x61b000000780,0x61b000000d58)
freed by thread T0 here:
    #0 0x105ba02c6 in wrap_free+0xa6 (libclang_rt.asan_osx_dynamic.dylib:x86_64h+0x492c6)
    #1 0x105b42e2a in philo_free exit.c:37
    #2 0x105b42d7b in philo_exit exit.c:52
    #3 0x105b411a3 in run 3_run.c:58
    #4 0x105b41544 in main 0_main.c:48
    #5 0x7fff7104ccc8 in start+0x0 (libdyld.dylib:x86_64+0x1acc8)

previously allocated by thread T0 here:
    #0 0x105ba017d in wrap_malloc+0x9d (libclang_rt.asan_osx_dynamic.dylib:x86_64h+0x4917d)
    #1 0x105b42c84 in ft_calloc ft_calloc.c:20
    #2 0x105b41fe1 in philo_data_constructor 2_init_data.c:61
    #3 0x105b41f71 in init_data 2_init_data.c:133
    #4 0x105b41532 in main 0_main.c:48
    #5 0x7fff7104ccc8 in start+0x0 (libdyld.dylib:x86_64+0x1acc8)

SUMMARY: AddressSanitizer: double-free (libclang_rt.asan_osx_dynamic.dylib:x86_64h+0x492c6) in wrap_free+0xa6
==32851==ABORTING
[1]    32851 abort      ./philo 11 0 0 0
 */