/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:43:39 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/08/03 22:29:14 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static bool	no_digit_found(char *str)
{
	int		i;
	bool	status;

	i = 0;
	status = true;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			status = false;
		i++;
	}
	return (status);
}

static int	*convert_and_add_rgb(char **rgb_to_convert, int *rgb)
{
	int		i;

	i = -1;
	while (rgb_to_convert[++i])
	{
		rgb[i] = ft_atoi(rgb_to_convert[i]);
		if (rgb[i] == -1 || no_digit_found(rgb_to_convert[i]))
		{
			free_array_2d((void **)rgb_to_convert);
			free(rgb);
			return (0);
		}
	}
	free_array_2d((void **)rgb_to_convert);
	return (rgb);
}

int	col_only_digits(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_isdigit(map[i][j])
				&& !ft_isspace(map[i][j]) && map[i][j] != '\n')
			{
				if (DEBUG)
					printf("Color debugger: %s\n", map[i]);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	*add_rgb(char *line)
{
	char	**rgb_to_convert;
	int		*rgb;
	int		count;

	rgb_to_convert = ft_split(line, ',');
	count = 0;
	while (rgb_to_convert[count])
		count++;
	if (count != 3)
	{
		free_array_2d((void **)rgb_to_convert);
		return (0);
	}
	if (col_only_digits(rgb_to_convert) == 0)
	{
		free_array_2d((void **)rgb_to_convert);
		return (0);
	}
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
	{
		print_error(ERR_MALLOC);
		return (0);
	}
	return (convert_and_add_rgb(rgb_to_convert, rgb));
}

int	add_colors(t_data *data, char *line, int j)
{
	if (line[j + 1] && ft_isprint_no_space(line[j + 1]))
		return (print_error(ERR_COL_FC), FAILURE);
	if (!data->col_ceiling && line[j] == 'C')
	{
		data->col_ceiling = add_rgb(line + j + 1);
		if (data->col_ceiling == 0)
			return (print_error(ERR_COL_C), FAILURE);
	}
	else if (!data->col_floor && line[j] == 'F')
	{
		data->col_floor = add_rgb(line + j + 1);
		if (data->col_floor == 0)
			return (print_error(ERR_COL_F), FAILURE);
	}
	else
		return (print_error(ERR_COL_FC), FAILURE);
	return (SUCCESS);
}
