/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charge_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <lebroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:48:20 by lebroue           #+#    #+#             */
/*   Updated: 2026/04/07 12:28:50 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*get_texture_path(t_file_data *data, char face)
{
	if (face == 'N' && data && data->north_face_texture)
		return (data->north_face_texture);
	else if (face == 'S' && data && data->south_face_texture)
		return (data->south_face_texture);
	else if (face == 'E' && data && data->east_face_texture)
		return (data->east_face_texture);
	else if (face == 'W' && data && data->west_face_texture)
		return (data->west_face_texture);
	return (NULL);
}

static int	load_all_textures(t_game *game, t_file_data *data)
{
	char	*path;

	path = get_texture_path(data, 'N');
	if (path)
		if (load_texture_by_face(game, path, 'N') == -1)
			return (-1);
	path = get_texture_path(data, 'S');
	if (path)
		if (load_texture_by_face(game, path, 'S') == -1)
			return (-1);
	path = get_texture_path(data, 'E');
	if (path)
		if (load_texture_by_face(game, path, 'E') == -1)
			return (-1);
	path = get_texture_path(data, 'W');
	if (path)
		if (load_texture_by_face(game, path, 'W') == -1)
			return (-1);
	return (0);
}

int	load_textures(t_game *game, t_file_data *file_data)
{
	if (load_all_textures(game, file_data) == -1)
		return (-1);
	printf("All textures loaded\n");
	return (0);
}
