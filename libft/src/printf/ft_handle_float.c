/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:39:22 by jose-cad          #+#    #+#             */
/*   Updated: 2025/09/08 23:30:24 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

char	*ft_handle_float(t_format *fmt, va_list args)
{
	double	n;
	char	*str;
	int		precision;

	n = va_arg(args, double);
	if (fmt->has_precision)
		precision = fmt->precision;
	else
		precision = 6;
	str = ft_ftoa(n, precision);
	if (!str)
		return (NULL);
	return (ft_format_output(str, fmt));
}
