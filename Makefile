NAME = pipex

CC = cc

CCFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

MANDATORY = mandatory/
BONUS = bonus/
FILENAMES = pipex utils get_path
BONUS_FILENAMES = pipex utils get_path execute

SRCS = $(addsuffix .c, $(addprefix $(MANDATORY)ft_, $(FILENAMES)))
BONUS_SRCS = $(addsuffix .c, $(addprefix $(BONUS)ft_, $(BONUS_FILENAMES)))

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(MANDATORY)ft_pipex.h $(LIBFT) $(SRCS)
	@$(CC) $(CCFLAGS) -I$(MANDATORY) $(SRCS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -sC libft

bonus: $(BONUS)ft_pipex.h $(LIBFT) $(BONUS_SRCS)
	@$(CC) $(CCFLAGS) -I$(BONUS) $(BONUS_SRCS) $(LIBFT) -o $(NAME)

clean:
	@make -sC libft clean

fclean: clean
	@make -sC libft fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus