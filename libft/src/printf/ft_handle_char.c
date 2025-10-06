/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:39:08 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:39:10 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_handle_char(t_format *fmt, va_list args)
{
	char	c;
	char	*str;

	c = (char)va_arg(args, int);
	if (c == '\0')
		return ((char *)(long)-42);
	str = malloc(2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (ft_format_output(str, fmt));
}
