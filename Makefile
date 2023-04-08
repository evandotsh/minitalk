# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/08 14:00:27 by evmorvan          #+#    #+#              #
#    Updated: 2023/04/08 14:17:27 by evmorvan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minitalk
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra

# Server stuff
SERVER_NAME	=	server
SERVER_SRCS	=	$(addprefix sources/server/, \
					server.c \
				)
SERVER_OBJS	=	${SERVER_SRCS:.c=.o}

# Client stuff
CLIENT_NAME	=	client
CLIENT_SRCS	=	$(addprefix sources/client/, \
					client.c \
				)
CLIENT_OBJS	=	${CLIENT_SRCS:.c=.o}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:	${CLIENT_NAME} ${SERVER_NAME}

${CLIENT_NAME}:	${CLIENT_OBJS}
	${CC} ${CLIENT_OBJS} -o ${CLIENT_NAME}

${SERVER_NAME}:	${SERVER_OBJS}
	${CC} ${SERVER_OBJS} -o ${SERVER_NAME}

clean:
	rm -f ${SERVER_OBJS} ${CLIENT_OBJS}

fclean:	clean
	rm -f ${SERVER_NAME} ${CLIENT_NAME}

re:	fclean all

.PHONY: all clean fclean re