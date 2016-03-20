/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_events_go_foreground.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void	ft_select_events_go_foreground(int i)
{
	signal(SIGTSTP, ft_select_event);
	signal(SIGQUIT, ft_select_event);
	ft_select_init_termcaps(ft_select_recover());
	ft_select_init_window(ft_select_recover());
	UNUSED(i);
}
