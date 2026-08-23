NAME        = cub3D

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -std=gnu17
INCLUDES    = -I. -I./minilibx

MLX_DIR     = minilibx
MLX_LIB     = $(MLX_DIR)/libmlx.a
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRCS        = $(shell find . -path ./$(MLX_DIR) -prune -o -name "*.c" -print)
OBJS        = $(SRCS:.c=.o)

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	chmod +x $(MLX_DIR)/configure
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	chmod +x $(MLX_DIR)/configure
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
