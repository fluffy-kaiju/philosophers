/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:01:22 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/07 13:50:38 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ph_debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

int	ft_isdigit(int c);

void	arg_check(int ac, char **av, t_data *data)
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
				philo_exit(EXIT_FAILURE, "non digit character in arg.\n",
					data);
			y++;
		}
		y = 0;
		x++;
	}
}

int	ft_atoi(const char *str);

/**
 * @brief Will skip the first `ac` and `av` arg. Check if the args are only
 *        digit character and populate the data struct.
 */
void	arg_init(int ac, char **av, t_data *data)
{
	ac--;
	av++;
	printf("[[%d\n", ac);
	if (ac != 4 || ac != 5)//TODO FIX 
		philo_exit(EXIT_FAILURE, PH_BADARG1 PH_BADARG2, data);
	arg_check(ac, av, data);
	struct_init_to_null(data);
/**
AddressSanitizer:DEADLYSIGNAL
=================================================================
==4390==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x0001000bdd84 bp 0x7ffeefb44540 sp 0x7ffeefb443a0 T0)
==4390==The signal is caused by a READ memory access.
==4390==Hint: address points to the zero page.
    #0 0x1000bdd84 in ft_atoi utils.c:85
    #1 0x1000be8fa in arg_init parser.c:75
    #2 0x1000bd971 in main main.c:40
    #3 0x7fff67028cc8 in start+0x0 (libdyld.dylib:x86_64+0x1acc8)

==4390==Register values:
rax = 0x0000000000000000  rbx = 0x00007ffeefb443e0  rcx = 0x0000100000000000  rdx = 0x0000100000000000  
rdi = 0x0000000000000000  rsi = 0xf3f3f300f1f1f100  rbp = 0x00007ffeefb44540  rsp = 0x00007ffeefb443a0  
 r8 = 0x0000000000013000   r9 = 0x0000000000000000  r10 = 0x000000010ed46420  r11 = 0x00000001001194c0  
r12 = 0x0000000000000000  r13 = 0x0000000000000000  r14 = 0x0000000000000000  r15 = 0x0000000000000000  
AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV utils.c:85 in ft_atoi
==4390==ABORTING
[1]    4390 abort      ./philo 1 2 3 4
 */

	data->nb_philo = ft_atoi(av[0]);
	data->time_die = ft_atoi(av[1]);
	data->time_eat = ft_atoi(av[2]);
	data->time_sleep = ft_atoi(av[3]);
	if (ac == 4)
		data->nb_must_eat = ft_atoi(av[4]);
	if (PH_DEBUG)
	{
		printf("nb_philo    [%d]\ntime_die    [%d]\n"
			"time_sleep  [%d]\nnb_must_eat [%d]\n",
			data->nb_philo, data->time_die, data->time_sleep,
			data->nb_must_eat);
	}
}
