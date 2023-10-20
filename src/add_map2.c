/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_map2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:43:13 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/08/03 22:30:09 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	fill_line_with_ones(char *new_line, t_data *data)
{
	int	j;

	j = 0;
	while (j < data->map_width)
	{
		new_line[j] = '1';
		j++;
	}
	new_line[j] = '\0';
}

static void	copy_line(char *new_line, char *old_line)
{
	int	j;

	j = 0;
	while (old_line[j])
	{
		if (old_line[j] != ' ')
			new_line[j] = old_line[j];
		j++;
	}
}

void	make_map_rectangular(t_data *data)
{
	int		i;
	char	*new_line;

	i = 0;
	while (i < data->map_height)
	{
		new_line = (char *)malloc(sizeof(char) * (data->map_width + 1));
		if (!new_line)
		{
			print_error(ERR_MALLOC);
			return ;
		}
		fill_line_with_ones(new_line, data);
		copy_line(new_line, data->map[i]);
		free(data->map[i]);
		data->map[i] = new_line;
		i++;
	}
}

// void	make_map_rectangular(t_data *data)
// {
// 	int		i;
// 	char	*new_line;

//     i = 0;
// 	while (i < data->map_height)
// 	{
// 		if (!(new_line = (char *)malloc(sizeof(char) * (data->map_width + 1))))
// 		{
// 			print_error(ERR_MALLOC);
// 			return ;
// 		}
// 		fill_line_with_ones(new_line, data);
// 		copy_line(new_line, data->map[i]);
// 		free(data->map[i]);
// 		data->map[i] = new_line;
// 		i++;
// 	}
// }
