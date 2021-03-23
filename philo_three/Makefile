NAME = philo_three
SRCS = init.c lib.c philo_three.c simulation.c utils.c monitor.c
OBJS = $(SRCS:.c=.o)
HDRS = philo_three.h
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
