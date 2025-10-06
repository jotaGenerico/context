#include "ft_printf.h"
#include "libft.h"

char	*ft_handle_float(t_format *fmt, va_list args)
{
	double	n;
	char	*str;
	int		precision;

	n = va_arg(args, double);
	if (fmt->has_precision)
		precision = fmt->precision;
	else
		precision = 6;
	str = ft_ftoa(n, precision);
	if (!str)
		return (NULL);
	return (ft_format_output(str, fmt));
}
