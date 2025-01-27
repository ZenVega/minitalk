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

void	send_bin(int pid, char *str)
{
	int	bit;

	while (*str)
	{
		bit = 7;
		while (bit >= 0)
		{
			if ((*str & (0x01 << bit)) != 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			bit--;
			usleep(42);
		}
		str++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	write(1, "SIGNALING...\n", 13);
	if (argc > 1)
	{
		pid = ft_atoi(argv[1]);
		ft_printf("PID = %d\n", pid);
		send_bin(pid, argv[2]);
	}
	return (1);
}
