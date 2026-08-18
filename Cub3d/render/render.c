/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 00:00:00 by                   #+#    #+#             */
/*   Updated: 2026/08/18 12:19:21 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_tex_column(t_data *data, int x, t_wall *wall, t_texdraw *td)
{
	int	y;
	int	tex_y;
	int	color;

	y = wall->draw_start;
	while (y < wall->draw_end)
	{
		tex_y = (int)td->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= td->tex->height)
			tex_y = td->tex->height - 1;
		td->tex_pos += td->step;
		color = get_texture_color(td->tex, td->tex_x, tex_y);
		if (color != 0)
			my_mlx_pixel_put(data, x, y, color);
		y++;
	}
}

void	draw_wall_column(t_data *data, int x, t_wall *wall)
{
	t_texture	*tex;
	t_texdraw	td;

	tex = select_texture(data, wall->side, wall->ray_dir_x, wall->ray_dir_y);
	if (!tex || !tex->addr)
		return ;
	td.tex = tex;
	td.tex_x = get_tex_x(tex, wall);
	td.step = 1.0 * tex->height / wall->line_height;
	td.tex_pos = (wall->draw_start - WIN_HEIGHT / 2
			+ wall->line_height / 2) * td.step;
	draw_tex_column(data, x, wall, &td);
}

static void	build_wall(t_ray *ray, t_wall *wall)
{
	wall->line_height = (int)(WIN_HEIGHT / ray->wall_dist);
	wall->side = ray->side;
	wall->wall_x = ray->wall_x;
	wall->ray_dir_x = ray->dir_x;
	wall->ray_dir_y = ray->dir_y;
	wall->draw_start = -wall->line_height / 2 + WIN_HEIGHT / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = wall->line_height / 2 + WIN_HEIGHT / 2;
	if (wall->draw_end >= WIN_HEIGHT)
		wall->draw_end = WIN_HEIGHT - 1;
}

void	render_walls(t_data *data)
{
	int		x;
	t_ray	ray;
	t_wall	wall;

	x = 0;
	while (x < WIN_WIDTH)
	{
		cast_ray(data, x, &ray);
		build_wall(&ray, &wall);
		draw_wall_column(data, x, &wall);
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
