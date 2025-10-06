/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:40:17 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:40:20 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_apply_sign_flag(char *str, t_format *fmt)
{
	char	*new_str;
	int		len;

	if (!str || !fmt)
		return (NULL);
	if (!fmt->flag_plus && !fmt->flag_space)
		return (str);
	if (str[0] == '-')
		return (str);
	len = (int)ft_strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	if (fmt->flag_plus)
		new_str[0] = '+';
	else
		new_str[0] = ' ';
	ft_memcpy(new_str + 1, str, len + 1);
	free(str);
	return (new_str);
}

char	*ft_apply_hash_flag(char *str, t_format *fmt)
{
	char	*new_str;
	int		len;

	if (!str || !fmt)
		return (NULL);
	if (!fmt->flag_hash)
		return (str);
	if (str[0] == '0' && str[1] == '\0')
		return (str);
	len = (int)ft_strlen(str);
	new_str = malloc(len + 3);
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	new_str[0] = '0';
	if (fmt->specifier == 'X')
		new_str[1] = 'X';
	else
		new_str[1] = 'x';
	ft_memcpy(new_str + 2, str, len + 1);
	free(str);
	return (new_str);
}
