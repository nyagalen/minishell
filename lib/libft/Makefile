# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 16:53:50 by svydrina          #+#    #+#              #
#    Updated: 2024/04/02 04:45:01 by svydrina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS  = ft_atoi.c ft_isalpha.c ft_memchr.c ft_strchr.c ft_strlen.c ft_tolower.c\
	ft_bzero.c ft_isascii.c ft_memcmp.c ft_strdup.c ft_strncmp.c ft_toupper.c\
	ft_calloc.c ft_isdigit.c ft_memcpy.c ft_strlcat.c ft_strnstr.c \
	ft_isalnum.c ft_isprint.c ft_memset.c ft_strlcpy.c ft_strrchr.c\
	ft_memmove.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c\
	ft_putstr_fd.c ft_putendl_fd.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c\
	ft_putnbr_fd.c ft_strcmp.c get_next_line.c 

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
	ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OB_BON = $(BONUS:.c=.o)

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME) $(OB_BON)

bonus: $(OB_BON)
	ar rcs $(NAME) $(OB_BON)
	ranlib $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	ranlib $(NAME)

.c.o:
	cc $(CFLAGS) -c $< -o $@

clean:
	/bin/rm -f $(OBJS) $(OB_BON)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
