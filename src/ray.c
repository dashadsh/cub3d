/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:09:41 by moduwole          #+#    #+#             */
/*   Updated: 2023/10/10 10:56:48 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	calculate_line_height(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
	ray->line_height = (int)(data->win_height / ray->wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + data->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + data->win_height / 2;
	if (ray->draw_end >= data->win_height)
		ray->draw_end = data->win_height - 1;
	if (ray->side == 0)
		ray->wall_x = data->player_pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = data->player_pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

static void	perform_dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0.25 || ray->map_x < 0.25
			|| ray->map_y > data->map_height - 0.25
			|| ray->map_x > data->map_width - 1.25)
			break ;
		else if (data->map[ray->map_y][ray->map_x] > '0')
			hit = 1;
	}
}

static void	set_dda(t_ray *ray, t_data *data)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (data->player_pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x
			= (ray->map_x + 1.0 - data->player_pos_x) * ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (data->player_pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y
			= (ray->map_y + 1.0 - data->player_pos_y) * ray->deltadist_y;
	}
}

static void	init_raycasting_info(int x, t_ray *ray, t_data *data)
{
	init_ray(ray);
	ray->camera_x = 2 * x / (double)WIN_W - 1;
	ray->dir_x = data->player_dir_x + data->player_plane_x * ray->camera_x;
	ray->dir_y = data->player_dir_y + data->player_plane_y * ray->camera_x;
	ray->map_x = (int)data->player_pos_x;
	ray->map_y = (int)data->player_pos_y;
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
}

int	raycasting(t_data *data)
{
	t_ray	*ray;
	int		x;

	x = 0;
	ray = &data->ray;
	while (x < data->win_width)
	{
		init_raycasting_info(x, ray, data);
		set_dda(ray, data);
		perform_dda(data, ray);
		calculate_line_height(ray, data);
		update_texture_pixels(data, ray, x);
		x++;
	}
	return (SUCCESS);
}
