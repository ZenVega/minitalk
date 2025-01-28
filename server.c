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

#define STR_LEN 12

typedef struct s_sig {
	int		bit;
	pid_t	pid;
	char	c;
	char	*str;
}	t_sig;

static t_sig	*g_sig;

void	send_return(int pid)
{
	g_sig->str[ft_strlen(g_sig->str)] = '\0';
	ft_printf("%s\n", g_sig->str);
	kill(pid, SIGUSR1);
	g_sig->pid = -1;
	g_sig->bit = 7;
	g_sig->c = 0;
	free(g_sig->str);
}

void	reset_c(void)
{
	int	str_len;

	str_len = ft_strlen(g_sig->str);
	g_sig->str[str_len] = g_sig->c;
	g_sig->bit = 7;
	g_sig->c = 0;
}

void	sig_handler(int sig_id, siginfo_t *sig_info, void *context)
{
	(void)context;
	if (g_sig->pid == -1)
	{
		g_sig->pid = sig_info->si_pid;
		g_sig->str = (char *)ft_calloc(STR_LEN, sizeof(char));
	}
	if (g_sig->pid != sig_info->si_pid)
		return ;
	if (sig_id == SIGUSR1)
		g_sig->c |= 0x01 << g_sig->bit;
	g_sig->bit--;
	if (g_sig->bit == -1)
	{
		if (g_sig->c == '\0')
			send_return(g_sig->pid);
		else
			reset_c();
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	g_sig = (t_sig *)malloc(sizeof(t_sig));
	if (!g_sig)
		return (1);
	g_sig->pid = -1;
	g_sig->c = 0;
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	g_sig->bit = 7;
	pid = getpid();
	ft_printf("PID: %d\n", pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		continue ;
	free(g_sig);
	return (1);
}
