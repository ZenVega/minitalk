/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:12:35 by uschmidt          #+#    #+#             */
/*   Updated: 2025/01/28 12:12:00 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_sig	*g_sig;

int	init_g_sig(void)
{
	g_sig = (t_sig *)malloc(sizeof(t_sig));
	if (!g_sig)
		return (0);
	g_sig->str = (char *)ft_calloc(g_sig->str_max, sizeof(char));
	g_sig->str_max = STR_LEN;
	if (!g_sig->str)
	{
		free(g_sig);
		return (0);
	}
	g_sig->pid = -1;
	g_sig->c = 0;
	g_sig->bit = 7;
	return (1);
}

void	send_and_return(int pid)
{
	g_sig->str[ft_strlen(g_sig->str)] = '\0';
	ft_printf("%s", g_sig->str);
	kill(pid, SIGUSR1);
	g_sig->pid = -1;
	g_sig->bit = 7;
	g_sig->c = 0;
	free(g_sig->str);
	free(g_sig);
	g_sig = NULL;
}

void	reset_c(void)
{
	size_t	str_len;
	char	*tmp;

	str_len = ft_strlen(g_sig->str);
	g_sig->str[str_len] = g_sig->c;
	if (str_len >= g_sig->str_max - 2)
	{
		tmp = (char *)ft_calloc((g_sig->str_max + STR_LEN), sizeof(char));
		ft_strlcpy(tmp, g_sig->str, g_sig->str_max);
		free(g_sig->str);
		g_sig->str = tmp;
		g_sig->str_max += STR_LEN;
	}
	g_sig->bit = 7;
	g_sig->c = 0;
}

void	sig_handler(int sig_id, siginfo_t *sig_info, void *context)
{
	(void)context;
	if (!g_sig)
	{
		if (!init_g_sig())
			return ;
		g_sig->pid = sig_info->si_pid;
	}
	if (g_sig->pid != sig_info->si_pid)
		return ;
	if (sig_id == SIGUSR1)
		g_sig->c |= 0x01 << g_sig->bit;
	g_sig->bit--;
	if (g_sig->bit == -1)
	{
		if (g_sig->c == '\0')
			send_and_return(g_sig->pid);
		else
			reset_c();
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	pid = getpid();
	ft_printf("PID: %d\n", pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		continue ;
	free(g_sig);
	return (1);
}
