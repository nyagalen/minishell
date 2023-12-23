# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svydrina <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 23:06:33 by svydrina          #+#    #+#              #
#    Updated: 2023/12/02 16:04:54 by svydrina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = test_getline.c path.c error.c built_in.c

OBJS = $(SRCS:.c=.o)

CC = gcc -Wall -Werror -Wextra

INCLUDES = -I. -Ilibft

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $(NAME) $(OBJS) $(LIBFT)

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
