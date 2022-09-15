/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:57:53 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/15 15:47:48 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_isdigit(int c);

/**
 * @brief Same as ft_atoi but ft_atoi_strict will return non 0 if a overflow
 * occur.
 */
int	ft_atoi_strict(const char *str, int *ptr)
{
	unsigned long	nbr;
	unsigned long	cutoff;
	int				cutlim;
	int				isneg;

	nbr = 0;
	isneg = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	isneg = (*str == '-');
	str += (isneg || *str == '+');
	cutoff = (unsigned long)(INT_MAX / 10);
	cutlim = (int)(INT_MAX % 10);
	while (ft_isdigit((int)*str))
	{
		if (nbr > cutoff || (nbr == cutoff && (int)(*str - '0') > cutlim))
			return (1);
		nbr *= 10;
		nbr += (*str - '0');
		str++;
	}
	ptr = (int []){nbr, -nbr}[isneg];
	return (0);
}
