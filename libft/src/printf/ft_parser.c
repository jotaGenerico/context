/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:40:31 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:40:34 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_flag(char c);
static void	ft_parse_flags(const char *s, int *i, t_format *fmt);
static void	ft_parse_width_precision(const char *s, int *i, t_format *fmt);

int	ft_parse_format(const char *s, int *i, t_format *fmt, va_list args)
{
	(void)args;
	(*i)++;
	fmt->flag_minus = 0;
	fmt->flag_zero = 0;
	fmt->flag_plus = 0;
	fmt->flag_space = 0;
	fmt->flag_hash = 0;
	fmt->width = 0;
	fmt->precision = 0;
	fmt->has_precision = 0;
	fmt->specifier = 0;
	ft_parse_flags(s, i, fmt);
	ft_parse_width_precision(s, i, fmt);
	fmt->specifier = s[*i];
	return (1);
}

static void	ft_parse_width_precision(const char *s, int *i, t_format *fmt)
{
	while (s[*i] >= '0' && s[*i] <= '9')
		fmt->width = fmt->width * 10 + (s[(*i)++] - '0');
	if (s[*i] == '.')
	{
		fmt->has_precision = 1;
		(*i)++;
		while (s[*i] >= '0' && s[*i] <= '9')
			fmt->precision = fmt->precision * 10 + (s[(*i)++] - '0');
	}
}

static void	ft_parse_flags(const char *s, int *i, t_format *fmt)
{
	while (is_flag(s[*i]))
	{
		if (s[*i] == '-')
			fmt->flag_minus = 1;
		else if (s[*i] == '0')
			fmt->flag_zero = 1;
		else if (s[*i] == '+')
			fmt->flag_plus = 1;
		else if (s[*i] == ' ')
			fmt->flag_space = 1;
		else if (s[*i] == '#')
			fmt->flag_hash = 1;
		(*i)++;
	}
	if (fmt->flag_minus)
		fmt->flag_zero = 0;
}

static int	is_flag(char c)
{
	return (c == '-' || c == '0' || c == '+' || c == ' ' || c == '#');
}
