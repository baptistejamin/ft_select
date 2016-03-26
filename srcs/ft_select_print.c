/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>
#include <printf.h>

int			tputs_putchar(int c)
{
	t_select	*select;

	select = ft_select_recover();
	write(select->tty, &c, 1);
	return (1);
}

static void	ft_select_print_one(t_selector *selector, int index, int *x, int *y)
{
	t_select	*select;

	select = ft_select_recover();
	if ((index + ft_selected_get_page_offset()) == select->cursor_index)
	{
		tputs(tgetstr("us", NULL), 0, tputs_putchar);
		select->cursor_x = *x;
		select->cursor_y = *y - 1;
	}
	if (*y == select->win.ws_row)
	{
		*y = 0;
		select->cols++;
		*x += select->max_len + 2;
	}
	if (selector->is_selected)
		tputs(tgetstr("mr", NULL), 0, tputs_putchar);
	ft_putstr_fd(selector->str, select->tty);
	selector->y = *y;
	tputs(tgetstr("me", NULL), 0, tputs_putchar);
	tputs(tgoto(tgetstr("cm", NULL), *x, *y), 1, tputs_putchar);
}

void		ft_select_print(t_select *select, t_list *list)
{
	t_list				*cur;
	t_selector			*selector;
	int					y;
	int					x;
	int					index;

	y = 1;
	x = 0;
	index = 0;
	select->cols = 1;
	tputs(tgetstr("cl", NULL), 0, tputs_putchar);
	tputs(tgetstr("ho", NULL), 0, tputs_putchar);
	cur = ft_lstget_at(list, ft_selected_get_page_offset());
	if (ft_select_get_max_words_by_page() == 0)
		ft_putstr_fd("Window size is too small", select->tty);
	while (cur && index < ft_select_get_max_words_by_page())
	{
		selector = cur->content;
		ft_select_print_one(selector, index, &x, &y);
		y++;
		index++;
		cur = cur->next;
	}
	tputs(tgoto(tgetstr("cm", NULL), select->cursor_x, select->cursor_y), 1,
		tputs_putchar);
}

void		ft_select_print_selected(t_select *select, t_list *list)
{
	t_list			*cur;
	t_selector		*selector;
	int				y;
	int				x;
	int				index;

	UNUSED(select);
	y = 1;
	x = 0;
	index = 0;
	cur = list;
	while (cur)
	{
		selector = cur->content;
		if (selector->is_selected)
		{
			if (index > 0)
				ft_putstr_fd(" ", 1);
			ft_putstr_fd(selector->str, 1);
		}
		index++;
		cur = cur->next;
	}
	exit(0);
}
