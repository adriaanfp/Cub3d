/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jugarcia <jugarcia@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 21:22:33 by jugarcia          #+#    #+#             */
/*   Updated: 2026/08/04 21:22:34 by jugarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc != 2)
		return (print_error("Uso: ./cub3D <archivo.cub>"), 1);
	if (init_game(&data, argv[1]))
		return (cleanup(&data), 1);
	init_hooks(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
