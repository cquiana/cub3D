/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:14:39 by cquiana           #+#    #+#             */
/*   Updated: 2020/11/07 10:07:28 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_checker(t_game *game, char **map)
{
	int		x;
	int		y;

	y = -1;
	while (map[++y] != NULL)
	{
		x = -1;
		while (map[y][++x] != '\0')
		{
			if (map[y][x] != '1' && map[y][x] != ' ' && map[y][x] != '\0')
			{
				if (x == 0 || x == game->map.map_w - 1)
					close_game("Error\nInvalid map", game);
				if (y == 0 || y == game->map.map_h - 1)
					close_game("Error\nInvalid map", game);
				if (x + 1 < game->map.map_w && map[y][x + 1] == ' ')
					close_game("Error\nInvalid map", game);
				if (map[y][x - 1] == ' ' || map[y - 1][x] == ' ')
					close_game("Error\nInvalid map", game);
				if (y + 1 < game->map.map_h && map[y + 1][x] == ' ')
					close_game("Error\nInvalid map", game);
			}
		}
	}
}

void	check_conf(t_game *game)
{
	if (game->plr.check <= 0)
		close_game("Error\nNot found player on map", game);
	map_checker(game, game->map.map);
}

void	validate_config(t_game *game)
{
	if (game->scr.w == -1 || game->scr.h == -1)
		close_game("Error\nNo resolution settings", game);
	if (game->txtr.north.img == NULL)
		close_game("Error\nNo north texture", game);
	if (game->txtr.south.img == NULL)
		close_game("Error\nNo south texture", game);
	if (game->txtr.west.img == NULL)
		close_game("Error\nNo west texture", game);
	if (game->txtr.east.img == NULL)
		close_game("Error\nNo east texture", game);
	if (game->txtr.spr.img == NULL)
		close_game("Error\nNo sprite texture", game);
	if (game->scr.ceiling_col == -1)
		close_game("Error\nNo ceiling color", game);
	if (game->scr.floor_col == -1)
		close_game("Error\nNo floor color", game);
}

int		check_arg(int ac, char **av, t_game *game)
{
	int		save;
	int		len;

	save = 0;
	game->scr.mlx = NULL;
	if (ac == 1)
		close_game("Error\nNo arguments", game);
	if (ac == 2)
	{
		len = ft_strlen(av[1]) - 4;
		if (ft_strncmp(av[1] + len, ".cub", 5) != 0)
			close_game("Error\nInvalid map filename", game);
	}
	if (ac == 3)
	{
		if (ft_strncmp(av[2], "--save", 7) == 0)
			save = 1;
		else
			close_game("Error\nInvalid save argumment", game);
	}
	if (ac > 3)
		close_game("Error\nTo many arguments", game);
	return (save);
}
