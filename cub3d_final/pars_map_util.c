/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:27:58 by cquiana           #+#    #+#             */
/*   Updated: 2020/11/07 06:26:07 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player(char c, int x, int y, t_game *game)
{
	if (game->plr.pov != -1 || game->plr.x != 0 || game->plr.y != 0)
		close_game("Error\nTo many players on map", game);
	game->plr.x = x + 0.5;
	game->plr.y = y + 0.5;
	if (c == 'N')
		game->plr.pov = 3 * M_PI / 2;
	else if (c == 'S')
		game->plr.pov = M_PI / 2;
	else if (c == 'W')
		game->plr.pov = M_PI;
	else if (c == 'E')
		game->plr.pov = 0;
}

void		read_line(char *conf, t_game *game, int i)
{
	int		x;
	char	*tmp;

	x = 0;
	tmp = ft_strdup(conf);
	if (!(ft_strchr(tmp, '1')))
		close_game("Error\nEmpty string after map", game);
	while (tmp[x] != '\0')
	{
		if (tmp[x] == 'N' || tmp[x] == 'S' || tmp[x] == 'W' || \
				tmp[x] == 'E')
		{
			game->plr.check = 1;
			set_player(tmp[x], x, i, game);
		}
		else if (tmp[x] == '2')
			game->map.spr_count++;
		else if (tmp[x] != '1' && tmp[x] != '0' && tmp[x] != ' ')
			close_game("Error\nInvalid symbol in map", game);
		x++;
	}
	free(tmp);
}
