/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:01:04 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/20 22:36:50 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

typedef struct	s_server
{
	int				clt_pid;
	char			handshaked;
	char			octet;
	unsigned char	mask;
	int				len;
	char			buff[10000];
}	t_srv;

static t_srv	g_srv;

/*
void	engage_handshake(void)
{
	int			i;
	sigset_t	sigset;

//	printf("server entering handshake !\n");
	sigemptyset(&sigset);
	i = -1;
	while (++i < 1)
	{
		sigaddset(&sigset, SIGUSR1);
		kill(g_srv.clt_pid, SIGUSR1);
		sigwait(&sigset, NULL);
		g_srv.handshaked = 1;
	}
	kill(g_srv.clt_pid, SIGUSR1);
//	printf("server handshake over ! handshaked status after : %d\n", g_srv.handshaked);
}
*/
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
	int		clt_pid;
	
	if (!g_srv.handshaked)
	{
//		printf("server : initiating handshake. cur handshaked : %d\n", g_srv.handshaked);
//		engage_handshake();
//		printf("server : handshake SUCCESSFULL\n");
		g_srv.clt_pid = siginfo->si_pid;
		g_srv.handshaked = 1;
		g_srv.octet = 0;
		g_srv.mask = 0;
		g_srv.len = 0;
	}
//	printf("server : 1 bit received : %d\n", (sig == SIGUSR2) ? 1 : 0);
	if (sig == SIGUSR2)
		g_srv.octet |= (1 << g_srv.mask);
	g_srv.mask++;
	if (g_srv.mask == 8)
	{
		printf("server : 8-bytes received : %c (%d)\n", g_srv.octet, (int)g_srv.octet);
		if (g_srv.octet == '\0')
		{
			g_srv.buff[g_srv.len++] = '\0';
			ft_printf("%s", g_srv.buff);
			close_connection();
		}
		else
		{
			g_srv.buff[g_srv.len++] = g_srv.octet;
//			write(1, &g_srv.octet, 1);
		}
		g_srv.octet = 0;
		g_srv.mask = 0;
	}
//	printf("signal received : %d, client pid : %d\n", sig, g_srv.clt_pid);
//	printf("signal received : handshake : %d\n", g_srv.handshaked);
}

int	main(void)
{
	char				octet;
	int					mask;
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	printf("server pid : %d\n", getpid());
	sa.sa_sigaction = handle_signals;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
