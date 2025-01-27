/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:36:27 by uschmidt          #+#    #+#             */
/*   Updated: 2024/11/19 09:38:14 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_start(char const *s, char const *set)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (set[i])
	{
		if (set[i] == s[start])
		{
			start++;
			i = 0;
		}
		else
			i++;
	}
	return (start);
}

static int	find_end(char const *s, char const *set)
{
	int	i;
	int	end;

	i = 0;
	end = ft_strlen(s);
	while (set[i])
	{
		if (set[i] == s[end - 1])
		{
			end--;
			i = 0;
		}
		else
			i++;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;

	if (!s1 || !set)
		return (NULL);
	start = find_start(s1, set);
	end = find_end(s1, set);
	return (ft_substr(s1, start, end - start));
}
