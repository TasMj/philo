# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile(tas)                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 12:26:34 by tmejri            #+#    #+#              #
#    Updated: 2023/01/16 14:13:05 by tmejri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo

SRCS			=	main.c\
					error.c \
 					free.c\
					init.c\
					thread.c\
					tools.c 

OBJS			= ${SRCS:.c=.o}

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g3 -pthread 

all:			${NAME}

${NAME}:		${OBJS}
						${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
						${RM} ${OBJS}

fclean:			clean
						${RM} ${NAME}

re:				fclean ${NAME}

.PHONY:			all clean fclean re