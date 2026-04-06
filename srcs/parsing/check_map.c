/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <lebroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:29:29 by kporceil          #+#    #+#             */
/*   Updated: 2026/04/06 19:11:48 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

static int	validate_map_chars(t_file_data *data)
{
	int	row;
	int	col;

	row = 0;
	while (row < data->map_height)
	{
		col = 0;
		while (col < data->map_width)
		{
			if (!is_valid_map_char(data->map[row][col]))
				return (-1);
			++col;
		}
		++row;
	}
	return (0);
}

static int	flood_fill(char **map, int row, int col, int height)
{
	if (row < 0 || col < 0 || row >= height)
		return (-1);
	if (map[row][col] == '1' || map[row][col] == '2')
		return (0);
	if (map[row][col] != '0')
		return (-1);
	map[row][col] = '2';
	if (flood_fill(map, row + 1, col, height) == -1)
		return (-1);
	if (flood_fill(map, row, col + 1, height) == -1)
		return (-1);
	if (flood_fill(map, row - 1, col, height) == -1)
		return (-1);
	if (flood_fill(map, row, col - 1, height) == -1)
		return (-1);
	return (0);
}

int	check_map(t_file_data *data)
{
	if (data->map_height == 0 || data->map_width == 0)
		return (-1);
	if (validate_map_chars(data) == -1)
		return (-1);
	if (data->player_dir == '\0')
		return (-1);
	if (!data->south_texture || !data->north_texture
		|| !data->east_texture || !data->west_texture)
		return (-1);
	if (!data->floor_set || !data->ceiling_set)
		return (-1);
	return (flood_fill(data->map, data->player_pos_y,
			data->player_pos_x, data->map_height));
}