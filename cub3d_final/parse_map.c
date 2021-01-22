/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:19:44 by cquiana           #+#    #+#             */
/*   Updated: 2020/11/07 06:26:48 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	remake_map(t_game *game, int line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (game->map.map[i] != NULL)
	{
		tmp = game->map.map[i];
		game->map.map[i] = (char *)malloc(sizeof(char) * (line + 1));
		ft_memset(game->map.map[i], ' ', line);
		game->map.map[i][line] = '\0';
		ft_memcpy(game->map.map[i], tmp, ft_strlen(tmp));
		free(tmp);
		i++;
	}
	game->map.map_w = line;
	game->map.map_h = i;
}

static void	init_sprite_struct(t_game *game)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	y = 0;
	if (!(game->sprite = malloc(sizeof(t_sprite) * (game->map.spr_count))))
		close_game("Error\nMalloc failed", game);
	while (game->map.map[y])
	{
		x = 0;
		while (game->map.map[y][x])
		{
			if (game->map.map[y][x] == '2')
			{
				game->sprite[i].x = (x + 0.5) * game->map.scale;
				game->sprite[i].y = (y + 0.5) * game->map.scale;
				i++;
			}
			x++;
		}
		y++;
	}
}

static void	set_map_scale(t_game *game, int j)
{
	game->map.scale = game->scr.h > game->scr.w ? game->scr.h / j : \
				game->scr.w / j;
	game->plr.x *= game->map.scale;
	game->plr.y *= game->map.scale;
}

void		create_map(t_list *config, t_game *game)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (config && ft_atoi(config->content) == 0)
		config = config->next;
	if (!(game->map.map = (char **)malloc(sizeof(char *) * \
						(ft_lstsize(config) + 1))))
		close_game("Error\nConfig file can't open", game);
	while (config->next != NULL)
	{
		read_line(config->content, game, i);
		game->map.map[i] = ft_strdup(config->content);
		j = j < ft_strlen(config->content) ? ft_strlen(config->content) : j;
		config = config->next;
		i++;
	}
	game->map.map[i] = NULL;
	remake_map(game, j);
	check_conf(game);
	j = j < i ? i : j;
	set_map_scale(game, j);
	init_sprite_struct(game);
}
