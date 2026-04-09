/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:26:59 by kporceil          #+#    #+#             */
/*   Updated: 2026/04/03 16:45:18 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	get_rgb_from_line(int *rgb, char *line)
{
	char	*start;
	char	*end;

	start = skip_whitespace(line + 1);
	rgb[0] = ft_strtol(start, &end, 10);
	if (start == end || *end != ',')
		return (-1);
	start = end + 1;
	rgb[1] = ft_strtol(start, &end, 10);
	if (start == end || *end != ',')
		return (-1);
	start = end + 1;
	rgb[2] = ft_strtol(start, &end, 10);
	if (start == end || *skip_whitespace(end) != '\0')
		return (-1);
	if (rgb[0] > 255 || rgb[0] < 0)
		return (-1);
	if (rgb[1] > 255 || rgb[1] < 0)
		return (-1);
	if (rgb[2] > 255 || rgb[2] < 0)
		return (-1);
	return (0);
}

int	parse_color_line(t_file_data *data, char *line)
{
	int	*color;
	int	*flag;

	if (*line == 'F')
	{
		color = data->floor_color;
		flag = &data->floor_set;
	}
	else
	{
		color = data->ceiling_color;
		flag = &data->ceiling_set;
	}
	if (*flag)
		return (-1);
	*flag = 1;
	return (get_rgb_from_line(color, line));
}
