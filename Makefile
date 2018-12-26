NAME= nm

CC = gcc

COMP_FLAGS = -Wall -Wextra -Werror
LINK_FLAGS = 

all: $(NAME)

SRC = nm.c

BINS = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(COMP_FLAGS) -c $<

$(NAME): $(BINS)
	$(CC) -o $(NAME) $(LINK_FLAGS) $(BINS)

clean:
	/bin/rm -f $(BINS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
