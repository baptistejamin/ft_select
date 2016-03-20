/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>
#include <stdio.h>

void	del_selector(void *elem, size_t content)
{
	t_selector	*selector;
	selector = ((t_list *)elem)->content;
	if(selector->str)
		free(selector->str);
	free(elem);
	content = 0;
}
void	init_select(t_select *select, int ac, char **av)
{
	int					i;
	t_selector	selector;

	i = 1;
	while (i < ac)
	{
		selector.str = ft_strdup(av[i]);
		ft_lstadd(&(select->list), ft_lstnew(&selector, sizeof(t_selector)));
		i++;
	}
	ft_lstrev(&(select->list));
}

void	show_str(t_list *elem)
{
	t_selector	*selector;

	selector = elem->content;
	ft_putendl(selector->str);
}

int		main(int ac, char **av)
{
	t_select	select;
	init_select(&select, ac, av);
	ft_lstiter(select.list, &show_str);
	return (0);
}
