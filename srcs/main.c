/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <lebroue@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:27:06 by lebroue           #+#    #+#             */
/*   Updated: 2026/04/06 19:46:19 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_file_data	data;

	ft_memset(&data, 0, sizeof(t_file_data));
	if (argc != 2)
	{
		printf("Usage: %s <map_file>\n", argv[0]);
		return (1);
	}
	if (parse_file(&data, argv[1]) == -1)
	{
		printf("error\nparsing failed\n");
		free_file_data(&data);
		return (1);
	}
	printf("Parsing successful! Opening window...\n");
	if (ft_open_window(&data) == -1)
	{
		free_file_data(&data);
		return (1);
	}
	return (0);
}
