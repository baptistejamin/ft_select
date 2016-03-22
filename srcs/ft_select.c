/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/21 18:53:53 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void		ft_select_event(int i)
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

t_select	*ft_select_recover(void)
{
	static t_select	select;

	return (&select);
}

int			main(int ac, char **av)
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
	if (!ft_select_init_termcaps(select))
	{
		ft_putendl_fd("Cannot show on tty", 2);
		ft_select_events_exit(0);
	}
	while (1)
	{
		ft_select_init_window(select);
		ft_select_keyboard(select);
	}
	return (0);
}
