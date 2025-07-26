/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:29:11 by achamdao          #+#    #+#             */
/*   Updated: 2025/07/22 13:06:24 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	*find_newline(char *s)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == '\n')
			return (s);
		s++;
	}
	return (NULL);
}

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	char	*dest_dup;

	if (!src)
		return (NULL);
	i = 0;
	dest_dup = (char *)malloc((n + 1) * sizeof(char));
	if (!dest_dup)
		return (NULL);
	while (src[i] && i < n)
	{
		dest_dup[i] = src[i];
		i++;
	}
	dest_dup[i] = '\0';
	return (dest_dup);
}

char	*exact_line(char **buff)
{
	char	*new_line;
	char	*remainder;
	char	*line;

	new_line = find_newline(*buff);
	if (new_line)
	{
		line = ft_strndup(*buff, new_line - *buff + 1);
		remainder = ft_strdup(new_line + 1);
		free(*buff);
		*buff = remainder;
	}
	else
	{
		line = ft_strdup(*buff);
		free(*buff);
		*buff = NULL;
	}
	return (line);
}

char	get_string(char	**arr, char **buff, int fd)
{
	int	bytes_ofread;
	
	while (!find_newline(*buff))
	{
		bytes_ofread = read(fd, *arr, BUFFER_SIZE);
		if (bytes_ofread < 0)
			return (free(*arr), free(*buff), 0);
		if (bytes_ofread == 0)
			break ;
		(*arr)[bytes_ofread] = '\0';
		*buff = ft_strjoin(*buff, *arr, 1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*arr;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	arr = (char *)malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	get_string(&arr, &buff, fd);
	free(arr);
	if (!buff || !*buff)
	{
		free(buff);
		buff = NULL;
		return (NULL);
	}
	return (exact_line(&buff));
}
