# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/06 16:16:22 by minsunki          #+#    #+#              #
#    Updated: 2021/09/30 16:41:23 by minsunki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

FIL_M		=	philo.c \
				main.c \
				meta.c \
				utils.c

OBJ_M		=	$(FIL_M:.c=.o)

CC			=	gcc
CFLAG		=	-Wall -Wextra -Werror
RM			=	rm -f
MAKE		=	make

%.o			:	%.c
			$(CC) $(CFLAG) -c $< -o $@

all			:	$(NAME)

$(NAME)		:	$(OBJ_M)
			$(CC) $(OBJ_M) $(CFLAG) -lpthread -o $(NAME)

bonus		:	$(all)

clean		:
			$(RM) $(OBJ_M)

fclean		:	clean
			$(RM) $(NAME)

re			:	fclean
				$(MAKE) all

.PHONY		:	all clean fclean re bonus
