/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:12:35 by uschmidt          #+#    #+#             */
/*   Updated: 2025/01/28 13:51:15 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_sig	*g_sig;

int	init_g_sig(void)
{
	g_sig = (t_sig *)ft_calloc(sizeof(t_sig), 1);
	if (!g_sig)
		return (0);
	g_sig->str_max = STR_LEN;
	g_sig->str = (char *)ft_calloc(g_sig->str_max, sizeof(char));
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

void	reset_server(void)
{
	if (g_sig)
	{
		if (g_sig->str)
			free(g_sig->str);
		free(g_sig);
		g_sig = NULL;
	}
}

void	reset_c(void)
{
	size_t	str_len;
	char	*tmp;

	str_len = ft_strlen(g_sig->str);
	if (str_len >= g_sig->str_max - 2)
	{
		tmp = (char *)ft_calloc((g_sig->str_max + STR_LEN + 1), sizeof(char));
		ft_strlcpy(tmp, g_sig->str, g_sig->str_max);
		free(g_sig->str);
		g_sig->str = tmp;
		g_sig->str_max += STR_LEN;
	}
	g_sig->str[str_len] = g_sig->c;
	g_sig->bit = 7;
	g_sig->c = 0;
}

void	sig_handler(int sig_id, siginfo_t *sig_info, void *context)
{
	(void)context;
	if (sig_id == SIGINT)
		(reset_server(), exit(0));
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
		{
			ft_printf("%s", g_sig->str);
			kill(g_sig->pid, SIGUSR1);
			reset_server();
		}
		else
			reset_c();
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	pid = getpid();
	ft_printf("PID: %d\n", pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	while (1)
		pause();
	return (0);
}
