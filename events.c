/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cub3d                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27                               #+#    #+#             */
/*   Updated: 2026/06/27                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		close_window(data);
	if (keycode == W_KEY)
		data->key_w = 1;
	if (keycode == S_KEY)
		data->key_s = 1;
	if (keycode == A_KEY)
		data->key_a = 1;
	if (keycode == D_KEY)
		data->key_d = 1;
	if (keycode == LEFT_ARROW)
		data->key_left = 1;
	if (keycode == RIGHT_ARROW)
		data->key_right = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W_KEY)
		data->key_w = 0;
	if (keycode == S_KEY)
		data->key_s = 0;
	if (keycode == A_KEY)
		data->key_a = 0;
	if (keycode == D_KEY)
		data->key_d = 0;
	if (keycode == LEFT_ARROW)
		data->key_left = 0;
	if (keycode == RIGHT_ARROW)
		data->key_right = 0;
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cub3d                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27                               #+#    #+#             */
/*   Updated: 2026/06/27                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** key_press - Manejador de eventos de tecla presionada
** @keycode: Código de la tecla presionada
** @data: Puntero a la estructura principal del juego
**
** Return: 0 siempre
*/
int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		close_window(data);
	if (keycode == W_KEY)
		data->key_w = 1;
	if (keycode == S_KEY)
		data->key_s = 1;
	if (keycode == A_KEY)
		data->key_a = 1;
	if (keycode == D_KEY)
		data->key_d = 1;
	if (keycode == LEFT_ARROW)
		data->key_left = 1;
	if (keycode == RIGHT_ARROW)
		data->key_right = 1;
	return (0);
}

/*
** key_release - Manejador de eventos de tecla liberada
** @keycode: Código de la tecla liberada
** @data: Puntero a la estructura principal del juego
**
** Return: 0 siempre
*/
int	key_release(int keycode, t_data *data)
{
	if (keycode == W_KEY)
		data->key_w = 0;
	if (keycode == S_KEY)
		data->key_s = 0;
	if (keycode == A_KEY)
		data->key_a = 0;
	if (keycode == D_KEY)
		data->key_d = 0;
	if (keycode == LEFT_ARROW)
		data->key_left = 0;
	if (keycode == RIGHT_ARROW)
		data->key_right = 0;
	return (0);
}
