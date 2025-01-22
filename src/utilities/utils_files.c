/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:31:34 by ccraciun          #+#    #+#             */
/*   Updated: 2025/01/22 14:09:09 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	file_exists_open(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		return (true);
	}
	return (false);
}
