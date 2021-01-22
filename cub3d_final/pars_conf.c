/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_conf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:42:50 by cquiana           #+#    #+#             */
/*   Updated: 2020/11/07 08:50:41 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		check_color(char *conf, t_game *game, char c)
{
	int		i;

	i = 1;
	if (c == 'F' && game->scr.floor_col != -1)
		close_game("Error\nInvalid color setting", game);
	if (c == 'C' && game->scr.ceiling_col != -1)
		close_game("Error\nInvalid color setting", game);
	while (conf[i])
	{
		if (!(ft_isdigit(conf[i])) && conf[i] != ',')
			close_game("Error\nInvalid color setting", game);
		i++;
	}
}

static void	set_color(t_game *game, int *color, char c)
{
	if (c == 'C')
		game->scr.ceiling_col = create_trgb(0, color[0], color[1], color[2]);
	else
		game->scr.floor_col = create_trgb(0, color[0], color[1], color[2]);
}

void		get_color(char *conf, t_game *game, char c)
{
	int		i;
	int		color[3];
	char	**arr;

	while (*conf && is_space(*conf))
		conf++;
	conf++;
	while (is_space(*conf))
		conf++;
	(check_comma(conf) == 2) ? check_color(conf, game, c) :
				close_game("Error\nColor configuration is bad", game);
	if (!(arr = ft_split(conf, ',')))
		close_game("Error\nMalloc", game);
	i = 0;
	while (arr && arr[i] != NULL)
	{
		color[i] = ft_atoi(arr[i]);
		if ((color[i] = ft_atoi(arr[i])) > 255 || arr[i] < 0 || i > 2)
			close_game("Error\nColor configuration is bad", game);
		free(arr[i]);
		i++;
	}
	free(arr);
	set_color(game, color, c);
}

static char	*set_resolution(char *conf, t_game *game)
{
	game->scr.w = ft_atoi(conf);
	while (*conf && is_space(*conf))
		conf++;
	while (*conf && ft_isdigit(*conf))
		conf++;
	game->scr.h = ft_atoi(conf);
	while (*conf && is_space(*conf))
		conf++;
	while (*conf && ft_isdigit(*conf))
		conf++;
	return (conf);
}

void		get_resolution(char *conf, t_game *game)
{
	int		w;
	int		h;

	mlx_get_screen_size(game->scr.mlx, &w, &h);
	if (game->scr.w != -1 || game->scr.h != -1)
		close_game("Error\nResolution setting not correct1", game);
	conf = ft_strchr(conf, 'R');
	conf++;
	conf = set_resolution(conf, game);
	while (*conf)
	{
		if (ft_isalnum(*conf++))
			close_game("Error\nInvalid symbols in resolution settings", game);
	}
	if (game->scr.w <= 100 || game->scr.h <= 100)
		close_game("Error\nSmall resolution settins", game);
	game->scr.w = game->scr.w > w ? w : game->scr.w;
	game->scr.h = game->scr.h > h ? h : game->scr.h;
}
