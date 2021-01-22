/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:24:07 by cquiana           #+#    #+#             */
/*   Updated: 2020/11/07 00:59:39 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	close_button(t_game *game)
{
	close_game("Game over", game);
	return (0);
}

int			key_press(int key, t_game *game)
{
	if (key == 53)
		close_button(game);
	if (key == 0)
	{
		game->plr.go_dir = 1;
		game->plr.side = 1;
	}
	else if (key == 2)
	{
		game->plr.go_dir = -1;
		game->plr.side = 1;
	}
	else if (key == 13 || key == 126)
		game->plr.go_dir = 1;
	else if (key == 1 || key == 125)
		game->plr.go_dir = -1;
	else if (key == 123)
		game->plr.turn = -1;
	else if (key == 124)
		game->plr.turn = 1;
	draw_scene(game);
	mlx_put_image_to_window(game->scr.mlx, game->scr.win, \
				game->img.img, 0, 0);
	return (1);
}

int			key_release(int key, t_game *game)
{
	if (key == 0)
	{
		game->plr.go_dir = 0;
		game->plr.side = 0;
	}
	else if (key == 2)
	{
		game->plr.go_dir = 0;
		game->plr.side = 0;
	}
	else if (key == 13)
		game->plr.go_dir = 0;
	else if (key == 1)
		game->plr.go_dir = 0;
	else if (key == 123)
		game->plr.turn = 0;
	else if (key == 124)
		game->plr.turn = 0;
	mlx_put_image_to_window(game->scr.mlx, game->scr.win, \
				game->img.img, 0, 0);
	return (1);
}

int			main(int ac, char **av)
{
	t_game	game;
	int		save;

	save = check_arg(ac, av, &game);
	init_game(&game, av[1], save);
	mlx_hook(game.scr.win, 2, 0, key_press, &game);
	mlx_hook(game.scr.win, 17, 0, close_button, &game);
	mlx_hook(game.scr.win, 3, 0, key_release, &game);
	mlx_loop(game.scr.mlx);
	return (0);
}
