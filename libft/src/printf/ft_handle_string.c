/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:40:02 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:40:04 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_handle_string(t_format *fmt, va_list args)
{
	char	*arg;
	char	*str;

	arg = va_arg(args, char *);
	if (!arg)
	{
		if (fmt->has_precision && fmt->precision < 6)
			arg = "";
		else
			arg = "(null)";
	}
	str = ft_strdup(arg);
	if (!str)
		return (NULL);
	return (ft_format_output(str, fmt));
}
