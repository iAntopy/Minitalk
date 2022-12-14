/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:37:55 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/21 20:43:01 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	close_connection(int srv_pid)
{
//	sigset_t	sigset;
//	int			sig;
	int			i;

	printf("client closing connection !\n");

	printf("client sending \\0 terminating char.\n");
	i = -1;
	while (++i < 8)
	{
		kill(srv_pid, SIGUSR1);
		usleep(1000);
	}
//	sigemptyset(&sigset);
//	sigaddset(&sigset, SIGUSR2);
//	sigwait(&sigset, &sig);
//	if (sig == SIGUSR2)
//		printf("clent received closing signal and closes connection.");
///	else if (sig == SIGUSR1)
//		printf("clent received wrong signal. All is not good in the world.");
}

void	signal_sender(int srv_pid, char *str)
{
	char			c;
	unsigned char	i;

	printf("client : signal transport starting\n");
	while (*str)
	{
		c = *str;
		i = -1;
//		printf("cient sending char : %c\n", c);
		while (++i < 8)
		{
//			printf("client : mask : %d, bit %d\n", (1 << i), !!(c & (1 << i)));
			if (c & (1 << i))
				kill(srv_pid, SIGUSR2);
			else
				kill(srv_pid, SIGUSR1);
			usleep(50);
//			printf("cient next char : %c\n", *(str + 1));
//			usleep(ping);
		}
		str++;
//		printf("cient next char : %c\n", *str);
	}
	close_connection(srv_pid);
//	printf("client : signal transport over\n");
}

int	main(int argc, char **argv)
{
	int		 pid;
//	ssize_t	ping;

	if (argc != 3)
	{
		ft_printf("client inputs : {server pid} {message}\n");
		return (0);
	}
	pid = ft_atoi(argv[1]);
//	ping = engage_handshake(pid);
//	ft_printf("ping : %d\n", (int)ping);
	signal_sender(pid, argv[2]);//"Maman fait des gateaux delicieux");
	printf("client : signal transport completed SUCCESSFULLY.\n");
	return (0);
}
