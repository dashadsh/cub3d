/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:24:58 by moduwole          #+#    #+#             */
/*   Updated: 2023/10/02 10:28:50 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	get_texture_index(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			data->tex_index = WEST;
		else
			data->tex_index = EAST;
	}
	else
	{
		if (ray->dir_y > 0)
			data->tex_index = SOUTH;
		else
			data->tex_index = NORTH;
	}
}

void	update_texture_pixels(t_data *data, t_ray *ray, int x)
{
	int	y;
	int	color;

	get_texture_index(data, ray);
	data->tex_x = (int)(ray->wall_x * data->tex_size);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		data->tex_x = data->tex_size - data->tex_x - 1;
	data->tex_step = 1.0 * data->tex_size / ray->line_height;
	data->tex_pos = (ray->draw_start - data->win_height / 2
			+ ray->line_height / 2) * data->tex_step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		data->tex_y = (int)data->tex_pos & (data->tex_size - 1);
		data->tex_pos += data->tex_step;
		color = data->textures[data->tex_index][data->tex_size
			* data->tex_y + data->tex_x];
		if (data->tex_index == NORTH || data->tex_index == EAST)
			color = (color >> 1) & 8355711;
		if (color > 0)
			data->tex_pixels[y][x] = color;
		y++;
	}
}
