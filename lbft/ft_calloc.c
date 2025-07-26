/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:51:40 by achamdao          #+#    #+#             */
/*   Updated: 2025/04/23 19:18:26 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*arr;

	if (!size || !num)
		return (malloc(0));
	if (num > SIZE_MAX / size)
		return (NULL);
	arr = NULL;
	arr = malloc(num * size);
	if (arr == NULL)
		return (NULL);
	ft_memset(arr, 0, (num * size));
	return (arr);
}
