/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 04:28:49 by moduwole          #+#    #+#             */
/*   Updated: 2023/10/03 18:05:25 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static bool	is_valid_pos_in_map(t_data *data, double x, double y)
{
	if (x < 0.25 || x >= data->map_width - 1.25)
		return (false);
	if (y < 0.25 || y >= data->map_height -0.25)
		return (false);
	return (true);
}

static bool	is_valid_pos(t_data *data, double x, double y)
{
	if (is_valid_pos_in_map(data, x, y))
		return (true);
	return (false);
}

int	validate_move(t_data *data, double new_x, double new_y)
{
	int	moved;

	moved = 0;
	if (is_valid_pos(data, new_x, data->player_pos_y))
	{
		data->player_pos_x = new_x;
		moved = 1;
	}
	if (is_valid_pos(data, data->player_pos_x, new_y))
	{
		data->player_pos_y = new_y;
		moved = 1;
	}
	return (moved);
}
