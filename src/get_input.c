/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 01:36:02 by moduwole          #+#    #+#             */
/*   Updated: 2023/10/03 18:04:34 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	key_release_handler(int key, t_data *data)
{
	if (key == ESC)
		quit_cub3d(data);
	if (key == W && data->player_move_y == 1)
		data->player_move_y = 0;
	if (key == S && data->player_move_y == -1)
		data->player_move_y = 0;
	if (key == A && data->player_move_x == -1)
		data->player_move_x += 1;
	if (key == D && data->player_move_x == 1)
		data->player_move_x -= 1;
	if (key == ARROW_LEFT && data->player_rotate <= 1)
		data->player_rotate = 0;
	if (key == ARROW_RIGHT && data->player_rotate >= -1)
		data->player_rotate = 0;
	return (0);
}

static int	key_press_handler(int key, t_data *data)
{
	if (key == ESC)
		quit_cub3d(data);
	if (key == ARROW_LEFT)
		data->player_rotate -= 1;
	if (key == ARROW_RIGHT)
		data->player_rotate += 1;
	if (key == W)
		data->player_move_y = 1;
	if (key == A)
		data->player_move_x = -1;
	if (key == S)
		data->player_move_y = -1;
	if (key == D)
		data->player_move_x = 1;
	return (0);
}

void	get_input(t_data *data)
{
	mlx_hook(data->mlx_win, X, 0L, quit_cub3d, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_press_handler, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, key_release_handler, data);
}
