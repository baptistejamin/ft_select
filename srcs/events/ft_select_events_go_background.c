/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_events_go_background.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void	ft_select_events_go_background(int i)
{
	char		cp[2];

	cp[0] = ft_select_recover()->term.c_cc[VSUSP];
	cp[1] = '\0';
	UNUSED(i);
	ft_putendl("go back");
	ft_select_reset(ft_select_recover());
	signal(SIGCONT, ft_select_event);
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, cp);
}
