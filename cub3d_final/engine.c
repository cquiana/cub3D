/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:30:14 by cquiana           #+#    #+#             */
/*   Updated: 2020/11/07 00:59:53 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	paint_bg(int x, int y, t_game *game)
{
	int		color;
	int		j;
	int		height;

	height = game->scr.h / 2;
	if (y == 0)
		color = game->scr.ceiling_col;
	else
		color = game->scr.floor_col;
	while (x < game->scr.w)
	{
		j = y;
		while (j < y + height)
		{
			my_pixel_put(&game->img, x, j, color);
			j++;
		}
		x++;
	}
}

static void	plr_movment(t_game *game)
{
	double	x;
	double	y;
	double	step;
	double	side;

	side = game->plr.side ? game->plr.go_dir * M_PI_2 : 0;
	step = game->plr.go_dir * game->plr.go_speed;
	if (game->plr.side && step < 0)
		step = -step;
	game->plr.pov += game->plr.turn * game->plr.turn_speed;
	x = game->plr.x + cos(game->plr.pov - side) * step * 2;
	y = game->plr.y + sin(game->plr.pov - side) * step * 2;
	if (!is_wall(x, y, game) && !is_sprite(x, y, game))
	{
		game->plr.x = game->plr.x + cos(game->plr.pov - side) * step;
		game->plr.y = game->plr.y + sin(game->plr.pov - side) * step;
	}
	game->plr.turn = 0;
	game->plr.go_dir = 0;
	game->plr.side = 0;
}

int			draw_scene(t_game *game)
{
	int		h;

	h = 0;
	mlx_do_sync(game->scr.mlx);
	paint_bg(0, h, game);
	h = game->scr.h / 2;
	paint_bg(0, h, game);
	plr_movment(game);
	raycasting(game);
	create_wall(game);
	create_sprite(game);
	return (1);
}
