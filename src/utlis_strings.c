/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:45:27 by corin             #+#    #+#             */
/*   Updated: 2025/01/13 12:40:04 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

int ft_isspace(char c)
{
	if(c == ' ' || (c <= 13 && c >= 11) || c == 9)
		return 1;
	return 0;
}

void strip_whitespace(char *str)
{
	if (!str)
		return;

	char *write_ptr = str;
	char *read_ptr = str;

	while (*read_ptr != '\0') {
		if (!ft_isspace((unsigned char)*read_ptr)) {
			*write_ptr++ = *read_ptr;
		}
		read_ptr++;
	}

	*write_ptr = '\0';
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		str++;
		len++;
	}
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	index;

	result = 0;
	sign = 1;
	index = 0;
	while (ft_isspace(str[index]))
		index++;
	if (str[index] == '-')
	{
		sign = -1;
		index++;
	}
	else if (str[index] == '+')
		index++;
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = result * 10 + str[index] - '0';
		index++;
	}
	return (result * sign);
}

char	*ft_strchr(const char *s, int c)
{
	char	char_c;
	char	*char_s;
	int		i;

	i = 0;
	char_s = (char *)s;
	char_c = c;
	while (char_s[i] != char_c)
	{
		if (char_s[i] == '\0')
		{
			return (NULL);
		}
		i++;
	}
	return ((char *)char_s + i);
}