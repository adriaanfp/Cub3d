/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 00:00:00 by                   #+#    #+#             */
/*   Updated: 2026/08/18 11:59:56 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_step_side(t_data *data, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (data->pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - data->pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (data->pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - data->pos_y) * ray->delta_y;
	}
}

static int	is_wall_hit(t_data *data, t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_x >= data->map.width
		|| ray->map_y < 0 || ray->map_y >= data->map.height)
		return (1);
	return (data->map.grid[ray->map_y][ray->map_x] == '1');
}

static void	perform_dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	ray->side = 0;
	while (hit == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		hit = is_wall_hit(data, ray);
	}
}

static void	finalize_ray(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - data->pos_x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->wall_dist = (ray->map_y - data->pos_y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	if (ray->side == 0)
		ray->wall_x = data->pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = data->pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= (int)ray->wall_x;
}

void	cast_ray(t_data *data, int x, t_ray *ray)
{
	init_ray(data, x, ray);
	init_delta_dist(ray);
	init_step_side(data, ray);
	perform_dda(data, ray);
	finalize_ray(data, ray);
}
