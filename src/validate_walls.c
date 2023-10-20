/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 01:44:54 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/10/06 16:51:11 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
dr: "delta row"
used to determine the row index for the next cell to visit during DFS,
each value represents a move in the vertical direction (up or down),
values are set to -1, 0, 1, 0 to represent:
	moving up, 
	(no vertical movement), 
	moving down, 
	(no vertical movement)
	
dc: "delta column"
used to determine the column index for the next cell to visit during DFS,
each value represents a move in the horizontal direction (left or right),
values are set to 0, 1, 0, -1 to represent
	(no horizontal movement),
	moving right, 
	(no horizontal movement), 
	moving left

using these arrays in the dfs_recursive function, 
loop through them to check all four possible directions from the current cell.
example: r + map_data->dr[i] and c + map_data->dc[i] gives us the indices of 
the cell in the direction specified by i from the current cell (r, c)
*/
void	init_map_data(t_dfs *map_data, t_data *data, char **map_clone)
{
	map_data->map = map_clone;
	map_data->h = data->map_height;
	map_data->w = data->map_width;
	map_data->valid = 1;
	map_data->dr[0] = -1;
	map_data->dr[1] = 0;
	map_data->dr[2] = 1;
	map_data->dr[3] = 0;
	map_data->dc[0] = 0;
	map_data->dc[1] = 1;
	map_data->dc[2] = 0;
	map_data->dc[3] = -1;
}

/*
performs depth-first search on the map from a given starting point
checks whether a given point is within the map and whether it's traversable.
If a point is outside the map or not traversable, 
the map is marked as invalid.

two integers (r and c) representing current position in the map
*/
void	dfs_recursive(t_dfs *map_data, int r, int c)
{
	int	i;

	if (r < 0 || c < 0 || r >= map_data->h || c >= map_data->w)
	{
		map_data->valid = 0;
		return ;
	}
	if (map_data->map[r][c] == '1' || map_data->map[r][c] == '.')
		return ;
	map_data->map[r][c] = '.';
	i = -1;
	while (++i < 4)
		dfs_recursive(map_data, r + map_data->dr[i], c + map_data->dc[i]);
}

/*
runs the depth-first search algorithm on every valid starting point on the map.
if any of the searches result in an invalid map, 
it stops the search and returns 0
*/
int	dfs(t_data *data, char **map_clone)
{
	t_dfs	map_data;
	int		i;
	int		j;

	init_map_data(&map_data, data, map_clone);
	i = -1;
	while (++i < map_data.h)
	{
		j = -1;
		while (++j < map_data.w)
		{
			if (map_data.map[i][j] == '0' || map_data.map[i][j] == 'N'
				|| map_data.map[i][j] == 'E' || map_data.map[i][j] == 'W'
				|| map_data.map[i][j] == 'S')
				dfs_recursive(&map_data, i, j);
		}
	}
	return (map_data.valid);
}

/*
added this function extra, 
bc dfs didn't work correctly with '\0'
*/
int	is_last_char_one(const char *line)
{
	int	len;
	int	i;

	len = ft_strlen(line);
	i = len - 1;
	while (i >= 0 && line[i] == ' ')
		i--;
	if (i >= 0 && ft_isprint_no_space(line[i]))
	{
		if (line[i] == '1')
			return (SUCCESS);
		return (FAILURE);
	}
	return (FAILURE);
}

int	validate_walls(t_data *data)
{
	char	**map_clone;
	int		i;
	int		valid;

	i = 0;
	while (i < data->map_height)
	{
		if (is_last_char_one(data->map[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	map_clone = malloc(data->map_height * sizeof(char *));
	i = -1;
	while (++i < data->map_height)
		map_clone[i] = ft_strdup2(data->map[i], data->map_width);
	valid = dfs(data, map_clone);
	i = -1;
	while (++i < data->map_height)
		free(map_clone[i]);
	free(map_clone);
	if (valid)
		return (SUCCESS);
	return (FAILURE);
}

//// ---------------------- norminette ---------------------------
// // Directions for DFS
// int dr[] = {-1, 0, 1, 0}; //up, right, down, left
// int dc[] = {0, 1, 0, -1};

// int is_valid(int r, int c, int height, int width) {
//     return r >= 0 && r < height && c >= 0 && c < width;
// }

// void dfs(char **map, int r, int c, int h, int w, int *valid) {
//     if (r < 0 || c < 0 || r >= h || c >= w) {
//         // We've hit a border, the map is invalid
//         *valid = 0;
//         return;
//     }
//     if (map[r][c] == '1' || map[r][c] == '.') {
//         // We've hit a wall or already visited point, so we stop
//         return;
//     }

//     // Mark this point as visited
//     map[r][c] = '.';

//     // Continue DFS in each direction
//     dfs(map, r + 1, c, h, w, valid);
//     dfs(map, r - 1, c, h, w, valid);
//     dfs(map, r, c + 1, h, w, valid);
//     dfs(map, r, c - 1, h, w, valid);
// }

// int validate_walls(t_data *data) {
//     // Clone the map so we don't modify the original
//     char **map_clone = malloc(data->map_height * sizeof(char *));
//     for (int i = 0; i < data->map_height; i++) {
//         map_clone[i] = strdup(data->map[i]);
//     }

//     int valid = 1;
//     // Perform DFS from each walkable point
//     for (int i = 0; valid && i < data->map_height; i++) {
//         for (int j = 0; valid && j < data->map_width; j++) {
//             if (map_clone[i][j] == '0' || map_clone[i][j] == 'N' ||
//                 map_clone[i][j] == 'E' || map_clone[i][j] == 'W' || 
//                 map_clone[i][j] == 'S') {
//                 dfs(map_clone, i, j, data->map_height, 
//						data->map_width, &valid);
//             }
//         }
//     }

//     // Cleanup
//     for (int i = 0; i < data->map_height; i++) {
//         free(map_clone[i]);
//     }
//     free(map_clone);

//     if (valid) {
//         return SUCCESS;
//     } else {
//         return FAILURE;
//     }
// }
