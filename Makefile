# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/08 14:00:27 by evmorvan          #+#    #+#              #
#    Updated: 2023/04/14 18:56:14 by evmorvan         ###   ########.fr        #
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
SERVER_B_SRCS	=	$(addprefix sources/server/, \
						server_bonus.c \
					)
SERVER_B_OBJS	=	${SERVER_B_SRCS:.c=.o}
# Client stuff
CLIENT_NAME		=	client
CLIENT_SRCS		=	$(addprefix sources/client/, \
						client.c utils.c \
					)
CLIENT_OBJS		=	${CLIENT_SRCS:.c=.o}
CLIENT_B_SRCS	=	$(addprefix sources/client/, \
						client_bonus.c utils_bonus.c \
					)
CLIENT_B_OBJS	=	${CLIENT_B_SRCS:.c=.o}

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:	${CLIENT_NAME} ${SERVER_NAME}

libft.a:
		${MAKE} -C ./libft

${CLIENT_NAME}:	libft.a ${CLIENT_OBJS}
		${CC} ${CLIENT_OBJS} ./libft/libft.a -o ${CLIENT_NAME}

${SERVER_NAME}:	libft.a ${SERVER_OBJS}
		${CC} ${SERVER_OBJS} ./libft/libft.a -o ${SERVER_NAME}

bonus:	libft.a ${CLIENT_B_OBJS} ${SERVER_B_OBJS}
		${CC} ${CLIENT_B_OBJS} ./libft/libft.a -o ${CLIENT_NAME}
		${CC} ${SERVER_B_OBJS} ./libft/libft.a -o ${SERVER_NAME}

clean:
		${MAKE} -C ./libft clean
		rm -f ${SERVER_OBJS} ${CLIENT_OBJS} ${SERVER_B_OBJS} ${CLIENT_B_OBJS}

fclean:	clean
		${MAKE} -C ./libft fclean
		rm -f ${SERVER_NAME} ${CLIENT_NAME}

re:		fclean all

.PHONY: all clean fclean re