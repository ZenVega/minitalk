/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:29:46 by uschmidt          #+#    #+#             */
/*   Updated: 2024/11/18 18:30:59 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digits(int n)
{
	int	digits;

	digits = 1;
	while (n / 10 > 0)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

static int	is_neg(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	int		digits;
	int		neg;
	char	*n_str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	neg = is_neg(n);
	if (neg)
		n *= -1;
	digits = get_digits(n);
	n_str = (char *)malloc(sizeof(char) * (digits + neg + 1));
	if (!n_str)
		return (NULL);
	n_str[digits + neg] = '\0';
	while (digits > 0)
	{
		n_str[digits + neg - 1] = (n % 10) + '0';
		n /= 10;
		digits--;
	}
	if (neg)
		n_str[0] = '-';
	return (n_str);
}
