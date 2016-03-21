/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void	ft_select_free_selector(void *content, size_t size)
{
	t_selector *selector;

	UNUSED(size);
	selector = content;
	if (selector->str)
		free(selector->str);
	free(content);
}

void	ft_select_free_env(void)
{
	t_select *select;

	select = ft_select_recover();
	ft_lstdel(&select->list, &ft_select_free_selector);
}
