/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:57:53 by mahadad           #+#    #+#             */
/*   Updated: 2022/09/07 13:21:13 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

/*
*  SYNOPSIS
*       #include <ctype.h>
*
*       int
*       isdigit(int c);
*
*       int
*       isnumber(int c);
*
*  DESCRIPTION
*       The isdigit() function tests for a decimal digit character.  Regardless
*       of locale, this includes the following characters only:
*
*       ``0''         ``1''         ``2''         ``3''         ``4''
*       ``5''         ``6''         ``7''         ``8''         ``9''
*
*       The isnumber() function behaves similarly to isdigit(), but may recognize
*       additional characters, depending on the current locale setting.
*
*       The value of the argument must be representable as an unsigned char or
*       the value of EOF.
*
*  RETURN VALUES
*       The isdigit() and isnumber() functions return zero if the character tests
*       false and return non-zero if the character tests true.
*/

int	ft_isdigit(int c)
{
	return ((c >= '0') && (c <= '9'));
}

/*
* SYNOPSIS
*   #include <stdlib.h>
* 
*   int
*   atoi(const char *str);
* 
* DESCRIPTION
*   The atoi() function converts the initial portion of the string pointed to
*   by str to int representation.
* 
*   It is equivalent to:
* 
*     (int)strtol(str, (char **)NULL, 10);
* 
*   While the atoi() function uses the current locale, the atoi_l() function
*   may be passed a locale directly. See xlocale(3) for more information.
* 
* IMPLEMENTATION NOTES
*   The atoi() and atoi_l() functions are thread-safe and async-cancel-safe.
* 
*   The strtol() and strtol_l() functions are recommended instead of atoi()
*   and atoi_l() functions, especially in new code.
* 
* ERRORS
*   The function atoi() need not affect the value of errno on an error.
*/

int	ft_atoi(const char *str)
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
	cutoff = (unsigned long)(LONG_MAX / 10);
	cutlim = (int)(LONG_MAX % 10);
	while (ft_isdigit((int)*str))
	{
		if (nbr > cutoff || (nbr == cutoff && (int)(*str - '0') > cutlim))
			return (-!isneg);
		nbr *= 10;
		nbr += (*str - '0');
		str++;
	}
	return ((int []){nbr, -nbr}[isneg]);
}
