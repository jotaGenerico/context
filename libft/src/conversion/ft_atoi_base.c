/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:12:00 by jose-cad          #+#    #+#             */
/*   Updated: 2025/06/10 11:12:03 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_base(const char *base);
static int	ft_base_index(char c, const char *base);

int	ft_atoi_base(const char *str, const char *base)
{
	long	result;
	int		sign;
	int		base_len;

	result = 0;
	sign = 1;
	if (!str || !ft_check_base(base))
		return (0);
	base_len = ft_strlen(base);
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && ft_base_index(*str, base) != -1)
	{
		result = result * base_len + ft_base_index(*str, base);
		str++;
	}
	return (result * sign);
}

static int	ft_check_base(const char *base)
{
	int	i;
	int	j;
	int	b_len;

	if (!base)
		return (0);
	i = 0;
	b_len = ft_strlen(base);
	if (b_len <= 1)
		return (0);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-' || ft_isspace(base[i]))
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	ft_base_index(char c, const char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}
