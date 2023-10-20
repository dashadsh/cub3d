/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:01:06 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/08/03 22:45:08 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// # define ERR_MAP_TAB "Map: Tab instead of space"

static int	fill_map_2d(t_data *data, char **map, int index)
{
	int		i;
	int		j;

	data->map_width = find_max_width(data, index);
	if (DEBUG)
		printf("Map max width: %d\n", data->map_width);
	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		map[i] = ft_calloc(sizeof(char), (data->map_width + 1));
		if (!map[i])
			return (print_error(ERR_MALLOC), FAILURE);
		while (data->cub_file[index][j] && data->cub_file[index][j] != '\n')
		{
			map[i][j] = data->cub_file[index][j];
			j++;
		}	
		i++;
		index++;
	}
	map[i] = NULL;
	return (SUCCESS);
}

// while (ft_isspace(file[i][j])) // r v f ?? - searchin for file start
static int	count_map_lines(t_data *data, char **file, int i)
{
	int	index_val;
	int	j;

	index_val = i;
	while (file[i])
	{
		j = 0;
		while (ft_isspace(file[i][j]))
			j++;
		if (file[i][j] && file[i][j] != '1')
			break ;
		i++;
	}
	data->map_end_idx = i;
	return (i - index_val);
}

int	no_tabs(t_data *data)
{
	char	**map;
	int		i;
	int		j;

	map = data->map;
	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '\t')
				return (print_error(ERR_MAP_TAB), FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

static int	retrieve_map_data(t_data *data, char **cub_file, int i)
{
	if (DEBUG)
		printf("Map start IDX: %d\n", i);
	data->map_height = count_map_lines(data, cub_file, i);
	if (DEBUG)
		printf("Map height: %d\n", data->map_height);
	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
		return (print_error(ERR_MALLOC), FAILURE);
	if (fill_map_2d(data, data->map, i) == FAILURE)
		return (FAILURE);
	if (no_tabs(data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

/* we should have check for walls here before we fill spaces with '1' */
int	add_map(t_data *data, char **cub_file, int i)
{
	int	j;

	if (retrieve_map_data(data, cub_file, i) == FAILURE)
		return (FAILURE);
	if (DEBUG)
	{
		printf("\nLoaded map (**map before filling spaces):\n");
		j = 0;
		while (j < data->map_height)
		{
			printf("%s\n", data->map[j]);
			j++;
		}
	}
	if (validate_walls(data) == FAILURE)
		return (print_error(ERR_MAP_WALLS), FAILURE);
	make_map_rectangular(data);
	return (SUCCESS);
}
