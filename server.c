/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:12:35 by uschmidt          #+#    #+#             */
/*   Updated: 2025/01/23 15:07:17 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft/libft.h"
#include <signal.h>

static int	g_bit;

void	sig_handler(int sig_id)
{
	static char	c;

	ft_printf("%c", g_bit);
	if (sig_id == SIGUSR1)
		c |= 0x01 << g_bit;
	g_bit--;
	if (g_bit == -1)
	{
		ft_printf("%c", c);
		g_bit = 7;
		c = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_handler = sig_handler;
	g_bit = 7;
	pid = getpid();
	ft_printf("PID: %d\n", pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		continue ;
	return (1);
}
