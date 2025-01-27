/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:57:28 by uschmidt          #+#    #+#             */
/*   Updated: 2024/11/27 16:11:25 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_printstr(char *str)
{
	int	len;

	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	len = ft_strlen(str);
	ft_putstr_fd(str, 1);
	return (len);
}

int	ft_printptr(void *ptr)
{
	int					len;
	unsigned long long	temp;

	len = 2;
	temp = (unsigned long long)ptr;
	if (ptr == NULL)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	while (temp)
	{
		temp /= 16;
		len++;
	}
	ft_putull_base((unsigned long long)ptr, "0123456789abcdef", 0, 16);
	return (len);
}

void	ft_putull_base(unsigned long long nbr,
		char *base, int cnt, int radix)
{
	unsigned long long	div;
	unsigned long long	mod;

	div = nbr / radix;
	mod = nbr % radix;
	if (div)
	{
		cnt++;
		ft_putull_base(div, base, cnt, radix);
	}
	write(1, &base[mod], 1);
}
