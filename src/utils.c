/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:29:20 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/08/03 22:28:45 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	ft_isspace(char c)
{
	if ((c == ' ') || (c == '\t'))
		return (true);
	return (false);
}

void	print_error(char *error_msg)
{
	printf("\nError:\n%s\n\n", error_msg);
}

bool	ft_isprint_no_space(int c)
{
	if (c >= '!' && c <= '~')
		return (true);
	else
		return (false);
}

size_t	ft_strlen_no_newline(const char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != '\n')
			len++;
		i++;
	}
	return (len);
}

// updated function which ignores newline since ft_strlen counts also \n chars
size_t	find_max_width(t_data *data, int i)
{
	size_t	max_width;

	max_width = ft_strlen_no_newline(data->cub_file[i]);
	while (data->cub_file[i])
	{
		if (ft_strlen_no_newline(data->cub_file[i]) > max_width)
			max_width = ft_strlen_no_newline(data->cub_file[i]);
		i++;
	}
	return (max_width);
}

// size_t	find_max_width(t_data *data, int i)
// {
// 	size_t	max_width;

// 	max_width = ft_strlen(data->cub_file[i]);
// 	while (data->cub_file[i])
// 	{
// 		if (ft_strlen(data->cub_file[i]) > max_width)
// 			max_width = ft_strlen(data->cub_file[i]);
// 		i++;
// 	}
// 	return (max_width);
// }
