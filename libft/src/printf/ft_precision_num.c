/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision_num.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:40:41 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:40:43 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static char	*ft_alloc_num_str(int prec, int has_sign)
{
	char	*new_str;

	if (has_sign)
		new_str = malloc(prec + 2);
	else
		new_str = malloc(prec + 1);
	return (new_str);
}

static void	ft_fill_num_str(char *new_str, char *str, int prec, int len)
{
	int		i;
	int		j;
	int		sign;

	i = 0;
	j = 0;
	sign = (str[0] == '-');
	if (sign)
		new_str[i++] = '-';
	while (i < (prec - len + sign))
		new_str[i++] = '0';
	while (str[j])
	{
		if (sign && j == 0)
			j++;
		new_str[i++] = str[j++];
	}
	new_str[i] = '\0';
}

char	*ft_apply_precision_num(char *str, t_format *fmt)
{
	if (!str || !fmt)
		return (NULL);
	if (!fmt->has_precision)
		return (str);
	if (fmt->precision == 0 && ft_strncmp(str, "0", 2) == 0)
	{
		free(str);
		return (ft_strdup(""));
	}
	return (ft_apply_precision_num_core(str, fmt));
}

char	*ft_apply_precision_num_core(char *str, t_format *fmt)
{
	int		len;
	int		prec;
	char	*new_str;
	int		has_sign;

	prec = fmt->precision;
	len = (int)ft_strlen(str);
	has_sign = (str[0] == '-');
	if (has_sign)
		len--;
	if (len >= prec)
		return (str);
	new_str = ft_alloc_num_str(prec, has_sign);
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	ft_fill_num_str(new_str, str, prec, len);
	free(str);
	return (new_str);
}
