NAME = philo_one
SRCS = init.c lib.c philo_one.c simulation.c utils.c
OBJS = $(SRCS:.c=.o)
HDRS = philo_one.h
FLAG = -Wall -Werror -Wextra -pthread -I .

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAG) -o $(NAME) $(OBJS)

%.o : %.c $(HDRS)
	gcc $(FLAG) -o $@ -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean $(NAME)
