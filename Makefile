NAME = pipex

CC = cc

CCFLAGS = -Wall -Wextra -Werror

SRCS = ft_pipex.c ft_utils.c

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): Makefile ft_pipex.h $(LIBFT)
	$(CC) $(CCFLAGS) $(SRCS) $(LIBFT) -o pipex

$(LIBFT):
	make -C libft

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

.PHONY: all clean fclean re