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

/* Prototipos de funciones estáticas */
static void	update_movement(t_data *data);

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
** calculate_ray_direction - Calcula la dirección del rayo para una columna
** @data: Estructura principal del juego
** @x: Columna de la pantalla
** @ray_dir_x: Puntero para almacenar la dirección X del rayo
** @ray_dir_y: Puntero para almacenar la dirección Y del rayo
*/
static void	calculate_ray_direction(t_data *data, int x,
	double *ray_dir_x, double *ray_dir_y)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	*ray_dir_x = data->dir_x + data->plane_x * camera_x;
	*ray_dir_y = data->dir_y + data->plane_y * camera_x;
}

/*
** perform_dda - Ejecuta el algoritmo DDA para encontrar el muro
** @data: Estructura principal del juego
** @map_x: Coordenada X del mapa
** @map_y: Coordenada Y del mapa
** @step_x: Dirección de paso en X
** @step_y: Dirección de paso en Y
** @side_dist_x: Distancia al siguiente lado X
** @side_dist_y: Distancia al siguiente lado Y
** @delta_dist_x: Distancia entre lados X
** @delta_dist_y: Distancia entre lados Y
**
** Return: 0 si golpeó lado vertical, 1 si golpeó lado horizontal
*/
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

/*
** cast_ray - Lanza un rayo y calcula la distancia al muro
** @data: Estructura principal del juego
** @x: Columna de la pantalla
** @side: Puntero para almacenar el lado del muro golpeado
**
** Return: Distancia perpendicular al muro
*/
static double	cast_ray(t_data *data, int x, int *side)
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

	calculate_ray_direction(data, x, &ray_dir_x, &ray_dir_y);
	map_x = (int)data->pos_x;
	map_y = (int)data->pos_y;
	delta_dist_x = (ray_dir_x == 0) ? 1e30 : (1.0 / ray_dir_x);
	if (delta_dist_x < 0)
		delta_dist_x = -delta_dist_x;
	delta_dist_y = (ray_dir_y == 0) ? 1e30 : (1.0 / ray_dir_y);
	if (delta_dist_y < 0)
		delta_dist_y = -delta_dist_y;
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (data->pos_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - data->pos_x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (data->pos_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - data->pos_y) * delta_dist_y;
	}
	*side = perform_dda(data, &map_x, &map_y, step_x, step_y,
			&side_dist_x, &side_dist_y, delta_dist_x, delta_dist_y);
	if (*side == 0)
		perp_wall_dist = (map_x - data->pos_x + (1 - step_x) / 2) / ray_dir_x;
	else
		perp_wall_dist = (map_y - data->pos_y + (1 - step_y) / 2) / ray_dir_y;
	return (perp_wall_dist);
}

/*
** draw_wall_column - Dibuja una columna vertical del muro
** @data: Estructura principal del juego
** @x: Columna de la pantalla
** @draw_start: Píxel de inicio
** @draw_end: Píxel de fin
** @side: Lado del muro (0 = vertical, 1 = horizontal)
*/
static void	draw_wall_column(t_data *data, int x, int draw_start,
	int draw_end, int side)
{
	int	y;
	int	color;

	if (side == 0)
		color = 0x808080;
	else
		color = 0x606060;
	y = draw_start;
	while (y < draw_end)
	{
		my_mlx_pixel_put(data, x, y, color);
		y++;
	}
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
	int		x;
	int		y;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		side;

	update_movement(data);
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
	x = 0;
	while (x < WIN_WIDTH)
	{
		perp_wall_dist = cast_ray(data, x, &side);
		line_height = (int)(WIN_HEIGHT / perp_wall_dist);
		draw_start = -line_height / 2 + WIN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + WIN_HEIGHT / 2;
		if (draw_end >= WIN_HEIGHT)
			draw_end = WIN_HEIGHT - 1;
		draw_wall_column(data, x, draw_start, draw_end, side);
		x++;
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
** move_forward_backward - Mueve al jugador hacia adelante o atrás
** @data: Estructura principal del juego
** @direction: 1 para adelante, -1 para atrás
*/
static void	move_forward_backward(t_data *data, int direction)
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
static void	move_strafe(t_data *data, int direction)
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
static void	rotate_camera(t_data *data, int direction)
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
static void	update_movement(t_data *data)
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
	mlx_hook(data.win_ptr, DESTROY_NOTIFY, NO_EVENT_MASK, close_window, &data);
	mlx_hook(data.win_ptr, KEY_PRESS, 1L << 0, key_press, &data);
	mlx_hook(data.win_ptr, KEY_RELEASE, 1L << 1, key_release, &data);
	mlx_loop_hook(data.mlx_ptr, render_frame, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
