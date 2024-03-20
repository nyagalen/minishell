# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 23:06:33 by svydrina          #+#    #+#              #
#    Updated: 2024/03/20 23:32:24 by svydrina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = src/path.c src/error.c src/built_in.c src/env.c \
src/env2.c src/env_utils.c src/create_tab/cmd_tab.c \
src/exit.c src/minishell.c src/test_getline.c \
src/unset.c src/echo.c src/utils.c src/shlvl.c \
src/utils/cmd_utils.c src/utils/print_utils.c src/utils/dollars_utils.c \
src/create_tab/cmd_conv.c src/create_tab/cmd_malloc1.c \
src/cmd_pars/cmd_pars1.c src/cmd_pars/cmd_pars2.c src/cmd_pars/cmd_pars3.c\
src/cmd_pars/check_buf.c src/cmd_pars/pars_errors.c src/cmd_pars/check_buf2.c\
src/cmd_pars/cmd_red.c\
src/error2.c src/pipe.c src/pipe2.c src/redir.c src/open_file.c src/no_pipe.c

OBJS = $(SRCS:.c=.o)

CC = cc -g3 -Wall -Werror -Wextra

INCLUDES = -I. -Ilib/libft -I/usr/include

LIBFT = lib/libft/libft.a

RL_FLAGS = -L/usr/local/lib -L/usr/include -I/usr/local/include -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $(NAME) $(OBJS) $(RL_FLAGS) $(LIBFT)
# @rm -f $(OBJS)

$(LIBFT):
	@make -C lib/libft

%.o: %.c
	@$(CC) -o $@ -c $< $(INCLUDES)

clean:
	rm -f $(OBJS)
	make -C lib/libft clean

fclean: clean
	rm -f $(NAME)
	make -C lib/libft fclean

re: fclean all

.PHONY: all clean fclean re
#note
#	$USER 		-> |buyuc|		vs $? 		-> |0|
#	$USERfdsf	-> ||			vs $?dfs 	-> |0dfs|
#	$USER"fdsf"	-> |buyucik|	vs $?"dfs"	-> |0dfs|
#	$"USER"		-> ||			vs $"?dfs" 	-> |?dfs|

