# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/08 14:00:27 by evmorvan          #+#    #+#              #
#    Updated: 2023/04/29 15:53:08 by evmorvan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minitalk
CC				=	cc
CFLAGS			=	-Wall -Werror -Wextra

# Server stuff
SERVER_NAME		=	server
SERVER_SRCS		=	$(addprefix sources/server/, \
						server.c \
					)
SERVER_OBJS		=	${SERVER_SRCS:.c=.o}

# Client stuff
CLIENT_NAME		=	client
CLIENT_SRCS		=	$(addprefix sources/client/, \
						client.c \
					)
CLIENT_OBJS		=	${CLIENT_SRCS:.c=.o}

LIBFT_BIN		= ./libft/libft.a

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:	${CLIENT_NAME} ${SERVER_NAME}

${CLIENT_NAME}:	${CLIENT_OBJS} ${LIBFT_BIN}
		${CC} ${CLIENT_OBJS} -o ${CLIENT_NAME} ${LIBFT_BIN}

${SERVER_NAME}: ${SERVER_OBJS} ${LIBFT_BIN}
		${CC} ${SERVER_OBJS} -o ${SERVER_NAME} ${LIBFT_BIN}

${LIBFT_BIN}:
		@${MAKE} -C ./libft

clean:
		@${MAKE} -C ./libft clean
		rm -f ${SERVER_OBJS} ${CLIENT_OBJS}

fclean:	clean
		@${MAKE} -C ./libft fclean
		rm -f ${SERVER_NAME} ${CLIENT_NAME}

re:		fclean all

.PHONY: all clean fclean re