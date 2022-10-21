/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:16:03 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/21 02:25:25 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>

typedef struct	s_server
{
	int		clt_pid;
	char	handshaked;
	char	byte;
	char	mask;
	int		len;
	char	buff[10000];
}	t_srv;

#endif
