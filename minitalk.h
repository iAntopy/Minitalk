/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:16:03 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/20 22:21:34 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>

typedef struct	s_string_chunk_lst
{
	char						buff[10000];
	int							len;
	struct s_string_chunk_lst	*next;
}	t_slst;

#endif
