NAME        := libft.a
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g

# Directories
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
SRC :=	src/basic/ft_isalnum.c \
	src/basic/ft_isalpha.c \
	src/basic/ft_isascii.c \
	src/basic/ft_isdigit.c \
	src/basic/ft_isprint.c \
	src/basic/ft_isspace.c \
	src/basic/ft_strlen.c \
	src/basic/ft_toupper.c \
	src/basic/ft_tolower.c \
	src/basic/ft_isfloat.c \
	src/basic/ft_atoi.c \
	src/basic/ft_atof.c \
	src/basic/ft_atol.c \
	src/basic/ft_strcmp.c \
	src/basic/ft_strncmp.c \
	src/basic/ft_strlcpy.c \
	src/basic/ft_strlcat.c \
	src/basic/ft_strnstr.c \
	src/basic/ft_strchr.c \
	src/basic/ft_strrchr.c \
	src/basic/ft_bzero.c \
	src/basic/ft_memset.c \
	src/basic/ft_memcmp.c \
	src/basic/ft_memchr.c \
	src/basic/ft_memmove.c \
	src/basic/ft_memcpy.c \
	src/basic/ft_strdup.c \
	src/basic/ft_calloc.c \
	src/basic/ft_putchar_fd.c \
	src/basic/ft_putstr_fd.c \
	src/basic/ft_putendl_fd.c \
	src/basic/ft_putnbr_fd.c \
	src/basic/ft_substr.c \
	src/basic/ft_strjoin.c \
	src/basic/ft_strmapi.c \
	src/basic/ft_striteri.c \
	src/basic/ft_itoa.c \
	src/basic/ft_strtrim.c \
	src/basic/ft_split.c \
	src/basic/ft_lstnew_bonus.c \
	src/basic/ft_lstadd_front_bonus.c \
	src/basic/ft_lstsize_bonus.c \
	src/basic/ft_lstlast_bonus.c \
	src/basic/ft_lstadd_back_bonus.c \
	src/basic/ft_lstdelone_bonus.c \
	src/basic/ft_lstclear_bonus.c \
	src/basic/ft_lstiter_bonus.c \
	src/basic/ft_lstmap_bonus.c \
	src/printf/ft_printf.c \
	src/printf/ft_conversion_specifier.c \
	src/printf/ft_print_char.c \
	src/printf/ft_print_str.c \
	src/printf/ft_print_nbr.c \
	src/printf/ft_print_hexa.c \
	src/printf/ft_print_pointer.c \
	src/gnl/get_next_line.c

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
	norminette $(SRC) includes -R CheckForbiddenSourceHeader || true

.PHONY: all clean fclean re norminette