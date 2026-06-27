/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cub3d                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27                               #+#    #+#             */
/*   Updated: 2026/06/27                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			WIN_TITLE);
	if (!data->win_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		return (1);
	}
	return (0);
}

static int	init_image(t_data *data)
{
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img_ptr)
		return (1);
	data->img_data = mlx_get_data_addr(data->img_ptr, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	return (0);
}

static void	setup_hooks(t_data *data)
{
	mlx_hook(data->win_ptr, DESTROY_NOTIFY, NO_EVENT_MASK,
		close_window, data);
	mlx_hook(data->win_ptr, KEY_PRESS, 1L << 0, key_press, data);
	mlx_hook(data->win_ptr, KEY_RELEASE, 1L << 1, key_release, data);
	mlx_loop_hook(data->mlx_ptr, render_frame, data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc != 2)
	{
		print_error("Uso: ./cub3D <archivo.cub>");
		return (1);
	}
	if (parse_file(argv[1], &data) || init_player(&data))
	{
		free_map(&data.map);
		return (1);
	}
	if (init_mlx(&data) || init_image(&data) || load_textures(&data))
	{
		print_error("Error al inicializar el juego");
		free_map(&data.map);
		return (1);
	}
	setup_hooks(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
