/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 21:21:56 by jugarcia          #+#    #+#             */
/*   Updated: 2026/08/04 21:21:56 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_hooks(t_data *data)
{
	mlx_hook(data->win_ptr, DESTROY_NOTIFY,
		NO_EVENT_MASK, close_window, data);
	mlx_hook(data->win_ptr, KEY_PRESS,
		1L << 0, key_press, data);
	mlx_hook(data->win_ptr, KEY_RELEASE,
		1L << 1, key_release, data);
	mlx_loop_hook(data->mlx_ptr,
		render_frame, data);
}
