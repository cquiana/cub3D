/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:43:04 by cquiana           #+#    #+#             */
/*   Updated: 2020/11/07 01:02:22 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	make_sprites(t_game *game)
{
	int		i;

	i = 0;
	while (i < game->map.spr_count)
	{
		game->sprite[i].ang = atan2(game->sprite[i].y - game->plr.y, \
							game->sprite[i].x - game->plr.x);
		while (game->sprite[i].ang - game->plr.pov > M_PI)
			game->sprite[i].ang -= 2.0 * M_PI;
		while (game->sprite[i].ang - game->plr.pov < -M_PI)
			game->sprite[i].ang += 2.0 * M_PI;
		game->sprite[i].ang -= game->plr.pov;
		game->sprite[i].dist = calc_dist(game->plr.x, game->sprite[i].x, \
					game->plr.y, game->sprite[i].y);
		game->sprite[i].size = (game->map.scale / game->sprite[i].dist) * \
					(game->scr.w / 2) / tan(FOV / 2);
		game->sprite[i].s_y = game->scr.h / 2 - game->sprite[i].size / 2;
		game->sprite[i].s_x = game->scr.w / (FOV * (180 / M_PI)) * \
					((180 / M_PI * game->sprite[i].ang) + 30) - \
						game->sprite[i].size / 2;
		game->sprite[i].step = game->txtr.spr.h / game->sprite[i].size;
		game->sprite[i].pos = 0;
		i++;
	}
}

static void	sort_sprites(t_game *game)
{
	int			i;
	int			j;
	t_sprite	spr;

	i = 0;
	while (i < game->map.spr_count)
	{
		j = 0;
		while (j < game->map.spr_count - 1)
		{
			if (game->sprite[j].dist < game->sprite[j + 1].dist)
			{
				spr = game->sprite[j];
				game->sprite[j] = game->sprite[j + 1];
				game->sprite[j + 1] = spr;
			}
			j++;
		}
		i++;
	}
}

static void	paint_sprites(t_sprite spr, t_game *game)
{
	int		i;
	int		j;
	int		yt;
	int		xt;

	i = -1;
	while (++i < spr.size)
	{
		if (spr.s_x + i > game->scr.w || spr.s_x + i < 0 || \
				game->rays[i + (int)spr.s_x].dist < spr.dist)
			continue;
		xt = i / spr.size * game->txtr.spr.w;
		spr.pos = 0;
		j = -1;
		while (++j < spr.size)
		{
			yt = (unsigned int)spr.pos & (game->txtr.spr.h - 1);
			spr.clr = (unsigned int *)(game->txtr.spr.addr + \
				(yt * game->txtr.spr.line_len + xt * (game->txtr.spr.bpp / 8)));
			spr.pos += spr.step;
			if (spr.s_y + j > game->scr.h || spr.s_y + i < 0 || *spr.clr == 0x0)
				continue;
			my_pixel_put(&game->img, spr.s_x + i, spr.s_y + j, *spr.clr);
		}
	}
}

void		create_sprite(t_game *game)
{
	int		i;

	i = 0;
	make_sprites(game);
	sort_sprites(game);
	while (i < game->map.spr_count)
	{
		paint_sprites(game->sprite[i], game);
		i++;
	}
}
