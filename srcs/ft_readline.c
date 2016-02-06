/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 14:53:32 by ngrasset          #+#    #+#             */
/*   Updated: 2016/02/04 19:28:45 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_readline.h>
#include <debug.h>

t_rl_reader	*ftrl_init(void)
{
	t_rl_reader		*r;

	r = (t_rl_reader *)malloc(sizeof(t_rl_reader));
	if (!r)
		return (NULL);
	r->line = NULL;
	r->size = 0;
	r->cursor = 0;
	r->end = 0;
	r->hist = NULL;
	r->term_name = getenv("TERM");
	if (!r->term_name)
	{
		ft_putendl("Coudln't init ft_readline: $TERM is not set");
		return (NULL);
	}
	return (r);
}

void		ftrl_exit(t_rl_reader *r)
{
	if (!r)
		return ;
	if (r->hist)
	{
		ftrl_delete_history(&(r->hist->head));
		if (r->hist->filename)
			free(r->hist->filename);
		free(r->hist);
	}
	free(r);
}

char		*ft_readline(t_rl_reader *r, char *prompt)
{
	long					key;
	t_rl_key_fn				sp;

	r->line = NULL;
	if (reader_clear(r) != 0)
		return (NULL);
	key = 0;
	if (r->hist)
	{
		r->hist->tail = rl_hist_push(&(r->hist->head), rl_hist_new_entry(NULL));
		r->hist->cur = r->hist->tail;
	}
	ft_putstr(prompt);
	if (init_tty(r->term_name) != 0)
		return (NULL);
	while (1)
	{
		key = 0;
		if (read(0, &key, sizeof(long)) == -1)
			return (NULL);
		debug_put_key(key); //
		if (key == '\n')
			break ;
		if ((sp = rl_sp_key(key)))
		{
			if (sp(r, key) != 0)
			{
				exec_tcaps("ei");
				return (NULL);
			}
			continue ;
		}
		//write(1, &key, 1);
		reader_write_char(r, (char)key);
		exec_tcaps("cd");
		ft_putstr(r->line + r->cursor - 1);
		exec_tcaps_n("le", ft_strlen(r->line + r->cursor));
	}
	if (r->hist)
		r->hist->tail->cmd = ft_strdup(r->line);
	reset_tty(r->term_name);
	return (r->line);
}
