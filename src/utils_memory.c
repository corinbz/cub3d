/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corin <corin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:44:52 by corin             #+#    #+#             */
/*   Updated: 2024/12/16 10:45:15 by corin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	void			*result;
	unsigned char	*p;

	result = malloc(num_elements * element_size);
	if (!result)
		return (NULL);
	p = (unsigned char *)result;
	while (num_elements != 0)
	{
		*p = '\0';
		p++;
		num_elements--;
	}
	return (result);
}