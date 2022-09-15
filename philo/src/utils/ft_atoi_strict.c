/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:57:53 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/15 16:37:05 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_isdigit(int c);

static int overflow_check(unsigned long nbr, int next_char, int isneg)
{
	unsigned long	cutoff;
	int				cutlim;

	if (isneg)
	{
		cutoff = -(unsigned long)(INT_MIN / 10);
		cutlim = -(int)(INT_MIN % 10);
	}
	else
	{
		cutoff = (unsigned long)(INT_MAX / 10);
		cutlim = (int)(INT_MAX % 10);
	}
	printf("cutlim: %d\ncutoff: %lu\n", cutlim, cutoff);
	if (nbr > cutoff || (nbr == cutoff && (int)(next_char - '0') > cutlim))
		return (1);
	return (0);
}

/**
 * @brief Same as ft_atoi but ft_atoi_strict will return non 0 if a overflow
 * occur.
 */
int	ft_atoi_strict(const char *str, int *ptr)
{
	unsigned long	nbr;
	int				isneg;

	nbr = 0;
	isneg = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	isneg = (*str == '-');
	str += (isneg || *str == '+');
	while (ft_isdigit((int)*str))
	{
		if (overflow_check(nbr, *str, isneg))
			return (1);
		nbr *= 10;
		nbr += (*str - '0');
		str++;
	}
	*ptr = (int []){nbr, -nbr}[isneg];
	return (0);
}
