/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:48:38 by uschmidt          #+#    #+#             */
/*   Updated: 2025/01/23 15:35:08 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft/libft.h"

#define SLEEP	100

void	sig_handler(int sig_id, siginfo_t *sig_info)
{
	pid_t		pid;

	pid = sig_info->si_pid;
	if (pid && sig_id == SIGUSR1)
		ft_printf("Message received by: %d\n", pid);
}

void	send_bin(int pid, char *str)
{
	int	bit;

	while (*str)
	{
		bit = 7;
		while (bit >= 0)
		{
			if (k(*str & (0x01 << bit)) != 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			bit--;
			usleep(SLEEP);
		}
		str++;
	}
	bit = 7;
	while (bit >= 0)
	{
		if (('\0' & (0x01 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit--;
		usleep(SLEEP);
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sa;

	sa.sa_handler = (void *)sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	write(1, "MESSAGING... ", 13);
	if (argc > 1)
	{
		pid = ft_atoi(argv[1]);
		ft_printf("PID = %d\n", pid);
		send_bin(pid, argv[2]);
	}
	return (1);
}
