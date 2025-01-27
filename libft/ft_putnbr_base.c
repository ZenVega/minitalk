/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:02:03 by uschmidt          #+#    #+#             */
/*   Updated: 2025/01/22 13:22:33 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_base(char *base)
{
	int	counter;
	int	compare_counter;

	counter = 0;
	while (base[counter])
	{
		if (base[counter] == '-' || base[counter] == '+')
			return (0);
		compare_counter = counter - 1;
		while (compare_counter >= 0)
		{
			if (base[counter] != base[compare_counter])
				compare_counter--;
			else
				return (0);
		}
		counter++;
	}
	if (counter < 1)
		return (0);
	return (counter);
}

int	ft_putnbr_base(long long nbr, char *base)
{
	unsigned long long	len;
	unsigned long long	temp;
	int					radix;

	len = 0;
	if (nbr == 0)
		len++;
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
		len++;
	}
	temp = nbr;
	radix = get_base(base);
	if (!radix)
		return (0);
	while (temp)
	{
		temp /= radix;
		len++;
	}
	ft_putull_base(nbr, base, 0, radix);
	return ((int)len);
}
