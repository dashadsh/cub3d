/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:59:34 by dgoremyk          #+#    #+#             */
/*   Updated: 2023/10/02 10:25:59 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	clean_exit(t_data *data, int exitstatus)
{
	if (data)
		free_data(data);
	exit(exitstatus);
}

int	quit_cub3d(t_data *data)
{
	clean_exit(data, 0);
	return (0);
}
