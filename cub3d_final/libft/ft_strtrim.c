/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 20:11:27 by cquiana           #+#    #+#             */
/*   Updated: 2020/05/24 12:55:48 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		len;
	int		i;
	char	*newstr;

	if (!s1 || !set)
		return (ft_strdup(""));
	start = 0;
	len = ft_strlen(s1);
	while (s1[start] != '\0' && ft_strchr(set, s1[start]))
		start++;
	if (start < len)
		while (len > start && ft_strchr(set, s1[len - 1]))
			len--;
	if (!(newstr = malloc(sizeof(char) * (len - start + 1))))
		return (NULL);
	i = 0;
	while (start < len)
	{
		newstr[i] = s1[start];
		i++;
		start++;
	}
	newstr[i] = '\0';
	return (newstr);
}
