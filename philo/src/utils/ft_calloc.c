/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:43:23 by mahadad           #+#    #+#             */
/*   Updated: 2022/10/04 12:09:19 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t size)
{
	void	*mem;
	size_t	i;

	mem = (void *)malloc(size);
	if (!mem)
		return (NULL);
	i = 0;
	while (i < size)
	{
		((char *)mem)[i] = 0;
		i++;
	}
	return (mem);
}
