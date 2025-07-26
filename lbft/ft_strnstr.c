/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:09:04 by achamdao          #+#    #+#             */
/*   Updated: 2024/11/15 07:54:32 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (to_find[j] == '\0')
		return ((char *)str);
	if (!str && !len)
		return (NULL);
	while (str[i] != '\0' && len > i)
	{
		if (str[i] == to_find[0])
		{
			while (str[i + j] == to_find[j]
				&& to_find[j] != '\0' && len > (i + j))
				j++;
			if (to_find[j] == '\0')
				return ((char *)&str[i]);
			else
				j = 0;
		}
		i++;
	}
	return (0);
}
