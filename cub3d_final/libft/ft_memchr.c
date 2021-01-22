/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 17:45:03 by cquiana           #+#    #+#             */
/*   Updated: 2020/05/18 19:02:41 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmps;
	unsigned char	sym;

	i = 0;
	tmps = (unsigned char*)str;
	sym = (unsigned char)c;
	while (i < n)
	{
		if (tmps[i] == sym)
			return (&tmps[i]);
		i++;
	}
	return (NULL);
}
