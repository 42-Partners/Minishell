NAME        := libft.a
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g

# Directories
SRC_DIRS     := src
OBJ_DIR      := build
INCLUDE_DIRS := includes
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

$(NAME): $(OBJ)
	@echo "$(YELLOW)🔧 Linking objects...$(RESET)"
	@ar -crs $(NAME) $(OBJ)
	@echo "$(GREEN)✅ $(NAME) built successfully$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rules
all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)🧴 Object files removed.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)🧼 Everything cleaned$(RESET)"

re: fclean all

norminette:
	@echo "$(YELLOW)🧠 Running norminette...$(RESET)"
	@norminette $(SRC) -R CheckForbiddenSourceHeader || true

.PHONY: all clean fclean re norminette