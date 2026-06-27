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


/*
** close_window - Función unificada para cerrar el juego limpiamente
** @data: Puntero a la estructura principal que contiene mlx_ptr y win_ptr
**
** Esta función libera todos los recursos de la MiniLibX en el orden correcto:
** 1. Destruye la ventana si existe
** 2. Destruye el display de X11
** 3. Libera la memoria del puntero MLX
** 4. Sale del programa con código 0
**
** Return: 0 (aunque nunca se alcanza debido a exit)
*/
/*
** free_textures - Libera las texturas cargadas
** @data: Estructura principal del juego
*/
void	free_textures(t_data *data)
{
	if (data->mlx_ptr)
	{
		if (data->tex_no.img != NULL)
			mlx_destroy_image(data->mlx_ptr, data->tex_no.img);
		if (data->tex_so.img != NULL)
			mlx_destroy_image(data->mlx_ptr, data->tex_so.img);
		if (data->tex_we.img != NULL)
			mlx_destroy_image(data->mlx_ptr, data->tex_we.img);
		if (data->tex_ea.img != NULL)
			mlx_destroy_image(data->mlx_ptr, data->tex_ea.img);
	}
}

/*
** load_textures - Carga las texturas XPM
** @data: Estructura principal del juego
**
** Return: 0 si es exitoso, 1 si hay error
*/
int	load_textures(t_data *data)
{
	data->tex_no.img = mlx_xpm_file_to_image(data->mlx_ptr,
			data->map.no_texture, &data->tex_no.width, &data->tex_no.height);
	if (!data->tex_no.img)
		return (1);
	data->tex_no.addr = mlx_get_data_addr(data->tex_no.img,
			&data->tex_no.bits_per_pixel, &data->tex_no.line_length,
			&data->tex_no.endian);
	data->tex_so.img = mlx_xpm_file_to_image(data->mlx_ptr,
			data->map.so_texture, &data->tex_so.width, &data->tex_so.height);
	if (!data->tex_so.img)
		return (1);
	data->tex_so.addr = mlx_get_data_addr(data->tex_so.img,
			&data->tex_so.bits_per_pixel, &data->tex_so.line_length,
			&data->tex_so.endian);
	data->tex_we.img = mlx_xpm_file_to_image(data->mlx_ptr,
			data->map.we_texture, &data->tex_we.width, &data->tex_we.height);
	if (!data->tex_we.img)
		return (1);
	data->tex_we.addr = mlx_get_data_addr(data->tex_we.img,
			&data->tex_we.bits_per_pixel, &data->tex_we.line_length,
			&data->tex_we.endian);
	data->tex_ea.img = mlx_xpm_file_to_image(data->mlx_ptr,
			data->map.ea_texture, &data->tex_ea.width, &data->tex_ea.height);
	if (!data->tex_ea.img)
		return (1);
	data->tex_ea.addr = mlx_get_data_addr(data->tex_ea.img,
			&data->tex_ea.bits_per_pixel, &data->tex_ea.line_length,
			&data->tex_ea.endian);
	return (0);
}

int	close_window(t_data *data)
{
	if (data->mlx_ptr)
	{
		free_textures(data);
		if (data->img_ptr != NULL)
			mlx_destroy_image(data->mlx_ptr, data->img_ptr);
		if (data->win_ptr != NULL)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_map(&data->map);
	exit(0);
	return (0);
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
