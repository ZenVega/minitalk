/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:48:38 by uschmidt          #+#    #+#             */
/*   Updated: 2025/01/28 13:21:25 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	g_pid;

void	morse_char(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((c & (0x01 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit--;
		usleep(SLEEP);
	}
}

void	sig_handler(int sig_id, siginfo_t *sig_info)
{
	pid_t		pid;

	if (sig_id == SIGINT)
	{
		morse_char(g_pid, '\0');
		exit(0);
	}
	pid = sig_info->si_pid;
	if (pid && sig_id == SIGUSR1)
		ft_printf("Message received by: %d\n", pid);
	exit(0);
}

void	send_msg(char *str)
{
	while (*str)
	{
		morse_char(g_pid, *str);
		str++;
	}
	morse_char(g_pid, '\0');
	pause();
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	sa.sa_handler = (void *)sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	write(1, "MESSAGING... ", 13);
	if (argc > 1)
	{
		g_pid = ft_atoi(argv[1]);
		ft_printf("PID = %d\n", g_pid);
		send_msg(argv[2]);
	}
	return (1);
}
