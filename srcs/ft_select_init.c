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

t_select	*ft_select_recover(void)
{
	static t_select	select;

	return (&select);
}

void		ft_init_max_len(t_select *select)
{
	size_t 			len;
	t_selector	*selector;
	t_list 			*cur;

	cur = select->list;
	select->max_len = 0;
	while (cur)
	{
		selector = cur->content;
		len = ft_strlen(selector->str);
		if (len > select->max_len)
			select->max_len = len;
		cur = cur->next;
	}
}
void	ft_select_init_select(t_select *select, int ac, char **av)
{
	int					i;
	t_selector	selector;

	select->list = NULL;
	i = 1;
	select->cursor_index = 0;
	select->cursor_x = 0;
	select->cursor_y = 0;
	select->max_len = 0;
	while (i < ac)
	{
		selector.str = ft_strdup(av[i]);
		selector.is_selected = 0;
		if (ft_strlen(selector.str) > select->max_len)
			select->max_len = ft_strlen(selector.str);
		ft_lstadd(&(select->list), ft_lstnew(&selector, sizeof(t_selector)));
		i++;
	}
	if (select->list)
		ft_lstrev(&(select->list));
	ft_init_max_len(select);
}

int		ft_select_init_termcaps(t_select *select)
{ 
	char	buff_env[4096];

  if ((select->term_name = getenv("TERM")) == NULL)
     return (0);
  if (tgetent(buff_env, select->term_name) != 1)
     return (0);
  if (tcgetattr(0, &select->term) == -1)
     return (0);
  select->tty = open("/dev/tty", O_RDWR);
	select->term.c_lflag &= ~(ICANON);
	select->term.c_lflag &= ~(ECHO);
	select->term.c_cc[VMIN] = 1;
	select->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &select->term) == -1)
		return (0);
	tputs(tgetstr("cl", NULL), 0, tputs_putchar);
	return (1);
}

int		ft_select_reset(t_select *select)
{ 
	char	buff_env[4096];

  if ((select->term_name = getenv("TERM")) == NULL)
     return (0);
  if (tgetent(buff_env, select->term_name) != 1)
     return (0);
  if (tcgetattr(0, &select->term) == -1)
     return (0);
  tputs(tgetstr("cl", NULL), 0, tputs_putchar);
  tputs(tgetstr("te", NULL), 0, tputs_putchar);
	tputs(tgetstr("ve", NULL), 0, tputs_putchar);
	select->term.c_lflag = (ICANON | ECHO | ISIG);
	if (tcsetattr(0, TCSADRAIN, &select->term) == -1)
		return (0);
	return (1);
}

int		ft_select_init_window(t_select *select)
{
	if (ioctl(0, TIOCGWINSZ, &select->win) != -1)
		ft_select_print(select->list);
	return (1);
}
