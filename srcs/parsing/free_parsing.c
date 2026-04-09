/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:52:31 by kporceil          #+#    #+#             */
/*   Updated: 2026/04/03 16:45:56 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdlib.h>

void	free_file_data(t_file_data *data)
{
	int	i;

	if (!data)
		return ;
	free(data->north_face_texture);
	free(data->south_face_texture);
	free(data->west_face_texture);
	free(data->east_face_texture);
	if (data->map)
	{
		i = 0;
		while (i < data->map_height)
			free(data->map[i++]);
		free(data->map);
	}
	if (data->map_lines)
		ft_lstclear(&data->map_lines, free);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_textures(game);
	free_file_data(game->data);
	if (game->mlx_image_ptr && game->mlx_ptr)
		mlx_destroy_image(game->mlx_ptr, game->mlx_image_ptr);
	if (game->mlx_ptr && game->mlx_window_ptr)
		mlx_destroy_window(game->mlx_ptr, game->mlx_window_ptr);
	if (game->mlx_ptr)
		mlx_destroy_display(game->mlx_ptr);
	if (game->mlx_ptr)
		free(game->mlx_ptr);
}
