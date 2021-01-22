/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:31:40 by cquiana           #+#    #+#             */
/*   Updated: 2020/11/07 06:27:57 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_default(t_game *game)
{
	game->scr.mlx = NULL;
	game->scr.win = NULL;
	game->img.img = NULL;
	game->txtr.north.img = NULL;
	game->txtr.south.img = NULL;
	game->txtr.west.img = NULL;
	game->txtr.east.img = NULL;
	game->txtr.spr.img = NULL;
	game->plr.x = 0;
	game->plr.y = 0;
	game->plr.check = 0;
	game->plr.side = 0;
	game->plr.pov = -1;
	game->plr.turn = 0;
	game->plr.turn_speed = 5 * (M_PI / 180);
	game->plr.go_dir = 0;
	game->plr.go_speed = 5;
	game->scr.w = -1;
	game->scr.h = -1;
	game->scr.ceiling_col = -1;
	game->scr.floor_col = -1;
	game->map.map = NULL;
	game->map.spr_count = 0;
}

void		read_config(t_game *game, char *av1)
{
	int		fd;
	char	*line;
	t_list	*config;
	t_list	*tmp;

	fd = open(av1, O_RDONLY);
	if (fd < 0)
		close_game("Error\nConfig file not valid", game);
	config = NULL;
	while (get_next_line(fd, &line) > 0)
		ft_lstadd_back(&config, ft_lstnew(line));
	close(fd);
	ft_lstadd_back(&config, ft_lstnew(line));
	parse_config(config, game);
	validate_config(game);
	create_map(config, game);
	while (config != 0)
	{
		tmp = config->next;
		free(config->content);
		free(config);
		config = tmp;
	}
}

void		create_image(t_img *img, t_game *game, t_screen *scr)
{
	img->img = mlx_new_image(scr->mlx, scr->w, scr->h);
	if (img->img == NULL)
		close_game("Error\nMlx error", game);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, \
				&img->endian);
	if (img->addr == NULL)
		close_game("Error\nMlx error", game);
}

void		init_game(t_game *game, char *av1, int save)
{
	init_default(game);
	game->scr.mlx = mlx_init();
	if (!game->scr.mlx)
		close_game("Error\nMlx init error", game);
	read_config(game, av1);
	if (!(game->rays = malloc(sizeof(t_rays) * game->scr.w)))
		close_game("Error\nMalloc failed", game);
	create_image(&game->img, game, &game->scr);
	draw_scene(game);
	if (save == 1)
		save_screenshot(game);
	game->scr.win = mlx_new_window(game->scr.mlx, game->scr.w, \
					game->scr.h, "cub3D");
	if (game->scr.win == NULL)
		close_game("Error\nMlx window init error", game);
	mlx_put_image_to_window(game->scr.mlx, game->scr.win, \
					game->img.img, 0, 0);
}
