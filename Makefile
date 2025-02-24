NAME = pipex

CC = cc

CCFLAGS = -Wall -Wextra -Werror

SRCS = ft_pipex.c ft_utils.c

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): Makefile ft_pipex.h $(LIBFT) $(SRCS)
	$(CC) $(CCFLAGS) $(SRCS) $(LIBFT) -o pipex

$(LIBFT):
	make -C libft

clean:
	make -C libft clean

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re