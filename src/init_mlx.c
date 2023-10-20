/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:18:06 by moduwole          #+#    #+#             */
/*   Updated: 2023/10/03 18:05:56 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		print_error(ERR_MLX);
		clean_exit(data, FAILURE);
	}
	data->mlx_win = mlx_new_window(data->mlx_ptr, WIN_W, WIN_H, "Cub3D");
	if (!data->mlx_win)
	{
		print_error(ERR_MLX_WIN);
		clean_exit(data, FAILURE);
	}
}
