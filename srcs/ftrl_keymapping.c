/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftrl_keymapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 16:14:55 by ngrasset          #+#    #+#             */
/*   Updated: 2016/02/04 04:16:16 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_readline.h>
#include <debug.h>

t_rl_keybind	g_rl_key_map[] = {
	{127, &rl_backdel},
	{0x445b1b, &rl_backward_char},
	{0x435b1b, &rl_forward_char},
	{0x44323b315b1b, &rl_backward_word},
	{0x43323b315b1b, &rl_forward_word},
	{0x415b1b, &rl_hist_get_previous},
	{0x425b1b, &rl_hist_get_next},
	{-1, NULL}
};

t_rl_key_fn	rl_sp_key(long key)
{
	int		i;

	i = 0;
	while (g_rl_key_map[i].key != -1)
	{
		if (g_rl_key_map[i].key == key)
			return (g_rl_key_map[i].fn);
		i++;
	}
	return (NULL);
}

int		rl_backdel(t_rl_reader *r, long key)
{
	(void)key;
	if (r->cursor == 0)
		return (0);
	ft_memmove(r->line + r->cursor - 1, r->line + r->cursor, r->size - r->cursor);
	(r->end)--;
	//ft_memset(r->line + r->end, 0, r->size - r->end);
	rl_backward_char(r, 0);
	exec_tcaps("cd");
	ft_putstr(r->line + r->cursor);
	exec_tcaps_n("le", ft_strlen(r->line + r->cursor));
	return (0);
}

int		rl_backward_char(t_rl_reader *r, long key)
{
	(void)key;
	debug_log("arr left pressed");
	if (r->cursor > 0)
	{
		(r->cursor)--;
		exec_tcaps("le");
	}
	return (0);
}

int		rl_forward_char(t_rl_reader *r, long key)
{
	(void)key;
	debug_log("arr right pressed");
	if (r->cursor < r->end)
	{
		(r->cursor)++;
		exec_tcaps("nd");
	}
	return (0);
}

int		rl_backward_word(t_rl_reader *r, long key)
{
	(void)key;
	while (r->cursor > 0 && !ft_isspace(r->line[r->cursor]))
		rl_backward_char(r, 0);
	while (r->cursor > 0 && ft_isspace(r->line[r->cursor]))
		rl_backward_char(r, 0);
	while (r->cursor > 0 && !ft_isspace(r->line[r->cursor - 1]))
		rl_backward_char(r, 0);
	return (0);
}

int		rl_forward_word(t_rl_reader *r, long key)
{
	(void)key;
	while (r->cursor < r->end && !ft_isspace(r->line[r->cursor]))
		rl_forward_char(r, 0);
	while (r->cursor < r->end && ft_isspace(r->line[r->cursor]))
		rl_forward_char(r, 0);
	return (0);
}

int		rl_hist_get_previous(t_rl_reader *r, long key)
{
	(void)key;
	debug_log("get hist previous");
	if (!r->hist->cur)
		return (0);
	if (r->hist->cur->prev)
	{
		exec_tcaps("rc");
		exec_tcaps("cd");
		r->hist->cur = r->hist->cur->prev;
		reader_clear(r);
		reader_write(r, r->hist->cur->cmd);
		if (r->hist->cur->cmd)
			ft_putstr(r->hist->cur->cmd);
	}
	return (0);
}

int		rl_hist_get_next(t_rl_reader *r, long key)
{
	(void)key;
	debug_log("get hist next");
	if (!r->hist->cur)
		return (0);
	if (r->hist->cur->next)
	{
		exec_tcaps("rc");
		exec_tcaps("cd");
		r->hist->cur = r->hist->cur->next;
		reader_clear(r);
		reader_write(r, r->hist->cur->cmd);
		if (r->hist->cur->cmd)
			ft_putstr(r->hist->cur->cmd);
	}
	return (0);
}
