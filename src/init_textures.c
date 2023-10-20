/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:33:22 by moduwole          #+#    #+#             */
/*   Updated: 2023/10/02 10:07:56 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_texture_pixels(t_data *data)
{
	int	i;

	if (data->tex_pixels)
		free_array_2d((void **)data->tex_pixels);
	data->tex_pixels = ft_calloc(data->win_height + 1,
			sizeof * data->tex_pixels);
	if (!data->tex_pixels)
		clean_exit(data, FAILURE);
	i = 0;
	while (i < data->win_height)
	{
		data->tex_pixels[i] = ft_calloc(data->win_width + 1,
				sizeof * data->tex_pixels);
		if (!data->tex_pixels[i])
			clean_exit(data, FAILURE);
		i++;
	}
}

void	init_texture_img(t_data *data, t_img *image, char *path)
{
	init_img_null(image);
	image->img = mlx_xpm_file_to_image(data->mlx_ptr, path, &data->tex_size,
			&data->tex_size);
	if (image->img == NULL)
	{
		print_error(ERR_MALLOC);
		clean_exit(data, FAILURE);
	}
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
}

static int	*xpm_to_img(t_data *data, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	init_texture_img(data, &tmp, path);
	buffer = ft_calloc(1,
			sizeof * buffer * data->tex_size * data->tex_size);
	if (!buffer)
		clean_exit(data, FAILURE);
	y = 0;
	while (y < data->tex_size)
	{
		x = 0;
		while (x < data->tex_size)
		{
			buffer[y * data->tex_size + x]
				= tmp.addr[y * data->tex_size + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx_ptr, tmp.img);
	return (buffer);
}

void	init_textures(t_data *data)
{
	data->textures = ft_calloc(5, sizeof * data->textures);
	if (!data->textures)
		clean_exit(data, FAILURE);
	data->textures[NORTH] = xpm_to_img(data, data->tex_north);
	data->textures[SOUTH] = xpm_to_img(data, data->tex_south);
	data->textures[EAST] = xpm_to_img(data, data->tex_east);
	data->textures[WEST] = xpm_to_img(data, data->tex_west);
}
