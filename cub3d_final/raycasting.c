/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:37:42 by cquiana           #+#    #+#             */
/*   Updated: 2020/11/07 01:02:06 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_raytools	check_hor_hit(t_game *game, t_rays *ray)
{
	t_raytools hor;

	hor.dist = INT32_MAX;
	hor.y = floor(game->plr.y / game->map.scale) * game->map.scale;
	hor.y += ray->down ? game->map.scale : 0;
	hor.x = game->plr.x + (hor.y - game->plr.y) / tan(ray->ang);
	if (hor.y < 0 || hor.y > game->map.map_h * game->map.scale)
		return (hor);
	hor.step_y = game->map.scale;
	hor.step_y *= ray->up ? -1 : 1;
	hor.step_x = game->map.scale / tan(ray->ang);
	hor.step_x *= (ray->left && hor.step_x > 0) ? -1 : 1;
	hor.step_x *= (ray->right && hor.step_x < 0) ? -1 : 1;
	while (hor.x >= 0 && hor.x < game->map.scale * game->map.map_w && \
				hor.y >= 0 && hor.y < game->map.scale * game->map.map_h)
	{
		if (is_wall(hor.x, hor.y - (ray->up ? 1 : 0), game))
		{
			hor.dist = calc_dist(game->plr.x, hor.x, game->plr.y, hor.y);
			return (hor);
		}
		hor.x += hor.step_x;
		hor.y += hor.step_y;
	}
	return (hor);
}

t_raytools	check_vert_hit(t_game *game, t_rays *ray)
{
	t_raytools vert;

	vert.dist = INT32_MAX;
	vert.x = floor(game->plr.x / game->map.scale) * game->map.scale;
	vert.x += ray->right ? game->map.scale : 0;
	vert.y = game->plr.y + (vert.x - game->plr.x) * tan(ray->ang);
	if (vert.y < 0 || vert.y > game->map.map_h * game->map.scale)
		return (vert);
	vert.step_x = game->map.scale;
	vert.step_x *= ray->left ? -1 : 1;
	vert.step_y = game->map.scale * tan(ray->ang);
	vert.step_y *= (ray->up && vert.step_y > 0) ? -1 : 1;
	vert.step_y *= (ray->down && vert.step_y < 0) ? -1 : 1;
	while (vert.x >= 0 && vert.x < game->map.scale * game->map.map_w && \
				vert.y >= 0 && vert.y < game->map.scale * game->map.map_h)
	{
		if (is_wall(vert.x - (ray->left ? 1 : 0), vert.y, game))
		{
			vert.dist = calc_dist(game->plr.x, vert.x, game->plr.y, vert.y);
			return (vert);
		}
		vert.x += vert.step_x;
		vert.y += vert.step_y;
	}
	return (vert);
}

void		check_side(t_game *game, double ang, int x)
{
	game->rays[x].down = ang > 0 && ang < M_PI;
	game->rays[x].up = !game->rays[x].down;
	game->rays[x].right = ang < M_PI_2 || ang > (3 * M_PI_2);
	game->rays[x].left = !game->rays[x].right;
}

void		raycasting(t_game *game)
{
	int			x;
	double		ang;
	t_raytools	hor;
	t_raytools	vert;

	x = 0;
	ang = game->plr.pov - FOV / 2;
	while (x < game->scr.w)
	{
		ang = fix_angle(ang);
		game->rays[x].ang = ang;
		check_side(game, ang, x);
		vert = check_vert_hit(game, &game->rays[x]);
		hor = check_hor_hit(game, &game->rays[x]);
		game->rays[x].dist = vert.dist > hor.dist ? hor.dist : vert.dist;
		game->rays[x].hit_x = vert.dist > hor.dist ? hor.x : vert.x;
		game->rays[x].hit_y = vert.dist > hor.dist ? hor.y : vert.y;
		game->rays[x].vert = vert.dist > hor.dist ? 0 : 1;
		ang += FOV / game->scr.w;
		x++;
	}
}
