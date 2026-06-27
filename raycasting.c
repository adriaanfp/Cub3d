/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cub3d                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27                               #+#    #+#             */
/*   Updated: 2026/06/27                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	perform_dda(t_data *data, int *map_x, int *map_y,
	int step_x, int step_y, double *side_dist_x, double *side_dist_y,
	double delta_dist_x, double delta_dist_y)
{
	int	hit;
	int	side;

	hit = 0;
	side = 0;
	while (hit == 0)
	{
		if (*side_dist_x < *side_dist_y)
		{
			*side_dist_x += delta_dist_x;
			*map_x += step_x;
			side = 0;
		}
		else
		{
			*side_dist_y += delta_dist_y;
			*map_y += step_y;
			side = 1;
		}
		if (*map_x >= 0 && *map_x < data->map.width
			&& *map_y >= 0 && *map_y < data->map.height)
		{
			if (data->map.grid[*map_y][*map_x] == '1')
				hit = 1;
		}
		else
			hit = 1;
	}
	return (side);
}

static void	init_ray_params(t_data *data, double ray_dir_x, double ray_dir_y,
	double *delta_dist_x, double *delta_dist_y)
{
	(void)data;
	*delta_dist_x = (ray_dir_x == 0) ? 1e30 : (1.0 / ray_dir_x);
	if (*delta_dist_x < 0)
		*delta_dist_x = -*delta_dist_x;
	*delta_dist_y = (ray_dir_y == 0) ? 1e30 : (1.0 / ray_dir_y);
	if (*delta_dist_y < 0)
		*delta_dist_y = -*delta_dist_y;
}

static void	init_step_and_side_dist(t_data *data, double ray_dir_x,
	double ray_dir_y, int *step_x, int *step_y, double *side_dist_x,
	double *side_dist_y, double delta_dist_x, double delta_dist_y, int map_x,
	int map_y)
{
	if (ray_dir_x < 0)
	{
		*step_x = -1;
		*side_dist_x = (data->pos_x - map_x) * delta_dist_x;
	}
	else
	{
		*step_x = 1;
		*side_dist_x = (map_x + 1.0 - data->pos_x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		*step_y = -1;
		*side_dist_y = (data->pos_y - map_y) * delta_dist_y;
	}
	else
	{
		*step_y = 1;
		*side_dist_y = (map_y + 1.0 - data->pos_y) * delta_dist_y;
	}
}

static double	calculate_perp_wall_dist(t_data *data, int side, int map_x,
	int map_y, int step_x, int step_y, double ray_dir_x, double ray_dir_y)
{
	double	perp_wall_dist;

	if (side == 0)
		perp_wall_dist = (map_x - data->pos_x + (1 - step_x) / 2) / ray_dir_x;
	else
		perp_wall_dist = (map_y - data->pos_y + (1 - step_y) / 2) / ray_dir_y;
	return (perp_wall_dist);
}

double	cast_ray(t_data *data, int x, double *params)
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	double	perp_wall_dist;
	double	wall_x;

	calculate_ray_direction(data, x, &ray_dir_x, &ray_dir_y);
	map_x = (int)data->pos_x;
	map_y = (int)data->pos_y;
	init_ray_params(data, ray_dir_x, ray_dir_y, &delta_dist_x, &delta_dist_y);
	init_step_and_side_dist(data, ray_dir_x, ray_dir_y, &step_x, &step_y,
		&side_dist_x, &side_dist_y, delta_dist_x, delta_dist_y, map_x, map_y);
	params[0] = perform_dda(data, &map_x, &map_y, step_x, step_y,
			&side_dist_x, &side_dist_y, delta_dist_x, delta_dist_y);
	perp_wall_dist = calculate_perp_wall_dist(data, (int)params[0], map_x,
			map_y, step_x, step_y, ray_dir_x, ray_dir_y);
	if ((int)params[0] == 0)
		wall_x = data->pos_y + perp_wall_dist * ray_dir_y;
	else
		wall_x = data->pos_x + perp_wall_dist * ray_dir_x;
	wall_x -= (int)wall_x;
	params[1] = wall_x;
	params[2] = ray_dir_x;
	params[3] = ray_dir_y;
	return (perp_wall_dist);
}
