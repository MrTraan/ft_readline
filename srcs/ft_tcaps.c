/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 15:53:36 by ngrasset          #+#    #+#             */
/*   Updated: 2016/01/25 15:31:24 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_readline.h>
#include <debug.h>

static int	my_putc(int a)
{
	return (write(2, &a, 1));
}

int			exec_tcaps(char *code)
{
	char	*cmd;

	cmd = tgetstr(code, NULL);
	if (!cmd)
		return (-1);
	return (tputs(cmd, 0, my_putc));
}

int			exec_tcaps_n(char *code, int n)
{
	int		ret;

	while (n > 0)
	{
		ret = exec_tcaps(code);
		if (ret != 0)
			return (ret);
		n--;
	}
	return (ret);
}
