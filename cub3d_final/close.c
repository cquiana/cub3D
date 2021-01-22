/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:03:52 by cquiana           #+#    #+#             */
/*   Updated: 2020/11/07 07:15:19 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	close_window(t_game *game)
{
	if (game->scr.mlx == NULL)
		return ;
	if (game->scr.win)
		mlx_destroy_window(game->scr.mlx, game->scr.win);
	if (game->txtr.north.img)
		mlx_destroy_image(game->scr.mlx, game->txtr.north.img);
	if (game->txtr.south.img)
		mlx_destroy_image(game->scr.mlx, game->txtr.south.img);
	if (game->txtr.west.img)
		mlx_destroy_image(game->scr.mlx, game->txtr.west.img);
	if (game->txtr.east.img)
		mlx_destroy_image(game->scr.mlx, game->txtr.east.img);
	if (game->txtr.spr.img)
		mlx_destroy_image(game->scr.mlx, game->txtr.spr.img);
	if (game->img.img)
		mlx_destroy_image(game->scr.mlx, game->img.img);
	if (game->scr.mlx)
		free(game->scr.mlx);
}

void		close_game(char *error, t_game *game)
{
	ft_putendl_fd(error, 1);
	close_window(game);
	exit(0);
}
