/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:00:29 by cquiana           #+#    #+#             */
/*   Updated: 2020/11/07 01:02:34 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_comma(char *conf)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (conf[i])
	{
		if (conf[i] == ',')
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

int		is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int		is_empty(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}
