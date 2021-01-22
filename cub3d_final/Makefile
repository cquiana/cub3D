# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cquiana <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/05 15:17:12 by cquiana           #+#    #+#              #
#    Updated: 2020/11/07 09:15:31 by cquiana          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

INCLUDE	=	libft/libft.h
SRC		=	cub3d.c	close.c		engine.c	init_game.c		parser.c	\
			pars_conf.c		parse_map.c		pars_map_util.c	\
			raycasting.c	raycasting_utils.c	screenshot.c	sprites.c	\
			utils.c		validator.c		walls.c


CC = gcc
FLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:%.c=%.o)

LIBFT_DIR	=	libft/
MLX_DIR		=	minilibxd/
MLX_LIB		=	libmlx.dylib

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
		@make -C $(LIBFT_DIR)
		@make -C $(MLX_DIR)
		@cp $(MLX_DIR)$(MLX_LIB) ./
		@$(CC) $(FLAGS) -lft -Llibft $(MLX_LIB) -framework OpenGL -framework AppKit $(OBJ) -o $(NAME)

%.o: %.c $(INCLUDE)
		$(CC) -Ilibft -Imlx -c $< -o $@

clean:
		@$(RM) *.o
		@rm -f screenshot.bmp
		@make -C $(LIBFT_DIR) clean
		@echo "Object files has been removed"

fclean: clean
		@make -C $(MLX_DIR) clean
		@make -C $(LIBFT_DIR) fclean
		@$(RM) -f $(NAME) $(MLX_LIB)
		@echo "Library files has been removed"

run: all
		./cub3D map.cub

norm:
		norminette *.c *.h

re: fclean all

.PHONY: all clean fclean re
