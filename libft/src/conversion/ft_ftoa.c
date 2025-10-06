/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:28:04 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:28:09 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_power(int nb, int power);
static char	*get_fraction_str(long long frac, int precision);
static char	*ft_join_parts(char *int_str, char *frac_str);

char	*ft_ftoa(double n, int precision)
{
	long long	int_part;
	long long	frac_part;
	char		*int_str;
	char		*frac_str;
	int			is_negative;

	if (precision < 0)
		precision = 6;
	is_negative = (n < 0);
	if (n < 0)
		n = -n;
	int_part = (long long)n;
	frac_part = (long long)((n - int_part) * ft_power(10, precision) + 0.5);
	if (is_negative)
		int_part = -int_part;
	int_str = ft_itoa(int_part);
	if (!int_str)
		return (NULL);
	frac_str = get_fraction_str(frac_part, precision);
	if (!frac_str)
		return (free(int_str), NULL);
	return (ft_join_parts(int_str, frac_str));
}

static char	*get_fraction_str(long long frac, int precision)
{
	char	*str;
	int		i;

	str = malloc(precision + 1);
	if (!str)
		return (NULL);
	str[precision] = '\0';
	i = precision - 1;
	while (i >= 0)
	{
		str[i] = (frac % 10) + '0';
		frac /= 10;
		i--;
	}
	return (str);
}

static char	*ft_join_parts(char *int_str, char *frac_str)
{
	char	*temp;
	char	*res;

	temp = ft_strjoin(".", frac_str);
	free(frac_str);
	if (!temp)
	{
		free(int_str);
		return (NULL);
	}
	res = ft_strjoin(int_str, temp);
	free(int_str);
	free(temp);
	return (res);
}

static int	ft_power(int nb, int power)
{
	int	result;

	result = 1;
	if (power < 0)
		return (0);
	if (nb == 0 && power == 0)
		return (1);
	while (power > 0)
	{
		result *= nb;
		power--;
	}
	return (result);
}
