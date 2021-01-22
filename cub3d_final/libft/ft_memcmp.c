/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 18:23:03 by cquiana           #+#    #+#             */
/*   Updated: 2020/05/18 18:52:14 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmps1;
	unsigned char	*tmps2;

	i = 0;
	tmps1 = (unsigned char*)s1;
	tmps2 = (unsigned char*)s2;
	if (n == 0)
		return (0);
	while ((tmps1[i] == tmps2[i]) && i + 1 < n)
		i++;
	return ((int)(tmps1[i] - tmps2[i]));
}
