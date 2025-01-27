/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:31:28 by uschmidt          #+#    #+#             */
/*   Updated: 2024/11/18 18:32:02 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*src;

	i = 0;
	src = (const unsigned char *)s;
	while (i < n)
	{
		if (src[i] == (unsigned char)c)
			return ((void *)src + i);
		i++;
	}
	return (NULL);
}
