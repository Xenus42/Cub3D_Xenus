/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <lebroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 11:38:39 by kporceil          #+#    #+#             */
/*   Updated: 2026/04/06 19:52:56 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "parsing.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>

static char	*make_padded_line(char *src, int width)
{
	char	*line;
	size_t	src_len;

	src_len = ft_strlen(src);
	line = ft_calloc(width + 1, sizeof(char));
	if (!line)
		return (NULL);
	ft_memcpy(line, src, src_len);
	ft_memset(line + src_len, ' ', (size_t)width - src_len);
	return (line);
}

static int	fill_map(char **map, t_file_data *data)
{
	t_list	*node;
	int		i;

	i = 0;
	node = data->map_lines;
	while (node)
	{
		map[i] = make_padded_line((char *)node->container, data->map_width);
		if (!map[i])
			return (-1);
		node = node->next;
		i++;
	}
	map[i] = NULL;
	return (0);
}

static int	finalize_map(t_file_data *data)
{
	char	**map;
	int		i;

	map = ft_calloc(data->map_height + 1, sizeof(char *));
	if (!map)
		return (-1);
	if (fill_map(map, data) == -1)
	{
		i = 0;
		while (i <= data->map_height)
		{
			free(map[i]);
			i++;
		}
		free(map);
		return (-1);
	}
	ft_lstclear(&data->map_lines, free);
	data->map = map;
	return (check_map(data));
}

static bool	is_extension_valid(const char *filename, const char *ext)
{
	size_t	fn_len;
	size_t	ext_len;

	fn_len = ft_strlen(filename);
	ext_len = ft_strlen(ext);
	if (fn_len >= ext_len && ft_strncmp(filename + (fn_len - ext_len),
			ext, ext_len + 1) == 0)
		return (true);
	return (false);
}

int	parse_file(t_file_data *data, const char *file)
{
	int		fd;
	char	*line;

	if (!is_extension_valid(file, ".cub"))
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd, READ);
	while (line)
	{
		if (parse_line(data, line) == -1)
		{
			free(line);
			get_next_line(fd, DELETE);
			close (fd);
			return (-1);
		}
		free(line);
		line = get_next_line(fd, READ);
	}
	get_next_line(fd, DELETE);
	close(fd);
	return (finalize_map(data));
}
