# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 00:56:42 by dgoremyk          #+#    #+#              #
#    Updated: 2023/10/02 06:15:37 by moduwole         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g -Imlx
RM			= rm -f

SRC_PATH 	= src/
OBJ_PATH 	= obj/

HEADER		= inc/cub3d.h

SRC 		= main.c \
			init.c \
			parsing.c \
			save_cub.c \
			retrieve_file_data.c \
			add_colors.c \
			add_map.c \
			add_map2.c \
			validate_map.c \
			validate_walls.c \
			validate_textures.c \
			add_player_dir.c \
			free.c \
			exit.c \
			utils.c \
			utils2.c \
			debug.c \
			init_mlx.c \
			init_textures.c \
			render.c \
			ray.c \
			texture.c \
			image.c \
			get_input.c \
			player_move.c \
			validate_move.c \
			player_rotate.c 
	
SRCS 		= $(addprefix $(SRC_PATH), $(SRC))

OBJ 		= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

LIBFT 		= ./libft/libft.a

# Detect the operating system
UNAME_S := $(shell uname -s)

# macOS
ifeq ($(UNAME_S),Darwin)
MLX_DIR = ./minilibx_opengl_20191021
MLXLIB = $(MLX_DIR)/libmlx.a
MLXFLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

# Linux
else
MLX_DIR = ./minilibx-linux
MLXLIB = $(MLX_DIR)/libmlx.a
MLXFLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
endif
# endif marks the end of a conditional block in a Makefile

$(OBJ_PATH)%.o: $(SRC_PATH)%.c  $(HEADER)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libft
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT) $(MLXFLAGS) -o $(NAME)
	@echo "     ---------------------------------------------"
	@echo "       compilation successful using $(UNAME_S)"
	@echo "     ---------------------------------------------"

clean:
	$(MAKE) clean -C $(MLX_DIR)
	$(MAKE) clean -C libft
	$(RM) $(OBJS)
	
fclean: clean
	$(MAKE) fclean -C libft
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
