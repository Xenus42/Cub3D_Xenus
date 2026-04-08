/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <lebroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:58:55 by lebroue           #+#    #+#             */
/*   Updated: 2026/04/01 16:26:04 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <X11/X.h>

int	init_mlx_and_window(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (printf("Failed to initialize MLX\n"), -1);
	game->mlx_window_ptr = mlx_new_window(game->mlx_ptr, S_WIDTH, S_HEIGHT,
			"Cub3D");
	if (!game->mlx_window_ptr)
		return (printf("Failed to create window\n"), -1);
	game->mlx_image_ptr = mlx_new_image(game->mlx_ptr, S_WIDTH, S_HEIGHT);
	if (!game->mlx_image_ptr)
		return (printf("Failed to create image\n"), -1);
	game->pixel_buffer = mlx_get_data_addr(game->mlx_image_ptr,
			&game->bits_for_one_pixel, &game->bytes_per_scanline,
			&game->byte_order);
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->mlx_window_ptr, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->mlx_window_ptr, KeyRelease, KeyReleaseMask, key_release,
		game);
	mlx_hook(game->mlx_window_ptr, DestroyNotify, NoEventMask, close_window,
		game);
	mlx_hook(game->mlx_window_ptr, VisibilityNotify, VisibilityChangeMask,
		minimize_window, NULL);
	mlx_hook(game->mlx_window_ptr, ConfigureNotify, ResizeRedirectMask,
		maximize_window, NULL);
	mlx_loop_hook(game->mlx_ptr, (int (*)(void *))render, game);
}

int	ft_open_window(t_file_data *data)
{
	t_game	game;

	init_game(&game, data);
	if (init_mlx_and_window(&game))
		return (1);
	load_textures(&game, data);
	setup_hooks(&game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
