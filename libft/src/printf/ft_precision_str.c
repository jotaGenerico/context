/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:41:24 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:41:28 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_apply_precision_str(char **str, t_format *fmt)
{
	char	*new_str;
	int		len;

	if (!str || !*str)
		return ;
	if (!fmt->has_precision)
		return ;
	if (fmt->precision < 0)
		return ;
	if (fmt->precision == 0)
	{
		free(*str);
		*str = ft_strdup("");
		return ;
	}
	len = (int)ft_strlen(*str);
	if (len > fmt->precision)
	{
		new_str = ft_substr(*str, 0, fmt->precision);
		if (!new_str)
			return ;
		free(*str);
		*str = new_str;
	}
}
