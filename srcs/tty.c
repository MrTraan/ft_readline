/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 15:00:56 by ngrasset          #+#    #+#             */
/*   Updated: 2016/02/04 04:17:41 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_readline.h>

int		init_tty(char *term_name)
{
	struct termios	term;

	tgetent(NULL, term_name);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	tcsetattr(0, TCSADRAIN, &term);
	//exec_tcaps("im");
	exec_tcaps("sc");
	return (0);
}

int		reset_tty(char *term_name)
{
	struct termios	term;

	tgetent(NULL, term_name);
	tcgetattr(0, &term);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, TCSADRAIN, &term);
	//exec_tcaps("ei");
	return (0);
}
