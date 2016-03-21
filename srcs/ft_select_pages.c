/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_pages.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

int	ft_select_get_max_words_by_page(void)
{
	t_select	*select;
	int			cols;

	select = ft_select_recover();
	cols = ((select->win.ws_col) / (select->max_len + 2));
	return (cols * select->win.ws_row);
}

int	ft_select_get_pages(void)
{
	t_select	*select;
	int			pages;
	int			words;

	select = ft_select_recover();
	words = ft_lstcount(select->list);
	select = ft_select_recover();
	if (ft_select_get_max_words_by_page() == 0)
		return (0);
	pages = words / ft_select_get_max_words_by_page();
	pages++;
	return (pages);
}

int	ft_selected_get_page_offset(void)
{
	t_select	*select;
	int			words_by_page;

	select = ft_select_recover();
	words_by_page = ft_select_get_max_words_by_page();
	if (words_by_page == 0)
		return (0);
	return (words_by_page * ((select->cursor_index) / words_by_page));
}
