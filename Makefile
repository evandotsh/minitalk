# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/08 14:00:27 by evmorvan          #+#    #+#              #
#    Updated: 2023/04/24 19:29:56 by evmorvan         ###   ########.fr        #
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
						client.c \
					)
CLIENT_OBJS		=	${CLIENT_SRCS:.c=.o}
CLIENT_B_SRCS	=	$(addprefix sources/client/, \
						client_bonus.c \
					)
CLIENT_B_OBJS	=	${CLIENT_B_SRCS:.c=.o}

LIBFT_BIN		= ./libft/libft.a

ifdef MAKEBONUS
	CLIENT_OBJS = ${CLIENT_B_OBJS}
	SERVER_OBJS = ${SERVER_B_OBJS}
endif

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:	${CLIENT_NAME} ${SERVER_NAME}

${CLIENT_NAME}:	${CLIENT_OBJS} ${LIBFT_BIN}
		${CC} ${CLIENT_OBJS} -o ${CLIENT_NAME} ${LIBFT_BIN}

${SERVER_NAME}: ${SERVER_OBJS} ${LIBFT_BIN}
		${CC} ${SERVER_OBJS} -o ${SERVER_NAME} ${LIBFT_BIN}

bonus: ${CLIENT_B_OBJS} ${SERVER_B_OBJS} ${LIBFT_BIN}
		@make MAKEBONUS=1 all

${LIBFT_BIN}:
		@${MAKE} -C ./libft

clean:
		@${MAKE} -C ./libft clean
		rm -f ${SERVER_OBJS} ${CLIENT_OBJS} ${SERVER_B_OBJS} ${CLIENT_B_OBJS}

fclean:	clean
		@${MAKE} -C ./libft fclean
		rm -f ${SERVER_NAME} ${CLIENT_NAME}

re:		fclean all

.PHONY: all clean fclean re