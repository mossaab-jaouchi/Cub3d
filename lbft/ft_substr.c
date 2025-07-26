/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:09:52 by achamdao          #+#    #+#             */
/*   Updated: 2024/11/17 08:06:30 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*arr;
	int		len_of_s;

	if (!s)
		return (NULL);
	len_of_s = ft_strlen(s);
	if (start >= (unsigned int)len_of_s)
	{
		arr = (char *)malloc(1);
		if (arr)
			arr[0] = '\0';
		return (arr);
	}
	if (len > (size_t)(len_of_s - start))
		len = len_of_s - start;
	arr = (char *)malloc(((len) + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	ft_strlcpy(arr, s + start, len + 1);
	arr[len] = '\0';
	return (arr);
}
