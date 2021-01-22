/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlyja <hlyja@ya.ru>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 14:29:29 by hlyja             #+#    #+#             */
/*   Updated: 2020/05/25 14:29:30 by hlyja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *cur_elem;

	while (*lst != NULL)
	{
		cur_elem = *lst;
		*lst = cur_elem->next;
		del(cur_elem->content);
		free(cur_elem);
	}
}
