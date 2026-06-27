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
** my_mlx_pixel_put - Pone un pixel en la imagen
** @data: Estructura principal del juego
** @x: Coordenada X
** @y: Coordenada Y
** @color: Color del pixel
*/
static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_data + (y * data->line_length + x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*
** render_frame - Renderiza un frame completo
** @data: Estructura principal del juego
**
** Pinta el techo y el suelo con los colores configurados
**
** Return: 0 siempre
*/
int	render_frame(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				my_mlx_pixel_put(data, x, y, data->map.ceiling_color);
			else
				my_mlx_pixel_put(data, x, y, data->map.floor_color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}

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
int	close_window(t_data *data)
{
	if (data->img_ptr != NULL)
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	if (data->win_ptr != NULL)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr != NULL)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_map(&data->map);
	exit(0);
	return (0);
}

/*
** key_hook - Manejador de eventos de teclado
** @keycode: Código de la tecla presionada
** @data: Puntero a la estructura principal del juego
**
** Captura la tecla ESC (XK_Escape) para cerrar el juego limpiamente.
**
** Return: 0 siempre
*/
int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		close_window(data);
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
	mlx_hook(data.win_ptr, DESTROY_NOTIFY, NO_EVENT_MASK, close_window, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_loop_hook(data.mlx_ptr, render_frame, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
