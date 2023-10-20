/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:42:45 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/10/06 21:30:36 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_img_null(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
}

void	init_ray(t_ray *ray)
{
	ray->camera_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->sidedist_x = 0;
	ray->sidedist_y = 0;
	ray->deltadist_x = 0;
	ray->deltadist_y = 0;
	ray->wall_dist = 0;
	ray->wall_x = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

void	init_data_cub_map(t_data *data)
{
	data->cub_path = NULL;
	data->cub_height = 0;
	data->cub_file = NULL;
	data->cub_fd = -42;
	data->map_height = 0;
	data->map_width = 0;
	data->map = NULL;
	data->map_end_idx = 0;
}

void	init_data_player(t_data *data)
{
	data->player_dir = 0;
	data->player_x = 0;
	data->player_y = 0;
	data->player_pos_x = 0;
	data->player_pos_y = 0;
	data->player_move_x = 0;
	data->player_move_y = 0;
	data->player_dir_x = 0;
	data->player_dir_y = 0;
	data->player_plane_x = 0;
	data->player_plane_y = 0;
	data->player_rotate = 0;
	data->player_has_moved = 0;
}

void	init_data(t_data *data)
{
	init_data_cub_map(data);
	init_data_player(data);
	data->tex_east = NULL;
	data->tex_north = NULL;
	data->tex_south = NULL;
	data->tex_west = NULL;
	data->tex_size = TILE_W;
	data->tex_x = 0;
	data->tex_y = 0;
	data->col_ceiling = NULL;
	data->col_floor = NULL;
	data->col_ceiling_int = 0;
	data->col_floor_int = 0;
	data->textures = NULL;
	data->tex_pixels = NULL;
	data->mlx_ptr = NULL;
	data->mlx_win = NULL;
	data->win_height = WIN_H;
	data->win_width = WIN_W;
}
