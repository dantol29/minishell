NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft
SANITAZER =  -fsanitize=address
SOURCES = src/main.c src/save_env.c src/echo.c src/utils.c \
		src/env.c src/launch_commands.c src/pipe.c src/heredoc.c \
		src/cd_pwd_exit.c src/export_unset.c src/free.c src/redirections.c \
		src/execve.c src/path.c src/error.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME) : $(OBJECTS)
		@make -C $(LIBFT)
		$(CC) $(CFLAGS) $(OBJECTS) -L./$(LIBFT) -lft -lreadline $(SANITAZER) -o $(NAME)

clean:
	rm -rf $(OBJECTS)
	rm -rf $(LIBFT)/*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)/libft.a

norm :
	@norminette ./includes/minishell.h $(SOURCES)

re: fclean all

.PHONY: all clean fclean re