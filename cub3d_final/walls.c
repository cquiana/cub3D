/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:39:18 by cquiana           #+#    #+#             */
/*   Updated: 2020/11/05 14:30:38 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img		select_text(t_game *game, t_rays ray, int *flag)
{
	*flag = 0;
	if (ray.vert == 1)
	{
		if (ray.right)
			return (game->txtr.west);
		else
		{
			*flag = 1;
			return (game->txtr.east);
		}
	}
	else
	{
		if (ray.up)
			return (game->txtr.north);
		else
		{
			*flag = 1;
			return (game->txtr.south);
		}
	}
}

static t_raytools	paint_wall(t_game *game, t_img text, int x)
{
	t_raytools	col;

	col.plane = (game->scr.w / 2.0) / tan(FOV / 2);
	game->rays[x].dist = game->rays[x].dist == 0 ? 1 : game->rays[x].dist;
	col.dist = game->rays[x].dist * cos(game->rays[x].ang - game->plr.pov);
	col.height = (game->map.scale / col.dist) * col.plane;
	col.start = game->scr.h / 2 - col.height / 2;
	if (game->rays[x].vert == 1)
		col.off_x = remainder(game->rays[x].hit_y, game->map.scale) / \
			game->map.scale * text.w;
	else
		col.off_x = remainder(game->rays[x].hit_x, game->map.scale) / \
		game->map.scale * text.w;
	col.off_x = col.off_x & (unsigned int)(text.h - 1);
	col.step = text.h / col.height;
	col.pos = 0;
	col.y = (int)col.start;
	return (col);
}

void				create_wall(t_game *game)
{
	t_img		text;
	t_raytools	col;
	int			x;
	int			flag;

	x = 0;
	while (x < game->scr.w)
	{
		text = select_text(game, game->rays[x], &flag);
		col = paint_wall(game, text, x);
		while (col.y < col.start + col.height)
		{
			col.off_y = (unsigned int)col.pos & ((unsigned int)text.h - 1);
			col.color = !flag ? text.addr + (col.off_y * text.line_len + \
					col.off_x * (text.bpp / 8)) : \
						text.addr + (col.off_y * text.line_len + \
								((64 - col.off_x) % 64) * (text.bpp / 8));
			col.pos += col.step;
			if (col.y >= 0 && col.y < game->scr.h && x >= 0 && \
					x < game->scr.w)
				my_pixel_put(&game->img, x, col.y, *(unsigned int *)col.color);
			col.y++;
		}
		x++;
	}
}
