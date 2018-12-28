NAME= nm

CC = gcc

COMP_FLAGS = -Wall -Wextra -Werror -g -I libft
LINK_FLAGS = -L libft -lft

all: $(NAME)

LFT_DIR = libft
LIBFT = $(LFT_DIR)/libft.a

$(LIBFT):
	make -j8 -C $(LFT_DIR)

SRC = nm.c				\
	  elf_64.c			\
	  sections.c		\

BINS = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(COMP_FLAGS) -c $<

$(NAME): $(BINS) $(LIBFT)
	$(CC) -o $(NAME) $(LINK_FLAGS) $(BINS)

clean:
	/bin/rm -f $(BINS)
	make -C $(LFT_DIR) clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C $(LFT_DIR) fclean

re: fclean all

.PHONY: clean fclean re
