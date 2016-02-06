/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 15:58:57 by ngrasset          #+#    #+#             */
/*   Updated: 2016/01/19 17:36:31 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_readline.h>
#include <stdio.h>

void	debug_put_key(long key)
{
	FILE	*f = fopen("readline.debug", "a+");

	fprintf(f, "KEY PRESSED: %lx\n", key);
	fclose(f);
}

void	debug_log(char *msg)
{
	FILE	*f = fopen("readline.debug", "a+");

	fprintf(f, "%s\n", msg);
	fclose(f);
}
