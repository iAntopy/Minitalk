/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:01:04 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/21 20:41:51 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minitalk.h"

static t_srv	g_srv;

void	close_connection(void)
{
//	printf("server : closing connection\n");
//	usleep(1000);
//	kill(g_srv.clt_pid, SIGUSR2);
	g_srv.handshaked = 0;
	g_srv.clt_pid = 0;
}

void	handle_signals(int sig, siginfo_t *siginfo, void *context)
{
//	ft_printf("server handling a signal : %d, siginfo ptr : %p\n", sig, siginfo);
	(void)context;
//	ft_printf("server : handshaked : %d\n", g_srv.handshaked);
	if (!g_srv.handshaked)
	{
//		ft_printf("clt_pid : %d\n", g_srv.clt_pid);
		g_srv.clt_pid = siginfo->si_pid;
		if (siginfo)
			g_srv.clt_pid = siginfo->si_pid;
		g_srv.handshaked = 1;	
		g_srv.byte = 0;
		g_srv.mask = 0;
		g_srv.len = 0;
	}
//	printf("server : 1 bit received : %d\n", (sig == SIGUSR2) ? 1 : 0);
	if (sig == SIGUSR2)
		g_srv.byte |= (1 << g_srv.mask);
	g_srv.mask++;
	if (g_srv.mask == 8)
	{
//		printf("server : 8-bytes received : %c (%d)\n", g_srv.byte, (int)g_srv.byte);
		if (g_srv.byte == '\0')
		{
			g_srv.buff[g_srv.len++] = '\0';
			ft_printf("%s", g_srv.buff);
			close_connection();
		}
		else
			g_srv.buff[g_srv.len++] = g_srv.byte;
		g_srv.byte = 0;
		g_srv.mask = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Oh tell me baby !\n");
	ft_bzero(&sa, sizeof(sa));
	ft_printf("server pid : %d\n", getpid());
	sa.sa_sigaction = handle_signals;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
//		ft_printf("server : going pause mode ...\n");
		pause();
//		ft_printf("server : back from pause mode ...\n");
	}
	return (0);
}
