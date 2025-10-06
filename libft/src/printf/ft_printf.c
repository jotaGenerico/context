/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:38:31 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:38:36 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_null_char(t_buffer *buffer, t_format *fmt);
static void	ft_print_formatted(t_format *fmt, va_list args, t_buffer *buffer);
static void	ft_handle_literal(const char *format, int *i, t_buffer *buffer);
static void	ft_handle_percent_and_formatted(const char *format, int *i,
				t_print_context *ctx, va_list args);

int	ft_printf(const char *format, ...)
{
	va_list			args;
	t_buffer		buffer;
	t_format		fmt;
	int				i;
	t_print_context	ctx;

	va_start(args, format);
	buffer.index = 0;
	buffer.printed_count = 0;
	i = 0;
	ctx.fmt = &fmt;
	ctx.buffer = &buffer;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
			ft_handle_percent_and_formatted(format, &i, &ctx, args);
		else
			ft_handle_literal(format, &i, &buffer);
	}
	va_end(args);
	ft_flush_buffer(&buffer);
	return (buffer.printed_count);
}

static void	ft_print_null_char(t_buffer *buffer, t_format *fmt)
{
	int	padding;

	padding = fmt->width - 1;
	if (!fmt->flag_minus)
	{
		while (padding-- > 0)
			ft_add_to_buffer(buffer, ' ');
	}
	ft_add_to_buffer(buffer, '\0');
	if (fmt->flag_minus)
	{
		padding = fmt->width - 1;
		while (padding-- > 0)
			ft_add_to_buffer(buffer, ' ');
	}
}

static void	ft_print_formatted(t_format *fmt, va_list args, t_buffer *buffer)
{
	char	*str;

	str = ft_dispatch_specifier(fmt->specifier, args, fmt);
	if (!str)
		return ;
	if ((long)str == -42)
		ft_print_null_char(buffer, fmt);
	else
	{
		ft_add_str_to_buffer(buffer, str);
		free(str);
	}
}

static void	ft_handle_literal(const char *format, int *i, t_buffer *buffer)
{
	ft_add_to_buffer(buffer, format[*i]);
	(*i)++;
}

static void	ft_handle_percent_and_formatted(const char *format, int *i,
				t_print_context *ctx, va_list args)
{
	ft_parse_format(format, i, ctx->fmt, args);
	ft_print_formatted(ctx->fmt, args, ctx->buffer);
	(*i)++;
}
