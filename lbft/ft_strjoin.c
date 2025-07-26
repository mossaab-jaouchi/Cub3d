/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:17:43 by achamdao          #+#    #+#             */
/*   Updated: 2025/05/03 21:11:50 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

char	*ft_strdup(const char *src)
{
	int		l;
	int		i;
	char	*dest_dup;

	i = 0;
	if (!src)
		return (NULL);
	l = ft_strlen(src);
	dest_dup = (char *)malloc(l + 1);
	if (!dest_dup)
		return (NULL);
	while (src[i])
	{
		dest_dup[i] = src[i];
		i++;
	}
	dest_dup[i] = '\0';
	return (dest_dup);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	free_str(char *str, char flag)
{
	if (flag)
		free(str);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2, char free_yes)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	if (!s2)
	{
		new_str = ft_strdup(s1);
		if (free_yes)
			free(s1);
		return (new_str);
	}
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = (char *)malloc(len1 + len2 + 1);
	if (!new_str)
		return (free_str(s1, free_yes), NULL);
	ft_strcpy(new_str, s1);
	ft_strcpy(new_str + len1, s2);
	free_str(s1, free_yes);
	return (new_str);
}
