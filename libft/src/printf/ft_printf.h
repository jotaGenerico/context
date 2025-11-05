/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:13:08 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:13:23 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../../include/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define PF_SIZE 1024

typedef struct s_format
{
	int		flag_minus;
	int		flag_zero;
	int		flag_plus;
	int		flag_space;
	int		flag_hash;
	int		width;
	int		precision;
	int		has_precision;
	char	specifier;
}	t_format;

typedef struct s_buffer
{
	char	buf[PF_SIZE];
	int		index;
	int		printed_count;
	int		fd;
}	t_buffer;

typedef struct s_print_context
{
	t_format	*fmt;
	t_buffer	*buffer;
}	t_print_context;

int		ft_printf(const char *format, ...);
int		ft_dprintf(int fd, const char *format, ...);
int		ft_parse_format(const char *s, int *i, t_format *fmt, va_list args);
char	*ft_handle_char(t_format *fmt, va_list args);
char	*ft_handle_string(t_format *fmt, va_list args);
char	*ft_handle_decimal(t_format *fmt, va_list args);
char	*ft_handle_float(t_format *fmt, va_list args);
char	*ft_handle_hex(t_format *fmt, va_list args);
char	*ft_handle_integer(t_format *fmt, va_list args);
char	*ft_handle_octal(t_format *fmt, va_list args);
char	*ft_handle_pointer(t_format *fmt, va_list args);
char	*ft_handle_percent(t_format *fmt, va_list args);
char	*ft_handle_unsigned(t_format *fmt, va_list args);
char	*ft_format_output(char *str, t_format *fmt);
void	ft_apply_width(char **str, t_format *fmt);
void	ft_apply_precision_str(char **str, t_format *fmt);
char	*ft_apply_precision_num(char *str, t_format *fmt);
char	*ft_apply_hash_flag(char *str, t_format *fmt);
char	*ft_apply_sign_flag(char *str, t_format *fmt);
void	ft_pad_left(char **str, int width, char pad_char);
void	ft_pad_right(char **str, int width);
char	ft_get_safe_pad_char(t_format *fmt);
char	*ft_apply_precision_num_core(char *str, t_format *fmt);
char	*ft_apply_sign(char *str, t_format *fmt);
void	ft_flush_buffer(t_buffer *buffer);
void	ft_add_to_buffer(t_buffer *buffer, char c);
void	ft_add_str_to_buffer(t_buffer *buffer, const char *str);
char	*ft_dispatch_specifier(char spec, va_list args, t_format *fmt);

#endif
