/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:02:15 by achamdao          #+#    #+#             */
/*   Updated: 2024/11/07 10:54:32 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest_str, const void *src_str, size_t numBytes)
{
	char		*dest;
	const char	*src;

	if (!dest_str && !src_str)
		return (NULL);
	dest = (char *)dest_str;
	src = (const char *)src_str;
	if (dest == src || numBytes == 0)
		return (dest_str);
	if (src < dest)
	{
		dest += numBytes;
		src += numBytes;
		while (numBytes--)
		{
			*(--dest) = *(--src);
		}
	}
	else
	{
		while (numBytes--)
			*dest++ = *src++;
	}
	return (dest_str);
}
