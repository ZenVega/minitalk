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

typedef struct s_client {
	pid_t		pid;
	int			bit;
	char		cur;
	t_client	*next;
}	t_client;

void	send_return(int pid)
{
	kill(pid, SIGUSR1);
}

void	sig_handler(int sig_id, siginfo_t *sig_info, void *context)
{
	static char	c;
	pid_t		pid;

	(void)context;
	pid = sig_info->si_pid;
	//ft_printf("\nUT: %d\n", pid);
	if (sig_id == SIGUSR1)
		c |= 0x01 << g_bit;
	g_bit--;
	if (g_bit == -1)
	{
		if (c == '\0')
			send_return(pid);
		else
			ft_printf("%c", c);
		g_bit = 7;
		c = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	//TODO: create client list
	//TODO: block for extra signals
	g_bit = 7;
	pid = getpid();
	ft_printf("PID: %d\n", pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		continue ;
	return (1);
}
