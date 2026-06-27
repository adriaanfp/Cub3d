/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cub3d                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27                               #+#    #+#             */
/*   Updated: 2026/06/27                              ###   ########.fr       */
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

void	draw_wall_column(t_data *data, int x, int draw_start,
	int draw_end, double *params)
{
	int			y;
	int			tex_x;
	int			tex_y;
	double		step;
	double		tex_pos;
	t_texture	*tex;
	int			color;

	tex = select_texture(data, (int)params[0], params[3], params[4]);
	if (!tex || !tex->addr)
		return ;
	tex_x = (int)(params[2] * (double)tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	if ((params[0] == 0 && params[3] > 0) || (params[0] == 1 && params[4] < 0))
		tex_x = tex->width - tex_x - 1;
	step = 1.0 * tex->height / params[1];
	tex_pos = (draw_start - WIN_HEIGHT / 2 + params[1] / 2) * step;
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		tex_pos += step;
		color = get_texture_color(tex, tex_x, tex_y);
		if (color != 0)
			my_mlx_pixel_put(data, x, y, color);
		y++;
	}
}

void	render_walls(t_data *data)
{
	int		x;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	params[5];

	x = 0;
	while (x < WIN_WIDTH)
	{
		perp_wall_dist = cast_ray(data, x, params);
		line_height = (int)(WIN_HEIGHT / perp_wall_dist);
		draw_start = -line_height / 2 + WIN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + WIN_HEIGHT / 2;
		if (draw_end >= WIN_HEIGHT)
			draw_end = WIN_HEIGHT - 1;
		params[4] = line_height;
		draw_wall_column(data, x, draw_start, draw_end, params);
		x++;
	}
}

int	render_frame(t_data *data)
{
	update_movement(data);
	draw_background(data);
	render_walls(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img_ptr, 0, 0);
	return (0);
}
