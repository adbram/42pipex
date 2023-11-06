/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 23:50:11 by aberramo          #+#    #+#             */
/*   Updated: 2023/11/06 19:34:02 by aberramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	pipex(t_data *d)
{
	while (d->i < d->nb_cmds)
	{
		if (d->i + 1 < d->nb_cmds)
			if (pipe(d->fds) < 0)
				ft_exit(d, "Pipe fail", EXIT_FAILURE);
		d->pids[d->i] = fork();
		if (d->pids[d->i] < 0)
			ft_exit(d, "Fork fail", EXIT_FAILURE);
		if (d->pids[d->i] == 0)
			exec_cmd(d);
		ft_close(&d->fds[1]);
		ft_close(&d->fd_tmp);
		d->fd_tmp = d->fds[0];
		d->i++;
	}
	d->i = 0;
	while (d->i < d->nb_cmds)
	{
		waitpid(d->pids[d->i], NULL, 0);
		d->i++;
	}
}
