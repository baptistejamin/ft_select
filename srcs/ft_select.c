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

void	del_selector(void *elem, size_t content)
{
	t_selector	*selector;
	selector = ((t_list *)elem)->content;
	if(selector->str)
		free(selector->str);
	free(elem);
	content = 0;
}

int		tputs_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

void	ft_select_event(int i)
{
	if (i == SIGWINCH)
		ft_select_events_resize(i);
	else if (i == SIGTSTP)
		ft_select_events_go_background(i);
	else if (i == SIGCONT)
		ft_select_events_go_foreground(i);
	else if (i == SIGINT)
		ft_select_events_exit(i);
	else if (i == SIGQUIT)
		ft_select_events_exit(i);
}

void	ft_select_print(t_list *list)
{
	t_list			*cur;
	t_selector	*selector;
	t_select		*select;
	int					y;
	int					x;
	int 				index;

	y = 1;
	x = 0;
	index = 0;
	select = ft_select_recover();
	select->cols = 1;
	tputs(tgetstr("cl", NULL), 0, tputs_putchar);
	tputs(tgetstr("ho", NULL), 0, tputs_putchar);
	cur = list;
	while (cur)
	{
		if (index == select->cursor_index)
		{
			tputs(tgetstr("us", NULL), 0, tputs_putchar);
			select->cursor_x = x;
			select->cursor_y = y - 1;
		}
		if (y == select->win.ws_row)
		{
			y = 0;
			select->cols++;
			x += select->max_len + 2;
		}
		selector = cur->content;
		if (selector->is_selected)
			tputs(tgetstr("mr", NULL), 0, tputs_putchar);
		ft_putstr(selector->str);
		tputs(tgetstr("me", NULL), 0, tputs_putchar);
		tputs(tgoto(tgetstr("cm", NULL), x, y), 1, tputs_putchar);
		y++;
		index++;
		cur = cur->next;
	}
	tputs(tgoto(tgetstr("cm", NULL), select->cursor_x, select->cursor_y), 1, tputs_putchar);
}

int		ft_select_keyboard(t_select *select)
{
	char buf[3];
	t_selector *selector;

	selector = NULL;
	ft_bzero(buf, 3);
	read(0, buf, 3);
	if ((buf[0] == 27 && buf[1] == 91 && buf[2] == 65))
	{
		//Move top
		if (select->cursor_index == 0)
			select->cursor_index = ft_lstcount(select->list) - 1;
		else
		{
			select->cursor_index--;
		}
	}
	else if ((buf[0] == 27 && buf[1] == 91 && buf[2] == 66))
	{
		if (select->cursor_index == (ft_lstcount(select->list) - 1))
			select->cursor_index = 0;
		else
		{
			select->cursor_index++;
		}
	}
	else if ((buf[0] == 27 && buf[1] == 91 && buf[2] == 67))
	{
		if (ft_lstget_at(select->list, select->cursor_index + select->win.ws_row))
			select->cursor_index += select->win.ws_row;
		else if (ft_lstget_at(select->list, select->cursor_index - (select->win.ws_row * (select->cols - 1))))
			select->cursor_index -= (select->win.ws_row * (select->cols - 1));
	}
	else if ((buf[0] == 27 && buf[1] == 91 && buf[2] == 68))
	{
		if (ft_lstget_at(select->list, select->cursor_index - select->win.ws_row))
			select->cursor_index -= select->win.ws_row;
		else if (ft_lstget_at(select->list, select->cursor_index + (select->win.ws_row * (select->cols - 1))))
			select->cursor_index += (select->win.ws_row * (select->cols - 1));
	}
	else if ((buf[0] == 32 && buf[1] == 0 && buf[2] == 0))
	{
		//Select
	}
	else if ((buf[0] == 127 || buf[0] == 126) && buf[1] == 0 && buf[2] == 0)
	{
		//Delete
	}
	else if ((buf[0] == 10 && buf[1] == 0 && buf[2] == 0))
	{
		//Return
	}
	else if ((buf[0] == 27 && buf[1] == 0 && buf[2] == 0))
	{
		//Escape
	}
	return (1);
}


int		main(int ac, char **av)
{
	t_select	*select;

	select = ft_select_recover();
	if (ac == 1)
	{
		ft_select_errors_usage();
		return (1);
	}
	signal(SIGWINCH, ft_select_event);
	signal(SIGTSTP, ft_select_event);
	signal(SIGCONT, ft_select_event);
	signal(SIGINT, ft_select_event);
	signal(SIGQUIT, ft_select_event);
	ft_select_init_select(select, ac, av);
	ft_select_init_termcaps(select);
	//ft_lstiter(select.list, &show_str);
	while (1)
	{
		ft_select_init_window(select);
		ft_select_keyboard(select);
	}
	return (0);
}
