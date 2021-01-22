/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 08:11:20 by cquiana           #+#    #+#             */
/*   Updated: 2020/05/24 22:42:12 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_wrdcnt(char const *s, char c)
{
	int	i;
	int	wcount;

	i = 0;
	wcount = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			wcount++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (wcount);
}

int		ft_wlen(char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] != '\0' && s[i] == c)
		i++;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

void	*ft_freearray(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**arr;

	if (!s || (!(arr = malloc(sizeof(char*) * (ft_wrdcnt(s, c) + 1)))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			if (!(arr[j] = malloc(sizeof(char) * (ft_wlen(&s[i], c) + 1))))
				return (ft_freearray(arr));
			k = 0;
			while (s[i] != '\0' && s[i] != c)
				arr[j][k++] = s[i++];
			arr[j++][k] = '\0';
		}
	}
	arr[j] = NULL;
	return (arr);
}
