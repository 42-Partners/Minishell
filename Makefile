NAME        := minishell
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g

# Library
LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a
LIBFT_FLAGS := -L$(LIBFT_DIR) -lft

# Directories
SRC_DIRS     := src
OBJ_DIR      := build
INCLUDE_DIRS := includes $(LIBFT_DIR)
INCLUDES     := $(foreach dir,$(INCLUDE_DIRS),-I$(dir))

# Colors
GREEN  := \033[0;32m
YELLOW := \033[0;33m
RED    := \033[0;31m
BLUE   := \033[0;34m
RESET  := \033[0m

# Files
SRC := $(shell find $(SRC_DIRS) -name "*.c")
OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(YELLOW)🔧 Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) built successfully$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(YELLOW)📚 Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --silent

# Rules
all: $(NAME)

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

.PHONY: all clean fclean re norminette