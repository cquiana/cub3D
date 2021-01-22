/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 23:02:13 by cquiana           #+#    #+#             */
/*   Updated: 2020/05/24 05:51:44 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmpd;
	unsigned char	*tmps;
	unsigned char	symbol;

	i = 0;
	tmpd = (unsigned char*)dest;
	tmps = (unsigned char*)src;
	symbol = (unsigned char)c;
	while (i < n)
	{
		tmpd[i] = tmps[i];
		if (tmpd[i] == symbol)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
