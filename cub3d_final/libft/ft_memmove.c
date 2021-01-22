/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 15:55:39 by cquiana           #+#    #+#             */
/*   Updated: 2020/05/24 12:53:59 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*tmpd;
	unsigned char	*tmps;

	if (len == 0)
		return (dest);
	tmpd = (unsigned char*)dest;
	tmps = (unsigned char*)src;
	if (tmpd > tmps)
	{
		while (len > 0)
		{
			tmpd[len - 1] = tmps[len - 1];
			len--;
		}
	}
	else
		ft_memcpy(dest, src, len);
	return (dest);
}
