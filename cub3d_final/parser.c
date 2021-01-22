/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:37:00 by cquiana           #+#    #+#             */
/*   Updated: 2020/11/07 01:01:46 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_texture(char *path, t_img *text, t_game *game)
{
	if (text->img != NULL)
		close_game("Error\nInvalid texture", game);
	text->img = mlx_xpm_file_to_image(game->scr.mlx, path, &text->w, \
			&text->h);
	if (text->img == NULL)
		close_game("Error\nInvalid texture", game);
	text->addr = mlx_get_data_addr(text->img, &text->bpp, &text->line_len, \
				&text->endian);
	if (text->addr == NULL)
		close_game("Error\nInvalid texture", game);
}

static void	get_texture(char *conf, t_game *game, char c)
{
	while (*conf && is_space(*conf))
		conf++;
	conf = conf + 2;
	while (*conf && is_space(*conf))
		conf++;
	if (c == 'N')
		set_texture(conf, &game->txtr.north, game);
	if (c == 'S')
		set_texture(conf, &game->txtr.south, game);
	if (c == 'W')
		set_texture(conf, &game->txtr.west, game);
	if (c == 'E')
		set_texture(conf, &game->txtr.east, game);
	if (c == 's')
		set_texture(conf, &game->txtr.spr, game);
}

static void	check_line(char *conf, t_game *game)
{
	while (is_empty(*conf) && *conf)
		conf++;
	if (*conf != '1' && *conf != '\0')
		close_game("Error\nConfig not valid", game);
}

void		parse_config(t_list *config, t_game *game)
{
	size_t	len;

	while (config)
	{
		len = ft_strlen(config->content);
		if (ft_strnstr(config->content, "R ", len))
			get_resolution(config->content, game);
		else if (ft_strnstr(config->content, "NO ", len))
			get_texture(config->content, game, 'N');
		else if (ft_strnstr(config->content, "SO ", len))
			get_texture(config->content, game, 'S');
		else if (ft_strnstr(config->content, "WE ", len))
			get_texture(config->content, game, 'W');
		else if (ft_strnstr(config->content, "EA ", len))
			get_texture(config->content, game, 'E');
		else if (ft_strnstr(config->content, "S ", len))
			get_texture(config->content, game, 's');
		else if (ft_strnstr(config->content, "F ", len))
			get_color(config->content, game, 'F');
		else if (ft_strnstr(config->content, "C ", len))
			get_color(config->content, game, 'C');
		else
			check_line(config->content, game);
		config = config->next;
	}
}
