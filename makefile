NAME = philosophers

INCLUDE = ./include/

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE)

SRCS = src/init.c \
			src/libft.c \
			src/monitoring.c \
			src/utils.c \
			src/main.c \
			src/routine.c \
			src/thread.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re