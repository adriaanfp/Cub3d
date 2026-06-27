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

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc != 2)
	{
		print_error("Uso: ./cub3D <archivo.cub>");
		return (1);
	}
	if (parse_file(argv[1], &data))
	{
		free_map(&data.map);
		return (1);
	}
	if (init_player(&data))
	{
		free_map(&data.map);
		return (1);
	}
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
	{
		free_map(&data.map);
		return (1);
	}
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			WIN_TITLE);
	if (!data.win_ptr)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		free_map(&data.map);
		return (1);
	}
	data.img_ptr = mlx_new_image(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!data.img_ptr)
	{
		mlx_destroy_window(data.mlx_ptr, data.win_ptr);
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		free_map(&data.map);
		return (1);
	}
	data.img_data = mlx_get_data_addr(data.img_ptr, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	if (load_textures(&data))
	{
		print_error("Error al cargar las texturas");
		mlx_destroy_image(data.mlx_ptr, data.img_ptr);
		mlx_destroy_window(data.mlx_ptr, data.win_ptr);
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		free_map(&data.map);
		return (1);
	}
	mlx_hook(data.win_ptr, DESTROY_NOTIFY, NO_EVENT_MASK, close_window, &data);
	mlx_hook(data.win_ptr, KEY_PRESS, 1L << 0, key_press, &data);
	mlx_hook(data.win_ptr, KEY_RELEASE, 1L << 1, key_release, &data);
	mlx_loop_hook(data.mlx_ptr, render_frame, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
