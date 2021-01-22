/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:34:30 by cquiana           #+#    #+#             */
/*   Updated: 2020/11/07 01:01:59 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	fix_angle(double ang)
{
	ang = remainder(ang, (M_PI * 2));
	if (ang < 0)
		ang = (M_PI * 2) + ang;
	return (ang);
}

int		is_wall(double x, double y, t_game *game)
{
	int	xm;
	int	ym;

	if (x < 0 || x > game->map.scale * game->map.map_w || y < 0 || \
					y > game->map.scale * game->map.map_h)
		return (1);
	xm = (int)(x / game->map.scale);
	ym = (int)(y / game->map.scale);
	return (game->map.map[ym][xm] == '1');
}

int		is_sprite(double x, double y, t_game *game)
{
	int	xm;
	int	ym;

	if (x < 0 || x > game->map.scale * game->map.map_w || y < 0 || \
				y > game->map.scale * game->map.map_h)
		return (1);
	xm = (int)(x / game->map.scale);
	ym = (int)(y / game->map.scale);
	return (game->map.map[ym][xm] == '2');
}

double	calc_dist(double x1, double x2, double y1, double y2)
{
	double dist;

	dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return (dist);
}
