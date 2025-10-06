/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:40:24 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:40:26 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static char	*ft_handle_sign_flag(char *str, t_format *fmt);
static char	*ft_handle_hash_flag(char *str, t_format *fmt);
static char	*ft_handle_precision(char *str, t_format *fmt);
static int	ft_is_hash_applicable(char spec);

char	*ft_format_output(char *str, t_format *fmt)
{
	if (!str || !fmt)
		return (NULL);
	str = ft_handle_precision(str, fmt);
	if (!str)
		return (NULL);
	str = ft_handle_hash_flag(str, fmt);
	if (!str)
		return (NULL);
	str = ft_handle_sign_flag(str, fmt);
	if (!str)
		return (NULL);
	ft_apply_width(&str, fmt);
	return (str);
}

static int	ft_is_hash_applicable(char spec)
{
	if (spec == 'x' || spec == 'X')
		return (1);
	return (0);
}

static char	*ft_handle_precision(char *str, t_format *fmt)
{
	char	*tmp;

	if (fmt->specifier == 's')
		ft_apply_precision_str(&str, fmt);
	else
	{
		tmp = ft_apply_precision_num(str, fmt);
		if (!tmp)
		{
			free(str);
			return (NULL);
		}
		str = tmp;
	}
	return (str);
}

static char	*ft_handle_hash_flag(char *str, t_format *fmt)
{
	char	*tmp;

	tmp = NULL;
	if (fmt->flag_hash == 1 && ft_is_hash_applicable(fmt->specifier))
	{
		tmp = ft_apply_hash_flag(str, fmt);
		if (!tmp)
		{
			free(str);
			return (NULL);
		}
		str = tmp;
	}
	return (str);
}

static char	*ft_handle_sign_flag(char *str, t_format *fmt)
{
	char	*tmp;

	tmp = NULL;
	if (fmt->specifier == 'd' || fmt->specifier == 'i')
	{
		tmp = ft_apply_sign_flag(str, fmt);
		if (!tmp)
		{
			free(str);
			return (NULL);
		}
		str = tmp;
	}
	return (str);
}
