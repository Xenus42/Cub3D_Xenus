/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 11:42:35 by kporceil          #+#    #+#             */
/*   Updated: 2026/04/03 16:44:29 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

static char	*skip_whitespace(char *str)
{
	while (ft_isspace(*str))
		++str;
	return (str);
}

static char	*get_path_from_line(char *line)
{
	const size_t	start = skip_whitespace(line + 2) - line;
	size_t			len;

	len = 0;
	while (line[start + len] && !ft_isspace(line[start + len]))
		++len;
	return (ft_substr(line, start, len));
}

static int	set_texture_path(t_file_data *data, char *line, int dir)
{
	char	**to_set;

	to_set = NULL;
	if (dir == NORTH)
		to_set = &data->north_face_texture;
	else if (dir == EAST)
		to_set = &data->east_face_texture;
	else if (dir == WEST)
		to_set = &data->west_face_texture;
	else if (dir == SOUTH)
		to_set = &data->south_face_texture;
	else
		return (-1);
	if (*to_set)
		return (-1);
	*to_set = get_path_from_line(line);
	return (0);
}

int	parse_line(t_file_data *data, char *line)
{
	if (data->has_map_started == true)
		return (parse_map_line(data, line));
	else if (*line == 'N' && *(line + 1) == 'O')
		return (set_texture_path(data, line, NORTH));
	else if (*line == 'W' && *(line + 1) == 'E')
		return (set_texture_path(data, line, WEST));
	else if (*line == 'E' && *(line + 1) == 'A')
		return (set_texture_path(data, line, EAST));
	else if (*line == 'S' && *(line + 1) == 'O')
		return (set_texture_path(data, line, SOUTH));
	else if (*line == 'F' || *line == 'C')
		return (parse_color_line(data, line));
	else if (*line == '\n')
		return (0);
	else
		return (parse_map_line(data, line));
	return (0);
}
