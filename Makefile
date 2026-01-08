NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
CFLAGS += -I./include

# Source files
SRCS = main.c \
       utils/utils.c \
	   routine/utils.c \
       routine/routine.c

# Object files
OBJS = $(SRCS:.c=.o)

# Targets
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
