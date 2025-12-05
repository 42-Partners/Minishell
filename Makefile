CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

all:
	@$(CC) $(CFLAGS) -o $(NAME) ./src/main.c