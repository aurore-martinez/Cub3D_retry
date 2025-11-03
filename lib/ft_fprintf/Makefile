# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eieong <eieong@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/03 14:26:20 by eieong            #+#    #+#              #
#    Updated: 2025/11/03 14:26:46 by eieong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftfprintf.a

CC = cc

CFLAGS = -Wall -Werror -Wextra -I ./

SRCS = ft_fprintf.c ft_fprintothers.c

OBJS = ${SRCS:.c=.o}

RM = rm -rf

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	ar -rsc ${NAME} ${OBJS}

all: ${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
