NAME		:= minishell
CC		:= cc
CFLAGS		:= -Wall -Wextra -Werror -g

# Valgrind
VALGRIND	:= valgrind

VALGRIND_FLAGS	:= --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --suppressions=valgrind.supp

VALGRIND_STACK	:= $(VALGRIND_FLAGS) \
		--read-var-info=yes --vgdb=yes --trace-children=yes \
		--track-fds=yes

# Library
LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a
LIB_FLAGS	:= -L$(LIBFT_DIR) -lft -lreadline

# Directories
OBJ_DIR		:= build
INCLUDE_DIRS	:= includes $(LIBFT_DIR)/includes
INCLUDES	:= $(foreach dir,$(INCLUDE_DIRS),-I$(dir))

# Colors
GREEN 		:= \033[0;32m
YELLOW		:= \033[0;33m
RED		:= \033[0;31m
BLUE		:= \033[0;34m
RESET		:= \033[0m

# Files
SRC		:= \
			src/minishell.c \
			src/lexer/tokenize.c \
			src/lexer/token_checkers.c \
			src/lexer/token_parse.c \
			src/lexer/token_stack.c \
			src/parser/ast_builder.c \
			src/parser/ast_free.c \
			src/parser/ast_level_handler.c \
			src/parser/ast_redirects.c \
			src/parser/ast_token_parser.c \
			src/parser/ast_validate.c \
			src/signals/signals.c \
			src/debug.c
OBJ		:= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(YELLOW)🔧 Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIB_FLAGS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) built successfully$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(YELLOW)📚 Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --silent

# Rules
all: $(NAME)

valgrind: $(NAME)
	@echo "$(YELLOW)🔎 Running Valgrind...$(RESET)"
	@$(VALGRIND) $(VALGRIND_FLAGS) ./$(NAME)

valgrind-stack: $(NAME)
	@echo "$(YELLOW)🧠 Running Valgrind (Stacktrace Mode)...$(RESET)"
	@$(VALGRIND) $(VALGRIND_STACK) ./$(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR) --silent
	@echo "$(RED)🧴 Object files removed.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR) --silent
	@echo "$(RED)🧼 Everything cleaned$(RESET)"

re: fclean all

norminette:
	@echo "$(YELLOW)🧠 Running norminette...$(RESET)"
	@norminette $(SRC) -R CheckForbiddenSourceHeader || true

.PHONY: all clean fclean re norminette valgrind valgrind-stack
