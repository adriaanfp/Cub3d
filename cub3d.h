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
# include <X11/keysym.h>
# include "./minilibx/mlx.h"

# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define WIN_TITLE "Cub3D"

# define ESC_KEY XK_Escape
# define DESTROY_NOTIFY 17
# define NO_EVENT_MASK 0

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
	t_map	map;
}	t_data;

/* Funciones de cierre y eventos */
int		close_window(t_data *data);
int		key_hook(int keycode, t_data *data);

/* Funciones de parsing */
int		parse_file(char *filename, t_data *data);
void	free_map(t_map *map);
void	print_error(char *message);

#endif
