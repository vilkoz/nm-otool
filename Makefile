NAME = ft_nm
OTOOL_NAME = ft_otool

CC = gcc

MAKE = make

COMP_FLAGS = -Wall -Wextra -Werror -g -I libft -I include
LINK_FLAGS = -L libft -lft

all: $(NAME) $(OTOOL_NAME)

LFT_DIR = libft
LIBFT = $(LFT_DIR)/libft.a

$(LIBFT):
	$(MAKE) -j8 -C $(LFT_DIR)

SRC = nm.c				\
	  arch/mach_o_64.c	\
	  arch/mach_o_32.c	\
	  arch/archive.c	\
	  arch/common.c		\
	  arch/fat_binary.c	\
	  sections.c		\
	  symbol_entry.c	\
	  safe_ptr.c		\
	  endian.c			\
	  otool.c			\
	  otool_32.c		\

BIN_DIR = bin

BINS = $(addprefix $(BIN_DIR)/, $(SRC:.c=.o))

$(BIN_DIR)/%.o: %.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(COMP_FLAGS) -c $< -o $@

$(NAME): $(BINS) $(LIBFT)
	$(CC) -o $(NAME) $(LINK_FLAGS) $(BINS)

$(OTOOL_NAME): $(NAME)
	/bin/cp $(NAME) $(OTOOL_NAME)

clean:
	/bin/rm -f $(BINS)
	$(MAKE) -C $(LFT_DIR) clean

fclean: clean
	/bin/rm -f $(NAME) $(OTOOL_NAME)
	$(MAKE) -C $(LFT_DIR) fclean

re: fclean all

.PHONY: clean fclean re
