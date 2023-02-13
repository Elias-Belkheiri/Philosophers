NAME				= 	philo

SRCS				=	philo.c ft_atoi.c tools.c routine.c parse.c

CC					= 	cc

CFLAGS				=	-Wall -Wextra -Werror
# CFLAGS				=	-Wall -Wextra -Werror -fsanitize=thread

all					:  ${NAME}


${NAME}				:  ${SRCS}
						${CC} ${CFLAGS} ${SRCS} -o ${NAME}

clean				:
						rm -f ${NAME}

fclean				:  clean

re 					: 	fclean all 