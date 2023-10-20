/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:20:17 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/10/06 21:30:20 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*ft_strdup2(const char *s1, int len)
{
	char	*copy;

	copy = ft_calloc(len + 1, sizeof(char));
	if (!copy)
		return (NULL);
	ft_memcpy(copy, s1, (ft_strlen(s1) + 1));
	return (copy);
}

int	open_file(char *filepath, t_data *data)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		print_error("ERR_OPEN");
		clean_exit(data, FAILURE);
	}
	return (fd);
}
