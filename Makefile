SRCS	= main.c \
		

OBJS	= ${SRCS:.c=.o}

NAME	= minishell

CC	= gcc

RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror

LIBFT = libft/libft.a

PATHLIB = libft/

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${LIBFT} ${OBJS}
				${CC} ${CFLAGS} ${LIBFT} ${OBJS} -o ${NAME}

${LIBFT}:
			@make -C ${PATHLIB}

all:		${NAME}

clean:
				@make clean -C ${PATHLIB}
				${RM} ${OBJS} ${OBJB}

fclean: 	clean
				@make fclean -C ${PATHLIB}
				${RM} ${NAME}

re: 		fclean all

.PHONY:		all clean fclean re