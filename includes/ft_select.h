/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:24:29 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/20 14:15:23 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <libft.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>

# include <term.h>
# include <sys/ioctl.h>

# define UNUSED(x) (void)(x)

# define FT_SELECT() (void)(x)

typedef struct termios	t_termios;
typedef struct winsize	t_winsize;

typedef struct			s_selector
{
	char				*str;
	int					is_selected;
}						t_selector;

typedef struct			s_select
{
	t_list				*list;
	t_termios			term;
	t_winsize			win;
	size_t				max_len;
	int					cursor_index;
	int					cursor_x;
	int					cursor_y;
	int					cols;
	char				*term_name;
}						t_select;

t_select	*ft_select_recover(void);
int			tputs_putchar(int c);
void		ft_select_init_select(t_select *select, int ac, char **av);
int			ft_select_init_termcaps(t_select *select);
int			ft_select_init_window(t_select *select);
void		ft_select_print(t_list *list);
void		ft_select_event(int i);
int			ft_select_reset(t_select *select);
void		ft_select_errors_usage(void);
void		ft_select_events_exit(int i);
void		ft_select_events_go_background(int i);
void		ft_select_events_go_foreground(int i);
void		ft_select_events_resize(int i);

#endif
