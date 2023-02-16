# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 12:26:34 by tmejri            #+#    #+#              #
#    Updated: 2023/02/16 13:55:44 by tmejri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo

SRCS			= check_simu.c error.c free.c init.c main.c parsing.c routine.c \
				tools.c tools_init.c \

OBJS			= ${SRCS:.c=.o}

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g3 -pthread 
# CFLAGS			+= -fsanitize=thread


all:			${NAME}

${NAME}:		${OBJS}
						${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
						${RM} ${OBJS}

fclean:			clean
						${RM} ${NAME}

re:				fclean ${NAME}

.PHONY:			all clean fclean re