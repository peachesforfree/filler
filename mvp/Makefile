NAME = sbalcort.filler

CC = gcc

FLAGS = -Wall -Werror -Wextra

LIBS = libft/libft.a

SRCS =	main.c \
		get_bounds.c \
		place_check.c \
		reading.c \
		algorithm_start.c \
		algorithm_etc.c \
		heat_map.c

OBJS = $(SRCS:.c=.o)

INC = filler.h

all: $(NAME)

$(NAME): $(LIBS)
	$(CC) $(FLAGS) $(SRCS) -I$(INC) $(LIBS) -o $(NAME)

$(LIBS):
	make -C libft

clean:
	/bin/rm -f rm $(NAME)
	make -C libft/ clean

fclean: clean
	/bin/rm -f rm $(NAME)
	make -C libft/ fclean

re: fclean all
