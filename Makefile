# **************************************************************************** #
#                                 MINISHELL MAKEFILE (Norma 42)                #
# **************************************************************************** #

# --- Nomes e Caminhos ---
NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
LDFLAGS		= -lreadline

# --- Diretórios ---
LIBFT_DIR	= libft
SRC_DIR		= srcs
OBJ_DIR		= obj
INC_DIR		= includes

# --- Bibliotecas ---
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft

# --- Flags de Compilação/Inclusão ---
INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR)/include

# --- Core ---
CORE_SRCS	= $(SRC_DIR)/core/main.c \
			$(SRC_DIR)/core/init.c \
			$(SRC_DIR)/core/signals.c \
			$(SRC_DIR)/core/shell_utils.c

# --- Lexer ---
LEXER_SRCS	= $(SRC_DIR)/lexer/lexer.c \
			$(SRC_DIR)/lexer/lexer_utils.c \
			$(SRC_DIR)/lexer/lexer_quotes.c \
			$(SRC_DIR)/lexer/lexer_operators.c

# --- Expander ---
EXP_SRCS	= $(SRC_DIR)/expander/expander.c \
			$(SRC_DIR)/expander/expander_var.c \
			$(SRC_DIR)/expander/expander_utils.c \
			$(SRC_DIR)/expander/expander_glob.c

# --- Parser ---
PARSE_SRCS	= $(SRC_DIR)/parser/parser.c \
			$(SRC_DIR)/parser/parser_utils.c \
			$(SRC_DIR)/parser/parse_and_or.c \
			$(SRC_DIR)/parser/parse_pipeline.c \
			$(SRC_DIR)/parser/parse_subshell.c \
			$(SRC_DIR)/parser/parse_command.c

# --- Executor ---
EXEC_SRCS	= $(SRC_DIR)/executor/executor.c \
			$(SRC_DIR)/executor/executor_utils.c \
			$(SRC_DIR)/executor/exec_simple_cmd.c \
			$(SRC_DIR)/executor/exec_simple_cmd_utils.c \
			$(SRC_DIR)/executor/exec_pipeline.c \
			$(SRC_DIR)/executor/exec_and_or.c \
			$(SRC_DIR)/executor/exec_subshell.c \
			$(SRC_DIR)/executor/exec_heredoc.c \
			$(SRC_DIR)/executor/exec_builtin.c \
			$(SRC_DIR)/executor/pipe/pipe.c \
			$(SRC_DIR)/executor/pipe/pipe_utils.c \
			$(SRC_DIR)/executor/redirections/redirections.c \
			$(SRC_DIR)/executor/redirections/redirections_utils.c \
			$(SRC_DIR)/executor/builtin/builtin_cd.c \
			$(SRC_DIR)/executor/builtin/builtin_echo.c \
			$(SRC_DIR)/executor/builtin/builtin_env.c \
			$(SRC_DIR)/executor/builtin/builtin_exit.c \
			$(SRC_DIR)/executor/builtin/builtin_pwd.c \
			$(SRC_DIR)/executor/builtin/builtin_export.c \
			$(SRC_DIR)/executor/builtin/builtin_unset.c \
			$(SRC_DIR)/executor/builtin/builtin_utils.c

# --- Utils ---
UTIL_SRCS	= $(SRC_DIR)/utils/env_utils.c

# --- Lista geral ---
SRCS		= $(CORE_SRCS) $(LEXER_SRCS) $(EXP_SRCS) $(PARSE_SRCS) $(EXEC_SRCS) $(UTIL_SRCS)
OBJS		= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# --- Cores ---
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
RESET		= \033[0m

# --- Regras principais ---
.PHONY: all bonus clean fclean re valgrind

all: $(NAME)

bonus: $(NAME)
	@echo "$(GREEN)✓ Bonus version compiled (same binary)$(RESET)"

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(YELLOW)Linkando $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBFT_FLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compilado com sucesso!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compilando: $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)✓ libft compiled$(RESET)"

clean:
	@echo "$(RED)Removendo objetos...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)✓ Objetos removidos$(RESET)"

fclean: clean
	@echo "$(RED)Removendo $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(GREEN)✓ Limpeza completa$(RESET)"

re: fclean all

#valgrind: $(NAME)
#	valgrind --leak-check=full --show-leak-kinds=all \
#	--track-origins=yes --suppressions=readline.supp ./$(NAME)

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all \
	--track-origins=yes ./$(NAME)
