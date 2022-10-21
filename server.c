/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:07:39 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/20 00:23:04 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

#include <signal.h>
#include <sys/wait.h>//signal.h>
#include <unistd.h>
#include <stdio.h>

int	receiver(void)
{
	char		octet;
	int			sig;
	sigset_t	sigset;
	int			bit;

	printf("receiver : entered\n");
	bit = 1;
	octet = '\0';
	sigemptyset(&sigset);
	printf("receiver : entering loop\n");
	while (1)
	{
		printf("receiver : loop entered\n");
		sigaddset(&sigset, SIGUSR1);
		sigaddset(&sigset, SIGUSR2);
		sigaddset(&sigset, SIGKILL);
		sigaddset(&sigset, SIGTERM);
		sigaddset(&sigset, SIGQUIT);
		sigwait(&sigset, &sig);
		printf("signal received : %d\n", sig);
		if (sig == SIGUSR2)
			octet |= bit;
		else if (sig == SIGKILL || sig == SIGTERM || sig == SIGQUIT)
			break ;
		bit <<= 1;
		if (bit >= 128)
		{
			if (!octet)
				write(1, "\n", 1);
			else
				write(1, &octet, 1);
			octet = 0;
			bit = 1;
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	status;

//	if (argc != 2)
//		return (-1);

	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	receiver();
	
	return (0);
}
