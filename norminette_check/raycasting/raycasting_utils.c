/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 00:00:00 by                   #+#    #+#             */
/*   Updated: 2026/08/18 12:00:19 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_data *data, int x, t_ray *ray)
{
	calculate_ray_direction(data, x, &ray->dir_x, &ray->dir_y);
	ray->map_x = (int)data->pos_x;
	ray->map_y = (int)data->pos_y;
}

void	init_delta_dist(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = 1.0 / ray->dir_x;
	if (ray->delta_x < 0)
		ray->delta_x = -ray->delta_x;
	if (ray->dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = 1.0 / ray->dir_y;
	if (ray->delta_y < 0)
		ray->delta_y = -ray->delta_y;
}
