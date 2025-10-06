/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:39:51 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:39:55 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static char	*ft_apply_pointer_prefix(char *str);

char	*ft_handle_pointer(t_format *fmt, va_list args)
{
	void			*ptr;
	unsigned long	addr;
	char			*num_str;

	ptr = va_arg(args, void *);
	if (!ptr)
		return (ft_format_output(ft_strdup("(nil)"), fmt));
	addr = (unsigned long)ptr;
	num_str = ft_ptr_hextoa(addr);
	if (!num_str)
		return (NULL);
	fmt->has_precision = 0;
	num_str = ft_apply_pointer_prefix(num_str);
	if (!num_str)
		return (NULL);
	num_str = ft_format_output(num_str, fmt);
	return (num_str);
}

static char	*ft_apply_pointer_prefix(char *str)
{
	char	*new_str;

	new_str = malloc(ft_strlen(str) + 3);
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	new_str[0] = '0';
	new_str[1] = 'x';
	ft_strlcpy(new_str + 2, str, ft_strlen(str) + 1);
	free(str);
	return (new_str);
}
