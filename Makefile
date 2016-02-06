# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/19 14:48:52 by ngrasset          #+#    #+#              #
#    Updated: 2016/01/25 15:19:05 by ngrasset         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_readline.c 	ftrl_keymapping.c	ftrl_history.c	rl_reader.c\
	  tty.c				ft_tcaps.c
NAME = libftrl.a
INCLUDES = -I./includes -I../libft/includes
CFLAGS = -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)
CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $@ $^

debug: $(OBJ)
	$(CC) -c  $(INCLUDES) $(CFLAGS) srcs/debug.c
	ar -rcs $(NAME) $^ debug.o
	
%.o: srcs/%.c
	$(CC) -c  $(INCLUDES) $(CFLAGS) $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
