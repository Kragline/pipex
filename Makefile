NAME = pipex

CC = cc

CCFLAGS = -Wall -Wextra -Werror

MANDATORY = mandatory/
BONUS = bonus/
FILENAMES = pipex utils

PREFIX_FILENAMES = $(addprefix $(MANDATORY)ft_, $(FILENAMES))
SRCS = $(addsuffix .c, $(PREFIX_FILENAMES))

PREFIX_BONUS = $(addprefix $(BONUS)ft_, $(FILENAMES))
BONUS_SRCS = $(addsuffix .c, $(PREFIX_BONUS))

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(MANDATORY)ft_pipex.h $(LIBFT) $(SRCS)
	$(CC) $(CCFLAGS) -I$(MANDATORY) $(SRCS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

bonus: $(BONUS)ft_pipex.h $(LIBFT) $(BONUS_SRCS)
	$(CC) $(CCFLAGS) -I$(BONUS) $(BONUS_SRCS) $(LIBFT) -o $(NAME)

clean:
	make -C libft clean

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus