/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_file_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:19:21 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/10/02 10:31:48 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// # define ERR_TEX "Texture: invalid"
// # define ERR_MAP "Map: wrong or incomplete"

static char	*add_tex_path(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	while (line[j] && ft_isspace(line[j]))
		j++;
	len = j;
	while (line[len] && !ft_isspace(line[j]))
		len++;
	path = malloc(sizeof(char) * (len - j + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (line[j] && (!ft_isspace(line[j]) && line[j] != '\n'))
		path[i++] = line[j++];
	path[i] = '\0';
	while (line[j] && (ft_isspace(line[j])))
		j++;
	if (line[j] && line[j] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

static int	add_textures(t_data *data, char *line, int j)
{
	if (line[j + 2] && ft_isprint_no_space(line[j + 2]))
	{
		return (print_error(ERR_TEX), FAILURE);
	}
	if (line[j] == 'N' && line[j + 1] == 'O' && !(data->tex_north))
		data->tex_north = add_tex_path(line, j + 2);
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(data->tex_south))
		data->tex_south = add_tex_path(line, j + 2);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(data->tex_west))
		data->tex_west = add_tex_path(line, j + 2);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(data->tex_east))
		data->tex_east = add_tex_path(line, j + 2);
	else
	{
		return (print_error(ERR_TEX), FAILURE);
	}
	return (SUCCESS);
}

/*	
check error message here:
else if (ft_isdigit(cub_file[i][j]))
	{
		if (add_map(data, cub_file, i) == FAILURE)
		{
			printf("remove error message from Retrieve_file_data: skip_spaces!\n");
			return (FAILURE);
			// return (print_error(ERR_MAP), FAILURE);
		}
		return (SUCCESS);
	}
*/

static int	skip_spaces(t_data *data, char **cub_file, int i, int j)
{
	while (ft_isspace(cub_file[i][j]) || cub_file[i][j] == '\n')
		j++;
	if (ft_isprint_no_space(cub_file[i][j]) && !ft_isdigit(cub_file[i][j]))
	{
		if (cub_file[i][j + 1] && ft_isprint_no_space(cub_file[i][j + 1])
			&& !ft_isdigit(cub_file[i][j]))
		{
			if (add_textures(data, cub_file[i], j) == FAILURE)
				return (FAILURE);
			return (TEXTURE_ADDED);
		}	
		else
		{
			if (add_colors(data, cub_file[i], j) == FAILURE)
				return (FAILURE);
			return (TEXTURE_ADDED);
		}	
	}
	else if (ft_isdigit(cub_file[i][j]))
	{
		if (add_map(data, cub_file, i) == FAILURE)
			return (FAILURE);
		return (SUCCESS);
	}
	return (42);
}

int	retrieve_file_data(t_data *data, char **cub_file)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	while (cub_file[i])
	{
		j = 0;
		while (cub_file[i][j])
		{
			status = skip_spaces(data, cub_file, i, j);
			if (status == FAILURE)
				return (FAILURE);
			else if (status == SUCCESS)
				return (SUCCESS);
			else if (status == TEXTURE_ADDED)
				break ;
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
