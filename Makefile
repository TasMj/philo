# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tas <tas@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 12:26:34 by tmejri            #+#    #+#              #
#    Updated: 2023/01/31 13:25:00 by tas              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo

SRCS			= check_simu.c error.c free.c init.c main.c parsing.c routine.c \
				tools.c \

OBJS			= ${SRCS:.c=.o}

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g3 -pthread 
# CFLAGS			+= -fsanitize=thread
# CFLAGS			+= -fsanitize=address


all:			${NAME}

${NAME}:		${OBJS}
						${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
						${RM} ${OBJS}

fclean:			clean
						${RM} ${NAME}

re:				fclean ${NAME}

.PHONY:			all clean fclean re