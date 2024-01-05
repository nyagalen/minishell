# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 23:06:33 by svydrina          #+#    #+#              #
#    Updated: 2024/01/05 16:39:38 by svydrina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = test_getline.c path.c error.c built_in.c env.c env_utils.c

OBJS = $(SRCS:.c=.o)

CC = gcc -Wall -Werror -Wextra

INCLUDES = -I. -Ilibft -I/usr/include

LIBFT = libft/libft.a

RL_FLAGS = -L/usr/local/lib -I/usr/local/include -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $(NAME) $(OBJS) $(RL_FLAGS) $(LIBFT)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) -o $@ -c $< $(INCLUDES)

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
