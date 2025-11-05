# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/04 14:04:37 by jose-cad          #+#    #+#              #
#    Updated: 2025/09/04 14:04:42 by jose-cad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Library name
NAME		= libft.a

# Directories
SRC_DIR		= src
OBJ_DIR		= objects
INC_DIR		= include

# Compiler and flags
CC			= cc
CFLAGS			= -Wall -Wextra -Werror
AR			= ar rcs
RM			= rm -rf

# Include path
INCLUDES	= -I$(INC_DIR) -I$(SRC_DIR)/printf

# Source files by category
ALLOC_SRC	= ft_calloc.c

CONVERSION_SRC	= ft_ato_bin.c \
		ft_atof.c \
		ft_atohex.c \
		ft_atohex_ptr.c \
		ft_atoi_base.c \
		ft_atoi.c \
		ft_atol.c \
		ft_ato_octa.c \
		ft_base_is_valid.c \
		ft_bin_toa.c \
		ft_ftoa.c \
		ft_hextoa.c \
		ft_itoa.c \
		ft_octa_toa.c \
		ft_ptr_hextoa.c \
		ft_utoa_base.c

CTYPE_SRC	= ft_isalnum.c \
		ft_isalnum_or_underscore.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isnumeric.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_tolower.c \
		ft_toupper.c

DLIST_SRC	= ft_dlstnew.c \
		ft_dlstadd_front.c \
		ft_dlstadd_back.c \
		ft_dlstlast.c \
		ft_dlstsize.c \
		ft_dlstdelone.c \
		ft_dlstclear.c \
		ft_dlstiter.c \
		ft_dlstmap.c \
		ft_dlstremove.c

GNL_SRC		= get_next_line.c \
		get_next_line_utils.c

LIST_SRC	= ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstlast.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_lstsize.c

MEMORY_SRC	= ft_bzero.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c

OUTPUT_SRC	= ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c

PRINTF_SRC	= ft_buffer.c \
		ft_dispatch_specifier.c \
		ft_flags.c \
		ft_format_output.c \
		ft_format_utils.c \
		ft_handle_char.c \
		ft_handle_decimal.c \
		ft_handle_float.c \
		ft_handle_hex.c \
		ft_handle_integer.c \
		ft_handle_octal.c \
		ft_handle_percent.c \
		ft_handle_pointer.c \
		ft_handle_string.c \
		ft_handle_unsigned.c \
		ft_parser.c \
		ft_precision_num.c \
		ft_precision_str.c \
		ft_printf.c \
		ft_dprintf.c

STRING_SRC	= ft_strchr.c \
		ft_strdup.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c

UTILS_SRC	= ft_count_digits.c \
		ft_split.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strjoin_free.c \
		ft_strmapi.c \
		ft_strtrim.c \
		ft_substr.c

# Full source paths
ALLOC_SRCS		= $(addprefix $(SRC_DIR)/alloc/, $(ALLOC_SRC))
CONVERSION_SRCS		= $(addprefix $(SRC_DIR)/conversion/, $(CONVERSION_SRC))
CTYPE_SRCS		= $(addprefix $(SRC_DIR)/ctype/, $(CTYPE_SRC))
DLIST_SRCS		= $(addprefix $(SRC_DIR)/dlist/, $(DLIST_SRC))
GNL_SRCS		= $(addprefix $(SRC_DIR)/gnl/, $(GNL_SRC))
LIST_SRCS		= $(addprefix $(SRC_DIR)/list/, $(LIST_SRC))
MEMORY_SRCS		= $(addprefix $(SRC_DIR)/memory/, $(MEMORY_SRC))
OUTPUT_SRCS		= $(addprefix $(SRC_DIR)/output/, $(OUTPUT_SRC))
PRINTF_SRCS		= $(addprefix $(SRC_DIR)/printf/, $(PRINTF_SRC))
STRING_SRCS		= $(addprefix $(SRC_DIR)/string/, $(STRING_SRC))
UTILS_SRCS		= $(addprefix $(SRC_DIR)/utils/, $(UTILS_SRC))

# All sources (without printf - for nopf target)
SRCS_BASE = $(ALLOC_SRCS) $(CONVERSION_SRCS) $(CTYPE_SRCS) $(DLIST_SRCS) \
	$(GNL_SRCS) $(LIST_SRCS) $(MEMORY_SRCS) $(OUTPUT_SRCS) $(STRING_SRCS) \
	$(UTILS_SRCS)

# All sources (with printf - default)
SRCS = $(SRCS_BASE) $(PRINTF_SRCS)

# Object files
ALLOC_OBJS		= $(addprefix $(OBJ_DIR)/alloc/, $(ALLOC_SRC:.c=.o))
CONVERSION_OBJS		= $(addprefix $(OBJ_DIR)/conversion/, $(CONVERSION_SRC:.c=.o))
CTYPE_OBJS		= $(addprefix $(OBJ_DIR)/ctype/, $(CTYPE_SRC:.c=.o))
DLIST_OBJS		= $(addprefix $(OBJ_DIR)/dlist/, $(DLIST_SRC:.c=.o))
GNL_OBJS		= $(addprefix $(OBJ_DIR)/gnl/, $(GNL_SRC:.c=.o))
LIST_OBJS		= $(addprefix $(OBJ_DIR)/list/, $(LIST_SRC:.c=.o))
MEMORY_OBJS		= $(addprefix $(OBJ_DIR)/memory/, $(MEMORY_SRC:.c=.o))
OUTPUT_OBJS		= $(addprefix $(OBJ_DIR)/output/, $(OUTPUT_SRC:.c=.o))
PRINTF_OBJS		= $(addprefix $(OBJ_DIR)/printf/, $(PRINTF_SRC:.c=.o))
STRING_OBJS		= $(addprefix $(OBJ_DIR)/string/, $(STRING_SRC:.c=.o))
UTILS_OBJS		= $(addprefix $(OBJ_DIR)/utils/, $(UTILS_SRC:.c=.o))

# All objects (without printf)
OBJS_BASE = $(ALLOC_OBJS) $(CONVERSION_OBJS) $(CTYPE_OBJS) $(DLIST_OBJS) \
	$(GNL_OBJS) $(LIST_OBJS) $(MEMORY_OBJS) $(OUTPUT_OBJS) $(STRING_OBJS) \
	$(UTILS_OBJS)

# All objects (with printf)
OBJS = $(OBJS_BASE) $(PRINTF_OBJS)

# Colors for output
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
RED	= \033[0;31m
BLUE	= \033[0;34m
NC	= \033[0m

# Default target (with printf)
all: $(NAME)

# Create library with printf (default)
$(NAME): $(OBJS)
	@echo "$(YELLOW)Creating library $(NAME) with printf...$(NC)"
	@$(AR) $(NAME) $(OBJS)
	@echo "$(GREEN)Library $(NAME) created successfully with printf!$(NC)"

# Create library without printf (for restricted projects)
nopf: $(OBJS_BASE)
	@echo "$(YELLOW)Creating library $(NAME) without printf...$(NC)"
	@$(AR) $(NAME) $(OBJS_BASE)
	@echo "$(BLUE)Library $(NAME) created successfully without printf!$(NC)"

# Create object directories
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/alloc
	@mkdir -p $(OBJ_DIR)/conversion
	@mkdir -p $(OBJ_DIR)/ctype
	@mkdir -p $(OBJ_DIR)/dlist
	@mkdir -p $(OBJ_DIR)/gnl
	@mkdir -p $(OBJ_DIR)/list
	@mkdir -p $(OBJ_DIR)/memory
	@mkdir -p $(OBJ_DIR)/output
	@mkdir -p $(OBJ_DIR)/printf
	@mkdir -p $(OBJ_DIR)/string
	@mkdir -p $(OBJ_DIR)/utils

# Compile object files by category
$(OBJ_DIR)/alloc/%.o: $(SRC_DIR)/alloc/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/conversion/%.o: $(SRC_DIR)/conversion/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/ctype/%.o: $(SRC_DIR)/ctype/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/dlist/%.o: $(SRC_DIR)/dlist/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/gnl/%.o: $(SRC_DIR)/gnl/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/list/%.o: $(SRC_DIR)/list/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/memory/%.o: $(SRC_DIR)/memory/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/output/%.o: $(SRC_DIR)/output/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/printf/%.o: $(SRC_DIR)/printf/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/string/%.o: $(SRC_DIR)/string/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/utils/%.o: $(SRC_DIR)/utils/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files and directories
clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@$(RM) $(OBJ_DIR)
	@echo "$(GREEN)Object files cleaned!$(NC)"

# Clean everything
fclean: clean
	@echo "$(RED)Cleaning library...$(NC)"
	@$(RM) $(NAME)
	@echo "$(GREEN)Everything cleaned!$(NC)"

# Rebuild everything
re: fclean all

# Rebuild without printf
renopf: fclean nopf

# Phony targets
.PHONY: all nopf clean fclean re renopf
