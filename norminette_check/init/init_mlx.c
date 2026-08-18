/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 21:23:13 by jugarcia          #+#    #+#             */
/*   Updated: 2026/08/04 21:23:13 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	create_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!data->win_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		return (1);
	}
	return (0);
}

static int	create_image(t_data *data)
{
	data->img_ptr = mlx_new_image(data->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT);
	if (!data->img_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		return (1);
	}
	data->img_data = mlx_get_data_addr(data->img_ptr,
			&data->bits_per_pixel,
			&data->line_length,
			&data->endian);
	return (0);
}

int	init_mlx(t_data *data)
{
	if (create_window(data))
		return (1);
	if (create_image(data))
		return (1);
	return (0);
}
