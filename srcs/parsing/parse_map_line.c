/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 12:22:12 by kporceil          #+#    #+#             */
/*   Updated: 2026/04/03 16:46:45 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

static int	scan_player(t_file_data *data, char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'N' || str[i] == 'S'
			|| str[i] == 'E' || str[i] == 'W')
		{
			if (data->player_dir != 0)
				return (-1);
			data->player_pos_x = (int)i;
			data->player_pos_y = data->map_height;
			data->player_dir = str[i];
			str[i] = '0';
		}
		i++;
	}
	return (0);
}

int	parse_map_line(t_file_data *data, char *line)
{
	t_list	*node;
	char	*str;
	size_t	len;

	data->has_map_started = true;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		--len;
	str = ft_strndup(line, len);
	if (!str)
		return (-1);
	node = ft_lstnew(str);
	if (!node || scan_player(data, str) == -1)
	{
		free (node);
		free(str);
		return (-1);
	}
	ft_lstadd_back(&data->map_lines, node);
	data->map_height++;
	if ((int)len > data->map_width)
		data->map_width = (int)len;
	return (0);
}
