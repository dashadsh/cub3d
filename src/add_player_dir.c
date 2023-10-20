/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_player_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:07:56 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/08/07 00:05:51 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
if player's direction is South, it sets:
direction vector to (0, 1),
plane (camera) vector to (-0.66, 0), for the orthogonal direction.

if the player's direction is North, it sets:
direction vector to (0, -1),
plane vector to (0.66, 0)
*/
static void	player_north_south(t_data *data)
{
	if (data->player_dir == 'S')
	{
		data->player_dir_x = 0;
		data->player_dir_y = 1;
		data->player_plane_x = -0.66;
		data->player_plane_y = 0;
	}
	else if (data->player_dir == 'N')
	{
		data->player_dir_x = 0;
		data->player_dir_y = -1;
		data->player_plane_x = 0.66;
		data->player_plane_y = 0;
	}
	else
		return ;
}

/*
West player direction: 
direction vector to (-1, 0),
the plane vector to (0, -0.66)

East player direction:
direction vector to (1, 0),
plane vector to (0, 0.66)
*/
static void	player_east_west(t_data *data)
{
	if (data->player_dir == 'W')
	{
		data->player_dir_x = -1;
		data->player_dir_y = 0;
		data->player_plane_x = 0;
		data->player_plane_y = -0.66;
	}
	else if (data->player_dir == 'E')
	{
		data->player_dir_x = 1;
		data->player_dir_y = 0;
		data->player_plane_x = 0;
		data->player_plane_y = 0.66;
	}
	else
		return ;
}

void	add_player_direction(t_data *data)
{
	player_north_south(data);
	player_east_west(data);
	if (DEBUG)
	{
		printf("Player data:\n");
		printf("player_dir (NEWS - direction player is looking at): %c\n",
			data->player_dir);
		printf("player_x (idx on **map): %i\n", data->player_x);
		printf("player_y (idx on **map): %i\n", data->player_y);
		printf("player_pos_x (+0.5 to idx to get real position on a grid): %f\n",
			data->player_pos_x);
		printf("player_pos_y (+0.5 to idx to get real position on a grid): %f\n",
			data->player_pos_y);
		printf("player_dir_x: %f\n", data->player_dir_x);
		printf("player_dir_y: %f\n", data->player_dir_y);
		printf("player_plane_x: %f\n", data->player_plane_x);
		printf("player_plane_y: %f\n", data->player_plane_y);
	}
}
