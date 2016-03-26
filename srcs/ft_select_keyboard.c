/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_keyboard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

static void	ft_select_keyboard_up_down(t_select *select, int is_up)
{
	if (is_up)
	{
		if (select->cursor_index == 0)
			select->cursor_index = ft_lstcount(select->list) - 1;
		else
		{
			select->cursor_index--;
		}
	}
	else
	{
		if (select->cursor_index == (ft_lstcount(select->list) - 1))
			select->cursor_index = 0;
		else
		{
			select->cursor_index++;
		}
	}
}

static void	ft_select_keyboard_right_left(t_select *s, int is_right)
{
	t_selector	*selector;

	selector = NULL;
	if (is_right)
	{
		if (ft_lstget_at(s->list, s->cursor_index - 1))
			selector =
				ft_lstget_at(s->list, s->cursor_index - 1)->content;
		if (ft_lstget_at(s->list, s->cursor_index + s->win.ws_row))
			s->cursor_index += s->win.ws_row;
		else if (selector && ft_lstget_at(s->list, selector->y))
			s->cursor_index = selector->y;
		else
			s->cursor_index = 0;
	}
	else
	{
		if (ft_lstget_at(s->list, s->cursor_index - s->win.ws_row))
			s->cursor_index -= s->win.ws_row;
		else if (ft_lstget_at(s->list,
			s->cursor_index + (s->win.ws_row * COLS)))
			s->cursor_index += s->win.ws_row * COLS;
		else
			s->cursor_index = ft_lstcount(s->list) - 1;
	}
}

static void	ft_select_keyboard_select(t_select *select)
{
	t_selector *selector;

	selector = NULL;
	if (ft_lstget_at(select->list, select->cursor_index))
	{
		selector = ft_lstget_at(select->list,
			select->cursor_index)->content;
		selector->is_selected = !selector->is_selected;
		if (select->cursor_index == (ft_lstcount(select->list) - 1))
			select->cursor_index = 0;
		else
			select->cursor_index++;
	}
}

static void	ft_select_keyboard_delete(t_select *select)
{
	if (ft_lstget_at(select->list, select->cursor_index))
	{
		ft_lstdel_at(&select->list, select->cursor_index,
			&ft_select_free_selector);
		select->cursor_index = (select->cursor_index > 0) ?
		select->cursor_index - 1 : 0;
		ft_init_max_len(select);
	}
	if (ft_lstcount(select->list) == 0)
		ft_select_events_exit(0);
}

int			ft_select_keyboard(t_select *select)
{
	char buf[3];

	ft_bzero(buf, 3);
	read(0, buf, 3);
	if (TOP)
		ft_select_keyboard_up_down(select, 1);
	else if (BOTTOM)
		ft_select_keyboard_up_down(select, 0);
	else if (RIGHT)
		ft_select_keyboard_right_left(select, 1);
	else if (LEFT)
		ft_select_keyboard_right_left(select, 0);
	else if (SPACE)
		ft_select_keyboard_select(select);
	else if (BACK_SPACE || DELETE)
		ft_select_keyboard_delete(select);
	else if (ENTER)
	{
		ft_select_reset(select);
		ft_select_print_selected(select, select->list);
		ft_select_free_env();
	}
	else if (EXIT)
		ft_select_events_exit(0);
	return (1);
}
