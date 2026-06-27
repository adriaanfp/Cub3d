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
# include <X11/keysym.h>
# include "./minilibx/mlx.h"

# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define WIN_TITLE "Cub3D"

# define ESC_KEY XK_Escape
# define DESTROY_NOTIFY 17
# define NO_EVENT_MASK 0

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

int		close_window(t_data *data);
int		key_hook(int keycode, t_data *data);

#endif
