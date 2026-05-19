NAME    = infinite
CC      = gcc
CFLAGS  = -Wall -Wextra -g -std=c99 $(shell pkg-config --cflags sdl2)
LIBS    = $(shell pkg-config --libs sdl2) -lm

SRCS    = main.c \
          view.c \
          mandelbrot.c \
          julia.c \
          colour.c \
          render.c

OBJS    = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
