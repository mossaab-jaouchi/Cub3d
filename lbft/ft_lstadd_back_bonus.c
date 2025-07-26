/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:52:49 by achamdao          #+#    #+#             */
/*   Updated: 2024/11/07 13:56:16 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lstback;

	if (!new || !lst)
		return ;
	lstback = ft_lstlast(*lst);
	if (lstback == NULL)
		*lst = new;
	else
		lstback->next = new;
}
