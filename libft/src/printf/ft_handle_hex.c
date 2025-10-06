/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:39:22 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:39:24 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_handle_hex(t_format *fmt, va_list args)
{
	unsigned int	n;
	char			*str;

	if (!fmt)
		return (NULL);
	n = va_arg(args, unsigned int);
	if (n == 0 && fmt->has_precision && fmt->precision == 0)
		str = ft_strdup("");
	else if (fmt->specifier == 'X')
		str = ft_utoa_base(n, "0123456789ABCDEF");
	else
		str = ft_utoa_base(n, "0123456789abcdef");
	if (!str)
		return (NULL);
	str = ft_format_output(str, fmt);
	return (str);
}
