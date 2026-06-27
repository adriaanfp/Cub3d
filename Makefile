# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cub3d                                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/27                               #+#    #+#              #
#    Updated: 2026/06/27                              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -std=gnu17
INCLUDES	= -I. -I./minilibx

SRCS		= main.c \
			  events.c \
			  movement.c \
			  render.c \
			  render_utils.c \
			  raycasting.c \
			  textures.c \
			  parsing.c \
			  parsing_utils.c \
			  parsing_config.c \
			  parsing_map.c \
			  parsing_validation.c \
			  player.c \
			  utils.c \
			  get_next_line.c

OBJS		= $(SRCS:.c=.o)

MLX_DIR		= ./minilibx
MLX_LIB		= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@make -C $(MLX_DIR)

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)
	@make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
