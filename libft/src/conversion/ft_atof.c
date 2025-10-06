/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:25:36 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:25:45 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_parse_fraction(const char *str, int *index);
static double	ft_parse_integer(const char *str, int *index);
static int		ft_sign(const char *str, int *index);

double	ft_atof(const char *str)
{
	int		i;
	int		sign;
	double	int_part;
	double	frac_part;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = ft_sign(str, &i);
	int_part = ft_parse_integer(str, &i);
	frac_part = ft_parse_fraction(str, &i);
	return (sign * (int_part + frac_part));
}

static int	ft_sign(const char *str, int *index)
{
	int	sign;

	sign = 1;
	if (str[*index] == '-' || str[*index] == '+')
	{
		if (str[*index] == '-')
			sign = -1;
		(*index)++;
	}
	return (sign);
}

static double	ft_parse_integer(const char *str, int *index)
{
	double	res;

	res = 0.0;
	while (ft_isdigit(str[*index]))
	{
		res = res * 10.0 + (str[*index] - '0');
		(*index)++;
	}
	return (res);
}

static double	ft_parse_fraction(const char *str, int *index)
{
	double	frac;
	double	divisor;

	frac = 0.0;
	divisor = 1.0;
	if (str[*index] == '.')
	{
		(*index)++;
		while (ft_isdigit(str[*index]))
		{
			frac = frac * 10.0 + (str[*index] - '0');
			divisor *= 10.0;
			(*index)++;
		}
		return (frac / divisor);
	}
	return (0.0);
}
