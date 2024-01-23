NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft

SOURCES = src/main.c src/save_env.c src/echo.c src/utils.c src/env.c src/launch_commands.c src/pipe.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME) : $(OBJECTS)
		@make -C $(LIBFT)
		$(CC) $(CFLAGS) $(OBJECTS) -L./$(LIBFT) -lft -lreadline -o $(NAME)

clean:
	rm -rf $(OBJECTS)
	rm -rf $(LIBFT)/*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)/libft.a

mini: re
	./minishell

norm :
	@norminette ./includes/minishell.h $(SOURCES)

re: fclean all

.PHONY: all clean fclean re