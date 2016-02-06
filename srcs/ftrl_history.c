/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 16:15:57 by ngrasset          #+#    #+#             */
/*   Updated: 2016/01/25 16:30:47 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_readline.h>
#include <debug.h>

int				ftrl_init_history(t_rl_reader *r, char *filename)
{
	int			fd;
	char		*str;

	if (!(r->hist = malloc(sizeof(t_reader_hist))))
		return (-1);
	if (!(r->hist->filename = ft_strdup(filename)))
		return (-1);
	r->hist->head = NULL;
	fd = open(filename, O_RDONLY | O_CREAT, S_IRWXU);
	if (fd == -1)
		return (-1);
	while (get_next_line(fd, &str) == 1)
	{
		if (!str)
			return (-1);
		if (!*str)
		{
			free(str);
			continue ;
		}
		r->hist->tail = rl_hist_push(&(r->hist->head), rl_hist_new_entry(str));
		free(str);
	}
	r->hist->cur = r->hist->tail;
	close(fd);
	return (0);
}

int				ftrl_save_history(t_rl_reader *r)
{
	int			fd;
	t_rl_hist	*h;

	if (!r->hist)
		return (-1);
	fd = open(r->hist->filename, O_CREAT | O_TRUNC | O_RDWR, S_IRWXU);
	if (fd == -1)
		return (-1);
	h = r->hist->head;
	while (h)
	{
		if (h->cmd && *(h->cmd))
			ft_putendl_fd(h->cmd, fd);
		h = h->next;
	}
	close(fd);
	return (0);
}

t_rl_hist		*rl_hist_new_entry(char *cmd)
{
	t_rl_hist	*new;

	new = (t_rl_hist *)malloc(sizeof(t_rl_hist));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	if (cmd)
		new->cmd = ft_strdup(cmd);
	else
		new->cmd = NULL;
	return (new);
}

t_rl_hist		*rl_hist_push(t_rl_hist **head, t_rl_hist *new)
{
	t_rl_hist	*cur;

	if (!head)
		return (NULL);
	if (!*head)
	{
		*head = new;
		return (new);
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	new->prev = cur;
	t_rl_hist	*debug;
	debug = *head;
	while (debug)
	{
		debug_log(debug->cmd);
		debug = debug->next;
	}
	return (new);
}

void			ftrl_delete_history(t_rl_hist **head)
{
	t_rl_hist	*cur;
	t_rl_hist	*next;

	cur = *head;
	while (cur)
	{
		if (cur->cmd)
			free(cur->cmd);
		next = cur->next;
		free(cur);
		cur = next;
	}
	*head = NULL;
}
