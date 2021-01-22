/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquiana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:18:49 by cquiana           #+#    #+#             */
/*   Updated: 2020/11/07 06:58:53 by cquiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define FOV (M_PI / 3)
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include "libft/libft.h"
# include "minilibxd/mlx.h"

typedef struct		s_screen
{
	void			*mlx;
	void			*win;
	int				w;
	int				h;
	int				floor_col;
	int				ceiling_col;
}					t_screen;

typedef struct		s_img
{
	void			*img;
	void			*addr;
	int				line_len;
	int				bpp;
	int				endian;
	int				w;
	int				h;
}					t_img;

typedef struct		s_texture
{
	t_img			north;
	t_img			south;
	t_img			west;
	t_img			east;
	t_img			spr;
}					t_texture;

typedef struct		s_plr
{
	double			x;
	double			y;
	double			pov;
	double			go_speed;
	double			turn_speed;
	int				side;
	int				turn;
	int				go_dir;
	int				step_x;
	int				step_y;
	int				check;
}					t_plr;

typedef struct		s_rays
{
	double			ang;
	double			x;
	double			y;
	double			dist;
	double			hit_x;
	double			hit_y;
	int				hit_vert;
	int				hit_hor;
	int				up;
	int				down;
	int				left;
	int				right;
	int				vert;
}					t_rays;

typedef struct		s_raytools
{
	double			dist;
	double			x;
	double			y;
	double			step_x;
	double			step_y;
	double			plane;
	double			height;
	double			start;
	double			step;
	double			pos;
	int				off_x;
	int				off_y;
	unsigned int	*color;
}					t_raytools;

typedef struct		s_map
{
	char			**map;
	int				scale;
	int				spr_count;
	int				map_w;
	int				map_h;
}					t_map;

typedef	struct		s_sprite
{
	double			x;
	double			y;
	double			dist;
	double			ang;
	double			size;
	double			s_x;
	double			s_y;
	unsigned int	*clr;
	double			step;
	double			pos;
}					t_sprite;

typedef struct		s_bmp_file
{
	char			type[2];
	unsigned int	size;
	short			reserved1;
	short			reserved2;
	unsigned int	off_bits;
}					t_bmp_file;

typedef struct		s_bmp_info
{
	unsigned int	size;
	long			w;
	long			h;
	short int		planes;
	short int		bit_count;
	unsigned int	compression;
	unsigned int	image_size;
	long			pels_per_meter_x;
	long			pels_per_meter_y;
	unsigned int	clr_used;
	unsigned int	clr_important;
}					t_bmp_info;

typedef struct		s_game
{
	t_img			img;
	t_plr			plr;
	t_screen		scr;
	t_rays			*rays;
	t_sprite		*sprite;
	t_map			map;
	t_texture		txtr;
}					t_game;

void				init_game(t_game *game, char *av1, int save);
void				parse_config(t_list *config, t_game *game);
void				get_resolution(char *conf, t_game *game);
void				get_color(char *conf, t_game *game, char c);
void				my_pixel_put(t_img *img, int x, int y, int color);
int					create_trgb(int t, int r, int g, int b);
int					is_space(char c);
int					is_empty(char c);
int					check_comma(char *conf);
void				close_game(char *error, t_game *game);
void				validate_config(t_game *game);
void				check_conf(t_game *game);
void				map_checker(t_game *game, char **map);
int					check_arg(int ac, char **av, t_game *game);
void				create_map(t_list *config, t_game *game);
void				read_line(char *conf, t_game *game, int i);
int					draw_scene(t_game *game);
double				fix_angle(double ang);
int					is_wall(double x, double y, t_game *game);
int					is_sprite(double x, double y, t_game *game);
double				calc_dist(double x1, double x2, double y1, double y2);
void				raycasting(t_game *game);
void				create_wall(t_game *game);
void				create_sprite(t_game *game);
void				save_screenshot(t_game *game);

#endif
