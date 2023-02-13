NAME		    	=	philo_bonus

SRCS				=	philo_bonus.c ft_atoi.c tools.c parse.c routine.c

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