/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <lebroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 12:18:02 by hadia             #+#    #+#             */
/*   Updated: 2026/03/14 01:13:52 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * Parses a color definition line (F or C).
 * Dispatches to RGB parsing based on the prefix.
 * @param line The line to process.
 * @param data Pointer to the file data structure.
 * @return 0 if processed, 1 if not a color, -1 on error.
 */
int	process_colors(char *line, t_file_data *data)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (parse_rgb(line + 2, data->floor_color) == 0)
		{
			data->floor_set = 1;
			return (0);
		}
		return (-1);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (parse_rgb(line + 2, data->ceiling_color) == 0)
		{
			data->ceiling_set = 1;
			return (0);
		}
		return (-1);
	}
	return (1);
}

/**
 * Extracts and validates an RGB value from a substring.
 * Checks for valid range [0-255] and max 3 digits.
 * @param str The full string.
 * @param start Start index of the substring.
 * @param end End index of the substring.
 * @param color_value Pointer to store the parsed value.
 * @return 0 on success, -1 on error.
 */
static int	extract_rgb_value(char *str, int start, int end, int *color_value)
{
	char	*num_str;
	int		length;

	length = end - start;
	if (length > 3 || length == 0)
		return (-1);
	num_str = ft_substr(str, start, length);
	if (!num_str)
		return (-1);
	*color_value = ft_atoi(num_str);
	free(num_str);
	if (*color_value < 0 || *color_value > 255)
		return (-1);
	return (0);
}

static int	counter(char *str, int i, int *nb_coma, char *coma)
{
	if (str[i] == ',')
	{
		if (!coma)
			return (1);
		*coma = 0;
		*nb_coma += 1;
	}
	if (str[i] != ',' && !ft_isdigit(str[i])
		&& str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
		return (1);
	return (0);
}

static int	parse_rgb_values(char *str, int color[3], int *nb_coma, int start)
{
	int		j;
	int		i;
	char	coma;

	j = 0;
	i = 0;
	coma = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			start = i;
			if (coma == 1)
				return (-1);
			while (ft_isdigit(str[i]))
				++i;
			if (extract_rgb_value(str, start, i, &color[j]) == -1 || ++j > 3)
				return (-1);
			coma = 1;
		}
		if (counter(str, i, nb_coma, &coma))
			return (-1);
		++i;
	}
	return (0);
}

/**
 * Parses an RGB color string.
 * Validates comma structure and extracts RGB values.
 * @param str The string to parse.
 * @param color Array to store the RGB values.
 * @return 0 on success, -1 on error.
 */
int	parse_rgb(char *str, int color[3])
{
	int	nb_coma;
	int	status;
	int	start;

	nb_coma = 0;
	start = 0;
	status = parse_rgb_values(str, color, &nb_coma, start);
	if (nb_coma > 2)
		return (-1);
	return (status);
}
