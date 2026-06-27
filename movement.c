/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cub3d                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27                               #+#    #+#             */
/*   Updated: 2026/06/27                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward_backward(t_data *data, int direction)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x + data->dir_x * MOVE_SPEED * direction;
	new_y = data->pos_y + data->dir_y * MOVE_SPEED * direction;
	if ((int)new_x >= 0 && (int)new_x < data->map.width
		&& (int)new_y >= 0 && (int)new_y < data->map.height)
	{
		if (data->map.grid[(int)new_y][(int)new_x] != '1')
		{
			data->pos_x = new_x;
			data->pos_y = new_y;
		}
	}
}

void	move_strafe(t_data *data, int direction)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x + data->plane_x * MOVE_SPEED * direction;
	new_y = data->pos_y + data->plane_y * MOVE_SPEED * direction;
	if ((int)new_x >= 0 && (int)new_x < data->map.width
		&& (int)new_y >= 0 && (int)new_y < data->map.height)
	{
		if (data->map.grid[(int)new_y][(int)new_x] != '1')
		{
			data->pos_x = new_x;
			data->pos_y = new_y;
		}
	}
}

void	rotate_camera(t_data *data, int direction)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = ROT_SPEED * direction;
	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(rot_speed) - data->dir_y * sin(rot_speed);
	data->dir_y = old_dir_x * sin(rot_speed) + data->dir_y * cos(rot_speed);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(rot_speed)
		- data->plane_y * sin(rot_speed);
	data->plane_y = old_plane_x * sin(rot_speed)
		+ data->plane_y * cos(rot_speed);
}

void	update_movement(t_data *data)
{
	if (data->key_w)
		move_forward_backward(data, 1);
	if (data->key_s)
		move_forward_backward(data, -1);
	if (data->key_d)
		move_strafe(data, 1);
	if (data->key_a)
		move_strafe(data, -1);
	if (data->key_left)
		rotate_camera(data, -1);
	if (data->key_right)
		rotate_camera(data, 1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cub3d                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27                               #+#    #+#             */
/*   Updated: 2026/06/27                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** move_forward_backward - Mueve al jugador hacia adelante o atrás
** @data: Estructura principal del juego
** @direction: 1 para adelante, -1 para atrás
*/
void	move_forward_backward(t_data *data, int direction)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x + data->dir_x * MOVE_SPEED * direction;
	new_y = data->pos_y + data->dir_y * MOVE_SPEED * direction;
	if ((int)new_x >= 0 && (int)new_x < data->map.width
		&& (int)new_y >= 0 && (int)new_y < data->map.height)
	{
		if (data->map.grid[(int)new_y][(int)new_x] != '1')
		{
			data->pos_x = new_x;
			data->pos_y = new_y;
		}
	}
}

/*
** move_strafe - Mueve al jugador lateralmente (strafe)
** @data: Estructura principal del juego
** @direction: 1 para derecha, -1 para izquierda
*/
void	move_strafe(t_data *data, int direction)
{
	double	new_x;
	double	new_y;
	double	strafe_x;
	double	strafe_y;

	strafe_x = data->plane_x;
	strafe_y = data->plane_y;
	new_x = data->pos_x + strafe_x * MOVE_SPEED * direction;
	new_y = data->pos_y + strafe_y * MOVE_SPEED * direction;
	if ((int)new_x >= 0 && (int)new_x < data->map.width
		&& (int)new_y >= 0 && (int)new_y < data->map.height)
	{
		if (data->map.grid[(int)new_y][(int)new_x] != '1')
		{
			data->pos_x = new_x;
			data->pos_y = new_y;
		}
	}
}

/*
** rotate_camera - Rota la cámara del jugador
** @data: Estructura principal del juego
** @direction: 1 para derecha, -1 para izquierda
*/
void	rotate_camera(t_data *data, int direction)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = ROT_SPEED * direction;
	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(rot_speed) - data->dir_y * sin(rot_speed);
	data->dir_y = old_dir_x * sin(rot_speed) + data->dir_y * cos(rot_speed);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(rot_speed)
		- data->plane_y * sin(rot_speed);
	data->plane_y = old_plane_x * sin(rot_speed)
		+ data->plane_y * cos(rot_speed);
}

/*
** update_movement - Actualiza el movimiento del jugador según las teclas
** @data: Estructura principal del juego
*/
void	update_movement(t_data *data)
{
	if (data->key_w)
		move_forward_backward(data, 1);
	if (data->key_s)
		move_forward_backward(data, -1);
	if (data->key_d)
		move_strafe(data, 1);
	if (data->key_a)
		move_strafe(data, -1);
	if (data->key_left)
		rotate_camera(data, -1);
	if (data->key_right)
		rotate_camera(data, 1);
}
