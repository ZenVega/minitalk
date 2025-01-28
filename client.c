/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:48:38 by uschmidt          #+#    #+#             */
/*   Updated: 2025/01/28 12:01:48 by uschmidt         ###   ########.fr       */
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
void	send_msg(int pid, char *str)
{
	while (*str)
	{
		morse_char(pid, *str);
		str++;
	}
	morse_char(pid, '\0');
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
		send_msg(pid, argv[2]);
	}
	return (1);
}
