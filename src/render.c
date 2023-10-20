/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:40:32 by moduwole          #+#    #+#             */
/*   Updated: 2023/10/03 18:39:01 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	if (data->tex_pixels[y][x] > 0)
		set_image_pixel(image, x, y, data->tex_pixels[y][x]);
	else if (y < data->win_height / 2)
		set_image_pixel(image, x, y, data->col_ceiling_int);
	else if (y < data->win_height - 1)
		set_image_pixel(image, x, y, data->col_floor_int);
}

static void	render_frame(t_data *data)
{
	t_img	image;
	int		x;
	int		y;

	image.img = NULL;
	init_img(data, &image, data->win_width, data->win_height);
	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			set_frame_image_pixel(data, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, image.img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, image.img);
}

void	render_images(t_data *data)
{
	init_texture_pixels(data);
	init_ray(&data->ray);
	raycasting(data);
	render_frame(data);
}

int	render(t_data *data)
{
	data->player_has_moved += move_player(data);
	if (data->player_has_moved == 0)
		return (0);
	render_images(data);
	return (0);
}
