/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cub3d                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27                               #+#    #+#             */
/*   Updated: 2026/06/27                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <X11/keysym.h>
# include "./minilibx/mlx.h"

# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define WIN_TITLE "Cub3D"

# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define DESTROY_NOTIFY 17
# define NO_EVENT_MASK 0

# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

typedef struct s_map
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color;
	int		ceiling_color;
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_map	map;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		key_w;
	int		key_a;
	int		key_s;
	int		key_d;
	int		key_left;
	int		key_right;
}	t_data;

/* Funciones de cierre y eventos */
int		close_window(t_data *data);
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
int		render_frame(t_data *data);

/* Funciones de parsing */
int		parse_file(char *filename, t_data *data);
void	free_map(t_map *map);
void	print_error(char *message);
int		init_player(t_data *data);

/* Funciones auxiliares de string */
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
char	*ft_strtrim(char *str);
int		ft_strncmp(char *s1, char *s2, int n);
char	*get_next_line(int fd);

#endif
