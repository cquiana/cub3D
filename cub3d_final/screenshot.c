/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:46:37 by cquiana           #+#    #+#             */
/*   Updated: 2020/11/07 08:25:31 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_sr_color(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int*)dst);
}

static void	header(unsigned char *head_info, int img_size,
		t_game *game, int temp)
{
	head_info[0] = (unsigned char)'B';
	head_info[1] = (unsigned char)'M';
	head_info[2] = (unsigned char)img_size;
	head_info[3] = (unsigned char)(img_size >> 8);
	head_info[4] = (unsigned char)(img_size >> 16);
	head_info[5] = (unsigned char)(img_size >> 24);
	head_info[10] = (unsigned char)54;
	head_info[14] = (unsigned char)40;
	head_info[18] = (unsigned char)temp;
	head_info[19] = (unsigned char)(temp >> 8);
	head_info[20] = (unsigned char)(temp >> 16);
	head_info[21] = (unsigned char)(temp >> 24);
	head_info[22] = (unsigned char)game->scr.h;
	head_info[23] = (unsigned char)(game->scr.h >> 8);
	head_info[24] = (unsigned char)(game->scr.h >> 16);
	head_info[25] = (unsigned char)(game->scr.h >> 24);
	head_info[26] = (unsigned char)1;
	head_info[28] = (unsigned char)24;
}

static void	write_screen(t_game *game, int fd, int res)
{
	int		color;
	int		x;
	int		y;

	color = 0;
	y = game->scr.h - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < res)
		{
			color = get_sr_color(&game->img, x, y);
			write(fd, &color, 3);
			x++;
		}
		y--;
	}
}

void		save_screenshot(t_game *game)
{
	int				fd;
	int				i;
	int				img_size;
	int				tmp_w;
	unsigned char	head_info[54];

	tmp_w = game->scr.w;
	if (game->scr.w % 4)
		tmp_w = game->scr.w - (game->scr.w % 4);
	img_size = tmp_w * game->scr.h + 54;
	i = 0;
	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 777);
	while (i < 54)
	{
		head_info[i] = (unsigned char)0;
		i++;
	}
	header(head_info, img_size, game, tmp_w);
	write(fd, head_info, 54);
	write_screen(game, fd, tmp_w);
	close(fd);
	exit(0);
}
