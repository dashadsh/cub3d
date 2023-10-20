/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:56:55 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/08/08 23:52:36 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	parsing(t_data *data, char **av)
{
	char	**cub_file;

	if (validate_cub_file(av[1]) == FAILURE)
		exit(FAILURE);
	save_cub(av[1], data);
	cub_file = data->cub_file;
	if (retrieve_file_data(data, cub_file) == FAILURE)
		return (FAILURE);
	if (DEBUG)
	{
		printf("\nSaved map (**map after filling spaces):\n");
		print_array_2d_newline(data->map);
		printf("\n");
		printf("Saved textures:\n");
		printf("South: %s\n", data->tex_south);
		printf("North: %s\n", data->tex_north);
		printf("West: %s\n", data->tex_west);
		printf("East: %s\n", data->tex_east);
	}
	if (validate_map(data, data->map) == FAILURE)
		return (FAILURE);
	if (validate_textures(data) == FAILURE)
		return (FAILURE);
	add_player_direction(data);
	return (SUCCESS);
}
