/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 11:13:38 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/14 18:59:03 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <stdio.h>

void	ft_lstdelat(t_list **list, int at, void (*del)(void *, size_t))
{

	t_list	*tmp;
	t_list	*prev;
	int		count;
	
	if (!list || !(*list)) return ;
    tmp = *list;
    prev = NULL;
    count =	0;
	while (count != at && tmp->next != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
		count++;
	}
    if (count == at)
    {
        if (prev)
            prev->next = tmp->next;
        else
            *list = tmp->next;
        del(tmp, tmp->content_size);
    }
}
