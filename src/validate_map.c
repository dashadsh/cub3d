/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 01:38:57 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/08/07 00:15:58 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// # define ERR_MAP_NONE "Map: Not found"
// # define ERR_MAP_WALLS "Map: Should be surrounded by walls"
// # define ERR_MAP_SMALL "Map: Should contain at least 3 lines"
// # define ERR_MAP_CHAR "Map: Contains invalid character"
// # define ERR_MAP_P_MANY "Map: more than one player"
// # define ERR_MAP_P_NONE "Map: no player found"
// # define ERR_MAP_LAST "Map: Should be the last element in file"

static int	check_map_is_at_the_end(t_data *data)
{
	int	i;
	int	j;

	i = data->map_end_idx;
	while (data->cub_file[i])
	{
		j = 0;
		while (data->cub_file[i][j])
		{
			if (!ft_isspace(data->cub_file[i][j])
				&& data->cub_file[i][j] != '\n')
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

static int	add_player_position(t_data *data, char **map)
{
	int	i;
	int	j;

	if (data->player_dir == '0')
		return (print_error(ERR_MAP_P_NONE), FAILURE);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NEWS", map[i][j]))
			{
				data->player_x = j;
				data->player_y = i;
				data->player_pos_x = (double)j + 0.5;
				data->player_pos_y = (double)i + 0.5;
				map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

// should we have here chck for 0 players?
//
// should we:
// while (ft_isspace(data->map[i][j]))// r v t
// 	j++;
static int	check_map_elements(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	data->player_dir = '0';
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j])
		{
			while (ft_isspace(data->map[i][j]))
				j++;
			if (!(ft_strchr("10NEWS", map[i][j])))
				return (print_error(ERR_MAP_CHAR), FAILURE);
			if (ft_strchr ("NEWS", map[i][j]) && data->player_dir != '0')
				return (print_error(ERR_MAP_P_MANY), FAILURE);
			if (ft_strchr ("NEWS", map[i][j]) && data->player_dir == '0')
				data->player_dir = map[i][j];
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	validate_map(t_data *data, char **map)
{
	if (!data->map)
		return (print_error(ERR_MAP_NONE), FAILURE);
	if (data->map_height < 3)
		return (print_error(ERR_MAP_SMALL), FAILURE);
	if (check_map_elements(data, map) == FAILURE)
		return (FAILURE);
	if (add_player_position(data, map) == FAILURE)
		return (FAILURE);
	if (check_map_is_at_the_end(data) == FAILURE)
		return (print_error(ERR_MAP_LAST), FAILURE);
	return (SUCCESS);
}
