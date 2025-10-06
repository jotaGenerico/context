/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:38:54 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:38:57 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_apply_width(char **str, t_format *fmt)
{
	int		width;
	char	pad_char;

	if (!str || !fmt)
		return ;
	width = fmt->width;
	if (width <= (int)ft_strlen(*str))
		return ;
	pad_char = ft_get_safe_pad_char(fmt);
	if (fmt->flag_minus)
		ft_pad_right(str, width);
	else
		ft_pad_left(str, width, pad_char);
}

char	ft_get_pad_char(t_format *fmt)
{
	if (fmt->flag_zero && !fmt->flag_minus)
		return ('0');
	return (' ');
}

void	ft_pad_right(char **str, int width)
{
	int		len;
	int		i;
	char	*new_str;

	len = (int)ft_strlen(*str);
	if (width <= len)
		return ;
	new_str = malloc(width + 1);
	if (!new_str)
		return ;
	ft_memcpy(new_str, *str, len);
	i = len;
	while (i < width)
		new_str[i++] = ' ';
	new_str[i] = '\0';
	free(*str);
	*str = new_str;
}

void	ft_pad_left(char **str, int width, char pad_char)
{
	int		len;
	int		i;
	int		sign_len;
	char	*new_str;

	len = (int)ft_strlen(*str);
	if (width <= len)
		return ;
	new_str = malloc(width + 1);
	if (!new_str)
		return ;
	sign_len = 0;
	if (pad_char == '0' && ((*str)[0] == '+' || (*str)[0] == '-'
		|| (*str)[0] == ' '))
		sign_len = 1;
	i = -1;
	while (++i < sign_len)
		new_str[i] = (*str)[i];
	while (i < width - len + sign_len)
		new_str[i++] = pad_char;
	ft_memcpy(new_str + i, *str + sign_len, len - sign_len);
	new_str[width] = '\0';
	free(*str);
	*str = new_str;
}

char	ft_get_safe_pad_char(t_format *fmt)
{
	if (!fmt)
		return (' ');
	if (fmt->flag_minus)
		return (' ');
	if (fmt->has_precision && (fmt->specifier == 'd' || fmt->specifier == 'i'
			|| fmt->specifier == 'u' || fmt->specifier == 'x'
			|| fmt->specifier == 'X'))
		return (' ');
	if (fmt->specifier == '%' || fmt->specifier == 's' || fmt->specifier == 'c')
		return (' ');
	if (fmt->flag_zero)
		return ('0');
	return (' ');
}
