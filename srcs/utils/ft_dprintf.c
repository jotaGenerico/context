#include "minishell.h"

static int	ft_vfprintf(int fd, const char *format, va_list args)
{
	(void)format;
	(void)args;
	ft_putendl_fd("Erro: ft_dprintf não implementado. Por favor, adicione a lógica ft_printf aqui.", fd);
	return (0);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		len;

	va_start(args, format);
	len = ft_vfprintf(fd, format, args);
	va_end(args);
	return (len);
}
