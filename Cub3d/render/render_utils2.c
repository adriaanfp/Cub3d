/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 00:00:00 by                   #+#    #+#             */
/*   Updated: 2026/08/18 12:19:12 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_ray_direction(t_data *data, int x,
	double *ray_dir_x, double *ray_dir_y)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	*ray_dir_x = data->dir_x + data->plane_x * camera_x;
	*ray_dir_y = data->dir_y + data->plane_y * camera_x;
}

int	get_tex_x(t_texture *tex, t_wall *wall)
{
	int	tex_x;

	tex_x = (int)(wall->wall_x * (double)tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	if ((wall->side == 0 && wall->ray_dir_x > 0)
		|| (wall->side == 1 && wall->ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}
