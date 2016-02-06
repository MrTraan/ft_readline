/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/24 15:15:02 by ngrasset          #+#    #+#             */
/*   Updated: 2016/01/24 15:37:50 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_readline.h>

int		reader_write(t_rl_reader *r, char *str)
{
	if (!str)
		return (0);
	while ((int)(r->end + ft_strlen(str)) >= r->size)
	{
		r->line = ft_realloc(r->line, r->size, r->size + RL_BUFF_SIZE);
		if (!r->line)
			return (-1);
		r->size += RL_BUFF_SIZE;
	}
	if (r->cursor < r->end)
		ft_memmove(r->line + r->cursor + ft_strlen(str), r->line + r->cursor, r->end - r->cursor);
	ft_memcpy(r->line + r->cursor, str, ft_strlen(str));
	r->end += ft_strlen(str);
	r->cursor += ft_strlen(str);
	return (ft_strlen(str));
}

int		reader_write_char(t_rl_reader *r, char c)
{
	if (r->end + 1 >= r->size)
	{
		r->line = ft_realloc(r->line, r->size, r->size + RL_BUFF_SIZE);
		if (!r->line)
			return (-1);
		r->size += RL_BUFF_SIZE;
	}
	if (r->cursor < r->end)
		ft_memmove(r->line + r->cursor + 1, r->line + r->cursor, r->end - r->cursor);
	r->line[r->cursor] = c;
	r->cursor++;
	r->end++;
	return (0);
}

int		reader_clear(t_rl_reader *r)
{
	if (r->line)
		free(r->line);
	if (!(r->line = malloc(sizeof(char) * RL_BUFF_SIZE)))
		return (-1);
	ft_memset(r->line, 0, RL_BUFF_SIZE);
	r->cursor = 0;
	r->end = 0;
	r->size = RL_BUFF_SIZE;
	return (0);
}
