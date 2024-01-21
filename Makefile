NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = src/main.c src/save_env.c src/echo.c src/utils.c src/print_env.c src/launch_commands.c src/pipe.c
LIBFT = libft
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
		@make -C $(LIBFT)
		$(CC) $(CFLAGS) $(OBJS) -L./$(LIBFT) -lft -lreadline -o $(NAME)

clean:
	rm -rf $(OBJS)
	rm -rf $(LIBFT)/*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)/libft.a

re: fclean all

.PHONY: all clean fclean re