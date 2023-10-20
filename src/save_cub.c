/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 12:21:38 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/08/05 17:15:59 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_cub_file_extension(char *filename)
{
	size_t	length_of_filename;

	length_of_filename = ft_strlen(filename);
	if (length_of_filename < 4)
		return (FAILURE);
	if (ft_strncmp(&filename[length_of_filename - 4], ".cub", 4) == 0)
		return (SUCCESS);
	else
		return (FAILURE);
}

int	validate_cub_file(char *filename)
{
	int	fd;

	if (check_cub_file_extension(filename) == FAILURE)
		return (print_error(ERR_EXTENTION), FAILURE);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (print_error(ERR_OPEN), FAILURE);
	close(fd);
	return (SUCCESS);
}

int	line_counter(char *filepath, t_data *data)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open_file(filepath, data);
	line = get_next_line(fd);
	while (line != NULL)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

void	read_and_save_cub_file(int row, int col, int i, t_data *data)
{
	char	*line;

	line = get_next_line(data->cub_fd);
	while (line != NULL)
	{
		data->cub_file[row]
			= ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!data->cub_file[row])
			return (print_error(ERR_MALLOC), clean_exit(data, FAILURE));
		while (line[i] != '\0')
			data->cub_file[row][col++] = line[i++];
		data->cub_file[row++][col] = '\0';
		col = 0;
		i = 0;
		free(line);
		line = get_next_line(data->cub_fd);
	}
	data->cub_file[row] = NULL;
}

/* save following data to t_mapdata mapdata:
1. path to file (using malloc)
2. amt of lines
3. all content of file as 2d array (using malloc)
*/
void	save_cub(char *cub_path, t_data *data)
{
	int	row;
	int	col;
	int	i;

	row = 0;
	col = 0;
	i = 0;
	data->cub_height = line_counter(cub_path, data);
	data->cub_file
		= ft_calloc(data->cub_height + 1, sizeof(char *));
	if (!(data->cub_file))
		return (print_error(ERR_MALLOC), clean_exit(data, FAILURE));
	data->cub_path = cub_path;
	if (DEBUG)
		printf("\n.cub file contains %d lines\n", data->cub_height);
	data->cub_fd = open_file(cub_path, data);
	read_and_save_cub_file(row, col, i, data);
	if (DEBUG)
	{	
		printf("\n------------- .cub ----------------\n");
		print_array_2d(data->cub_file);
		printf("\n-----------------------------------\n\n");
	}
	close(data->cub_fd);
}
