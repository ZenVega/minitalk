/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:02:06 by uschmidt          #+#    #+#             */
/*   Updated: 2025/01/28 13:20:58 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <unistd.h>
# include "libft/libft.h"
# include <signal.h>

# define STR_LEN 1024
# define RESET	2000

typedef struct s_sig {
	int		bit;
	pid_t	pid;
	char	c;
	char	*str;
	size_t	str_max;
}	t_sig;

#endif
