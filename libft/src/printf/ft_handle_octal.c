/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_octal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:39:22 by jose-cad          #+#    #+#             */
/*   Updated: 2025/09/08 23:30:24 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static char	*ft_apply_octal_hash(char *str, unsigned int n)
{
	char	*new_str;
	int		len;

	if (n == 0 || str[0] == '0')
		return (str);
	len = (int)ft_strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	new_str[0] = '0';
	ft_strlcpy(new_str + 1, str, len + 1);
	free(str);
	return (new_str);
}

char	*ft_handle_octal(t_format *fmt, va_list args)
{
	unsigned int	n;
	char			*str;

	if (!fmt)
		return (NULL);
	n = va_arg(args, unsigned int);
	if (n == 0 && fmt->has_precision && fmt->precision == 0)
		str = ft_strdup("");
	else
		str = ft_utoa_base(n, "01234567");
	if (!str)
		return (NULL);
	if (fmt->flag_hash)
	{
		str = ft_apply_octal_hash(str, n);
		if (!str)
			return (NULL);
	}
	return (ft_format_output(str, fmt));
}
