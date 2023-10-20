/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:54:19 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/08/03 22:32:55 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	print_array_2d(char **array_2d)
{
	int	i;

	i = 0;
	while (array_2d[i])
	{
		printf("%s", array_2d[i]);
		i++;
	}
}

void	print_array_2d_newline(char **array_2d)
{
	int	i;

	i = 0;
	while (array_2d[i])
	{
		printf("line idx %d\n", i);
		printf("%s", array_2d[i]);
		printf("\n");
		i++;
	}
}
