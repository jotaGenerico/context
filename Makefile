# --- EXECUTABLES ---
NAME		= push_swap
BONUS_NAME	= checker

# --- COMPILER & FLAGS ---
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I include/ -I libft/include/
RM			= rm -f

# --- DIRECTORIES ---
OBJ_DIR		= obj
SRC_DIR		= src
LIBFT_DIR	= libft

# --- SOURCE FILES (No Wildcards) ---
# Project sources
SRCS_FILES	= ft_alg_analysis.c \
		ft_alg_cost.c \
		ft_alg_movement.c \
		ft_alg_target.c \
		ft_parse.c \
		ft_parsing.c \
		ft_push_swap.c \
		ft_stack_operations.c \
		ft_stack_rot_ab.c \
		ft_stack_rot_r.c \
		ft_stack_utils1.c \
		ft_stack_utils2.c

# Libft sources
LIBFT_FILES	=	ft_calloc.c \
				ft_ato_bin.c ft_atof.c ft_atohex.c ft_atohex_ptr.c ft_atoi_base.c \
				ft_atoi.c ft_atol.c ft_ato_octa.c ft_base_is_valid.c ft_bin_toa.c \
				ft_ftoa.c ft_hextoa.c ft_itoa.c ft_octa_toa.c ft_ptr_hextoa.c \
				ft_utoa_base.c \
				ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
				ft_isspace.c ft_tolower.c ft_toupper.c \
				ft_dlstadd_back.c ft_dlstadd_front.c ft_dlstclear.c ft_dlstdelone.c \
				ft_dlstiter.c ft_dlstlast.c ft_dlstmap.c ft_dlstnew.c ft_dlstsize.c \
				get_next_line.c get_next_line_utils.c \
				ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
				ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c \
				ft_bzero.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
				ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
				ft_buffer.c ft_dispatch_specifier.c ft_flags.c ft_format_output.c \
				ft_format_utils.c ft_handle_char.c ft_handle_decimal.c ft_handle_float.c \
				ft_handle_hex.c ft_handle_integer.c ft_handle_octal.c ft_handle_percent.c \
				ft_handle_pointer.c ft_handle_string.c ft_handle_unsigned.c ft_parser.c \
				ft_precision_num.c ft_precision_str.c ft_printf.c \
				ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
				ft_strncmp.c ft_strnstr.c ft_strrchr.c \
				ft_count_digits.c ft_split.c ft_striteri.c ft_strjoin.c ft_strmapi.c \
				ft_strtrim.c ft_substr.c

# Main files
MAIN_SRC	= main.c
BONUS_SRC	= checker_bonus.c

# --- VPATH (Search Paths for Sources) ---
VPATH		= $(SRC_DIR) \
			  $(LIBFT_DIR)/src/alloc $(LIBFT_DIR)/src/conversion $(LIBFT_DIR)/src/ctype \
			  $(LIBFT_DIR)/src/dlist $(LIBFT_DIR)/src/gnl $(LIBFT_DIR)/src/list \
			  $(LIBFT_DIR)/src/memory $(LIBFT_DIR)/src/output $(LIBFT_DIR)/src/printf \
			  $(LIBFT_DIR)/src/string $(LIBFT_DIR)/src/utils

# --- OBJECT FILES ---
# Create object file lists by adding the object directory prefix and changing .c to .o
SRCS_OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS_FILES:.c=.o))
LIBFT_OBJS		= $(addprefix $(OBJ_DIR)/, $(LIBFT_FILES:.c=.o))
MAIN_OBJ		= $(addprefix $(OBJ_DIR)/, $(MAIN_SRC:.c=.o))
BONUS_OBJ		= $(addprefix $(OBJ_DIR)/, $(BONUS_SRC:.c=.o))

# Common objects for both executables
COMMON_OBJS		= $(SRCS_OBJS) $(LIBFT_OBJS)

# --- RULES ---
.PHONY: all bonus clean fclean re

all: $(NAME)

# Rule to link the main program
$(NAME): $(MAIN_OBJ) $(COMMON_OBJS)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) -o $(NAME) $(MAIN_OBJ) $(COMMON_OBJS)
	@echo "$(NAME) is ready! ✅"

# Rule to build the bonus program
bonus: $(BONUS_NAME)

# Rule to link the bonus program
$(BONUS_NAME): $(BONUS_OBJ) $(COMMON_OBJS)
	@echo "Linking $(BONUS_NAME)..."
	@$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJ) $(COMMON_OBJS)
	@echo "$(BONUS_NAME) is ready! ✨"

# Generic rule to compile any .c file into an object file inside OBJ_DIR
# The '| $(OBJ_DIR)' part ensures the directory is created before compiling
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# Rule to create the object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "Cleaning object files..."
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@echo "Cleaning executables..."
	@$(RM) $(NAME) $(BONUS_NAME)

re: fclean all
