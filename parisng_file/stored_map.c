/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stored_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 08:58:52 by achamdao          #+#    #+#             */
/*   Updated: 2025/07/22 13:07:18 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	**return_map(char *arr, int fd)
{
	char	**matrex;

	close(fd);
	if (!arr)
		return (NULL);
	arr = ft_strjoin(arr, "\n", 1);
	if (!arr)
		return (NULL);
	matrex = ft_split(arr, ':');
	free(arr);
	return (matrex);
}

char	*get_map(int fd)
{
	char	*arr1;
	char	*arr_map;
	int		count;

	count = 0;
	arr1 = NULL;
	arr_map = NULL;
	arr1 = get_next_line(fd);
	while (arr1)
	{
		arr_map = ft_strjoin(arr_map, ":", 1);
		arr_map = ft_strjoin(arr_map, arr1, 1);
		if (!arr_map)
			return (close(fd), free(arr1), free(arr_map), NULL);
		free(arr1);
		arr1 = get_next_line(fd);
	}
	return (arr_map);
}

char	**stored_map(char *name)
{
	int		fd;
	char	*arr_map;

	arr_map = NULL;
	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nIn map file");
		return (NULL);
	}
	arr_map = get_map(fd);
	return (return_map(arr_map, fd));
}
