╭───────────────────────────────────────────╮
│           📘 MAKEFILE CHEAT SHEET         │
│             Versão 42 Certified™          │
╰───────────────────────────────────────────╯

📌 VARIÁVEIS
─────────────────────────────────────────────
VAR = valor         # Declara
$(VAR)              # Usa

🧠 EXEMPLO:
NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

📌 SÍMBOLOS MÁGICOS (dentro de regras!)
─────────────────────────────────────────────
$@   → alvo (target)             → nome da regra atual
$<   → primeira dependência      → bom p/ compilar .c
$^   → todas as dependências     → bom p/ linkar tudo

🧠 EXEMPLO:
$(NAME): $(OBJS)
	ar rcs $@ $^

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

📌 REGRAS ESPECIAIS
─────────────────────────────────────────────
all:        → build normal
bonus:      → build com bônus




# Nome da biblioteca final
NAME = libft.a

# Compilador padrão (cc = clang na 42)
CC = cc

# Flags obrigatórias da 42: avisam sobre problemas sem gritar em runtime
CFLAGS = -Wall -Wextra -Werror

# Lista de arquivos fonte obrigatórios
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

# Lista de arquivos fonte bônus (funções da parte bônus)
BONUS_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

# Lista de objetos obrigatórios (transforma .c em .o)
OBJS = $(SRCS:.c=.o)

# Lista de objetos bônus
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

# Flag de controle: marca se o bônus foi pedido
BONUS_FLAG = no

# Regra padrão: compila apenas as funções obrigatórias
all: $(NAME)

# Regra que gera o arquivo .a com os objetos obrigatórios
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Regra para compilar a versão com bônus (ativa a flag e inclui os bônus)
bonus: BONUS_FLAG = yes
bonus: $(OBJS) $(BONUS_OBJS)
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

# Como compilar cada .c em .o — depende do libft.h (importante!)
%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

# Remove os arquivos .o (limpa a sujeira da compilação)
clean:
	rm -f $(OBJS) $(BONUS_OBJS)

# Limpa tudo: objetos + biblioteca final
fclean: clean
	rm -f $(NAME)

# Recompila do zero (limpa e recompila tudo)
re: fclean all

# Define os nomes das regras "falsas" (não são arquivos)
.PHONY: all bonus clean fclean re
