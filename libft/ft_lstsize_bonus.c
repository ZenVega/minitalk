/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:38:55 by uschmidt          #+#    #+#             */
/*   Updated: 2024/11/19 10:38:57 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*tmp;

	if (lst)
	{
		tmp = lst;
		i = 1;
		while (tmp->next)
		{
			tmp = tmp->next;
			i++;
		}
		return (i);
	}
	return (0);
}
