/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 19:12:15 by cquiana           #+#    #+#             */
/*   Updated: 2020/05/23 20:44:34 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	*mem;

	if (!(mem = (size_t *)malloc(count * size)))
		return (NULL);
	ft_memset(mem, '\0', count * size);
	return (mem);
}
