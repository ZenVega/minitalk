/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:48:02 by uschmidt          #+#    #+#             */
/*   Updated: 2024/11/27 10:47:37 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_conversion(char co, va_list arg)
{
	if (co == 'c')
		return (ft_printchar(va_arg(arg, int)));
	else if (co == 's')
		return (ft_printstr(va_arg(arg, char *)));
	else if (co == 'p')
		return (ft_printptr(va_arg(arg, void *)));
	else if (co == 'd' || co == 'i')
		return (ft_putnbr_base(va_arg(arg, int), "0123456789"));
	else if (co == '%')
		return (ft_printprcnt());
	else if (co == 'u')
		return (ft_putnbr_base(va_arg(arg, unsigned int), "0123456789"));
	else if (co == 'x')
		return (ft_putnbr_base(va_arg(arg, unsigned int), "0123456789abcdef"));
	else if (co == 'X')
		return (ft_putnbr_base(va_arg(arg, unsigned int), "0123456789ABCDEF"));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list		arg;
	int			i;
	int			counter;

	if (!str)
		return (-1);
	i = 0;
	counter = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			if (!ft_strchr("cspdiuxX%", str[i + 1]))
				return (-1);
			counter += print_conversion(str[i + 1], arg);
			i += 2;
		}
		else
			counter += ft_printchar(str[i++]);
	}
	va_end(arg);
	return (counter);
}
