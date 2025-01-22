/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:45:27 by corin             #+#    #+#             */
/*   Updated: 2025/01/22 14:09:24 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*ft_strdup(const char *str)
{
	char	*new_str;
	int		i;

	i = 0;
	if (!str)
		return (ft_strdup(""));
	while (str[i])
		i++;
	new_str = ft_calloc(i + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	return (new_str);
}

char	*join_strs(const char *s1, const char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	result = ft_calloc(i + j + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		result[i] = s1[i];
	while (s2[++j])
		result[i + j] = s2[j];
	return (result);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	index;

	index = 0;
	while ((s1[index] != '\0' || s2[index] != '\0') && n--)
	{
		if (s1[index] != s2[index])
			return ((unsigned char)s1[index] - (unsigned char)s2[index]);
		index++;
	}
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || (c <= 13 && c >= 11) || c == 9)
		return (1);
	return (0);
}

void	strip_whitespace(char *str)
{
	char	*write_ptr;
	char	*read_ptr;

	if (!str)
		return ;
	write_ptr = str;
	read_ptr = str;
	while (*read_ptr != '\0')
	{
		if (!ft_isspace((unsigned char)*read_ptr)
			&& (unsigned char)*read_ptr != '\n')
		{
			*write_ptr++ = *read_ptr;
		}
		read_ptr++;
	}
	*write_ptr = '\0';
}
