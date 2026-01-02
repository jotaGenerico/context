#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

/**
 * Pula todos os caracteres de espaço em branco (espaço, tab, nova linha)
 * lidos do fluxo de entrada (stdin).
 */
int match_space(FILE *f)
{
	int	c;

	// Lê caracteres enquanto não for o fim do arquivo (EOF)
	while ((c = fgetc(f)) != EOF)
	{
		// Se encontrar algo que NÃO é espaço, interrompe
		if (!isspace(c))
		{
			// Devolve o caractere lido para o buffer do arquivo
			// para que a próxima função de leitura possa usá-lo
			ungetc(c, f);
			break ;
		}
	}
	return (0);
}

/**
 * Tenta ler um caractere específico 'c' do arquivo.
 * Usado para lidar com caracteres fixos na string de formato.
 */
int match_char(FILE *f, char c)
{
	int	ch = fgetc(f);

	// Se o caractere lido for exatamente o esperado, sucesso
	if (ch == c)
		return (1);
	// Se for diferente e não for EOF, devolve o caractere ao buffer
	if (ch != EOF)
		ungetc(ch, f);
	return (0);
}

/**
 * Conversão %c: Lê exatamente um caractere, sem pular espaços.
 */
int scan_char(FILE *f, va_list ap)
{
	int	ch = fgetc(f);
	char *dst;

	if (ch == EOF)
		return (0);

	// Extrai o próximo argumento da lista como um ponteiro char*
	dst = va_arg(ap, char *);
	// Atribui o caractere lido ao endereço de destino
	*dst = (char)ch;
	return (1);
}

/**
 * Conversão %d: Lê um número inteiro decimal.
 */
int scan_int(FILE *f, va_list ap)
{
	int	c = fgetc(f);
	int	value = 0;
	int	sign = 1;

	// Gerencia sinal positivo ou negativo opcional
	if (c == '-' || c == '+')
	{
		if (c == '-')
			sign = -1;
		c = fgetc(f);
	}

	// Acumula dígitos transformando caracteres em valor numérico
	while (isdigit(c))
	{
		value = value * 10 + (c - '0');
		c = fgetc(f);
	}

	// Devolve o caractere que interrompeu o loop (se não for EOF)
	if (c != EOF)
		ungetc(c, f);

	// Extrai o argumento como ponteiro de inteiro (int*) e atribui o valor
	int	*dst = va_arg(ap, int *);
	*dst = value * sign;
	return (1);
}

/**
 * Conversão %s: Lê uma sequência de caracteres até encontrar um espaço.
 */
int scan_string(FILE *f, va_list ap)
{
	// Pega o ponteiro para o array de caracteres (char*)
	char *dst = va_arg(ap, char *);
	int	c = fgetc(f);
	int	i = 0;

	if (c == EOF)
		return (0);

	// Armazena o primeiro caractere lido
	dst[i++] = (char)c;

	// Continua lendo até encontrar um espaço branco ou fim do arquivo
	while ((c = fgetc(f)) != EOF && !isspace(c))
		dst[i++] = (char)c;

	// Devolve o caractere de espaço lido para o buffer
	if (c != EOF)
		ungetc(c, f);

	// Adiciona obrigatoriamente o terminador nulo da string
	dst[i] = '\0';
	return (1);
}

/**
 * Direciona para a função de conversão correta baseada no caractere após o '%'
 */
int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			// Scanf pula espaços automaticamente antes de %d e %s
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

/**
 * Lógica principal de processamento do formato (fornecida no template do exame)
 */
int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	// Verifica se o arquivo já começou em EOF
	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		// Se encontrar um especificador de conversão
		if (*format == '%')
		{
			format++;
			// Executa a conversão e incrementa o contador de sucessos
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		// Se encontrar um espaço no formato, pula espaços no stdin
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		// Se encontrar um caractere fixo no formato, tenta casá-lo com o stdin
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}

	if (ferror(f))
		return EOF;
	return nconv;
}

/**
 * Função principal que o usuário chama. Gerencia a lista de argumentos variáveis.
 */
int ft_scanf(const char *format, ...)
{
	int	ret;
	va_list ap;

	// Inicializa 'ap' para apontar para o primeiro argumento após 'format'
	va_start(ap, format);
	// Delega a leitura para a função que trabalha com va_list
	ret = ft_vfscanf(stdin, format, ap);
	// Finaliza o uso da lista (obrigatório)
	va_end(ap);
	return (ret);
}
