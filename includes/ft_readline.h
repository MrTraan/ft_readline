/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 14:58:40 by ngrasset          #+#    #+#             */
/*   Updated: 2016/02/04 19:28:10 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H
# include <libft.h>
# include <unistd.h>
# include <stdlib.h>
# include <term.h>
# include <curses.h>
# include <fcntl.h>
# define RL_BUFF_SIZE 100

typedef struct			s_rl_hist
{
	struct s_rl_hist	*prev;
	struct s_rl_hist	*next;
	char				*cmd;
}						t_rl_hist;

typedef struct			s_reader_hist
{
	t_rl_hist			*head;
	t_rl_hist			*cur;
	t_rl_hist			*tail;
	char				*filename;
}						t_reader_hist;

typedef struct			s_rl_reader
{
	char				*line;
	int					cursor;
	int					end;
	int					size;
	void				(*prompt)(void);
	char				*term_name;
	t_reader_hist		*hist;
}						t_rl_reader;

typedef int				(*t_rl_key_fn)(t_rl_reader *, long);

typedef struct			s_rl_keybind
{
	long				key;
	t_rl_key_fn			fn;
}						t_rl_keybind;

t_rl_reader				*ftrl_init(void);
char					*ft_readline(t_rl_reader *r, char *prompt);
void					ftrl_exit(t_rl_reader *r);


t_rl_key_fn				rl_sp_key(long key);
int						rl_backdel(t_rl_reader *r, long key);
int						rl_exit(t_rl_reader *r, long key);
int						rl_backward_char(t_rl_reader *r, long key);
int						rl_forward_char(t_rl_reader *r, long key);
int						rl_backward_word(t_rl_reader *r, long key);
int						rl_forward_word(t_rl_reader *r, long key);
int						rl_hist_get_previous(t_rl_reader *r, long key);
int						rl_hist_get_next(t_rl_reader *r, long key);


int						ftrl_init_history(t_rl_reader *r, char *filename);
int						ftrl_save_history(t_rl_reader *r);
t_rl_hist				*rl_hist_new_entry(char *cmd);
t_rl_hist				*rl_hist_push(t_rl_hist **head, t_rl_hist *new);
void					ftrl_delete_history(t_rl_hist **head);

int						reader_write(t_rl_reader *r, char *str);
int						reader_write_char(t_rl_reader *r, char c);
int						reader_clear(t_rl_reader *r);

int						init_tty(char *term_name);
int						reset_tty(char *term_name);

int						exec_tcaps(char *code);
int						exec_tcaps_n(char *code, int n);
#endif
