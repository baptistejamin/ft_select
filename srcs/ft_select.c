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

int		tputs_putchar(int c)
{
	t_select	*select;

	select = ft_select_recover();
	write(select->tty, &c, 1);
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

int		ft_select_get_max_words_by_page(void)
{
	t_select		*select;
	int 				cols;

	select = ft_select_recover();
	cols = ((select->win.ws_col) / 	(select->max_len + 2));
	return (cols * select->win.ws_row);
}

int		ft_select_get_pages(void)
{
	t_select		*select;
	int 				pages;
	int 				words;

	select = ft_select_recover();
	words = ft_lstcount(select->list);
	select = ft_select_recover();
	if (ft_select_get_max_words_by_page() == 0)
		return (0);
	pages = words / ft_select_get_max_words_by_page();
	pages++;
	//printf("pages = %d\n", pages);
	//printf("max_words = %d\n", ft_select_get_max_words_by_page());
	return pages;
}


int		ft_selected_get_page_offset(void)
{
	t_select		*select;
	int 				words_by_page;

	select = ft_select_recover();
	words_by_page = ft_select_get_max_words_by_page();
	if (words_by_page == 0)
		return (0);
	return (words_by_page * ((select->cursor_index) / words_by_page));
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
	cur = ft_lstget_at(list, ft_selected_get_page_offset());
	if (ft_select_get_max_words_by_page() == 0)
		ft_putstr_fd("Window size is too small", select->tty);
	while (cur && index < ft_select_get_max_words_by_page())
	{
		selector = cur->content;
		if ((index + ft_selected_get_page_offset()) == select->cursor_index)
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
		if (selector->is_selected)
			tputs(tgetstr("mr", NULL), 0, tputs_putchar);
		ft_putstr_fd(selector->str, select->tty);
		tputs(tgetstr("me", NULL), 0, tputs_putchar);
		tputs(tgoto(tgetstr("cm", NULL), x, y), 1, tputs_putchar);
		y++;
		index++;
		cur = cur->next;
	}
	tputs(tgoto(tgetstr("cm", NULL), select->cursor_x, select->cursor_y), 1, tputs_putchar);
}

void	ft_select_print_selected(t_list *list)
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
	cur = list;
	while (cur)
	{
		selector = cur->content;
		if (selector->is_selected)
		{
			if (index > 0)
				ft_putstr_fd(" ", select->tty);
			ft_putstr_fd(selector->str, select->tty);
		}
		index++;
		cur = cur->next;
	}
}

void	free_selector(void *content, size_t size)
{
	t_selector *selector;

	UNUSED(size);
	selector = content;
	if (selector->str)
		free(selector->str);
	free(content);
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
		if (ft_lstget_at(select->list, select->cursor_index))
		{
			selector = ft_lstget_at(select->list, select->cursor_index)->content;
			selector->is_selected = !selector->is_selected;
			if (select->cursor_index == (ft_lstcount(select->list) - 1))
				select->cursor_index = 0;
			else
				select->cursor_index++;
		}
		//Select
	}
	else if ((buf[0] == 127 && buf[1] == 0 && buf[2] == 0))
	{
		if (ft_lstget_at(select->list, select->cursor_index))
		{
			ft_lstdel_at(&select->list, select->cursor_index, &free_selector);
			select->cursor_index  = (select->cursor_index > 0) ? select->cursor_index - 1 : 0;
		}
	}
	else if ((buf[0] == 10 && buf[1] == 0 && buf[2] == 0))
	{
		ft_select_reset(select);
		ft_select_print_selected(select->list);
		exit(0);
	}
	else if ((buf[0] == 27 && buf[1] == 0 && buf[2] == 0))
	{
		ft_select_events_exit(0);
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
