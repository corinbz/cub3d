/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:44:52 by corin             #+#    #+#             */
/*   Updated: 2025/01/22 14:09:13 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	void			*result;
	unsigned char	*p;
	size_t			total_size;

	total_size = num_elements * element_size;
	result = malloc(total_size);
	if (!result)
		return (NULL);
	p = (unsigned char *)result;
	while (total_size != 0)
	{
		*p = '\0';
		p++;
		total_size--;
	}
	return (result);
}

void	ft_free_2d(char **arr)
{
	size_t	i;

	i = 0;
	if (arr != NULL)
	{
		while (arr[i] != NULL)
		{
			free(arr[i]);
			arr[i] = NULL;
			i++;
		}
		free(arr);
		arr = NULL;
	}
}
