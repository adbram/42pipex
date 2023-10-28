/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:35:28 by aberramo          #+#    #+#             */
/*   Updated: 2023/10/28 05:41:18 by aberramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	first_cmd(t_data *d)
{
	if (dup2(d->in_fd, STDIN_FILENO) < 0)
		ft_exit(d, EXIT_FAILURE);
	if (dup2(d->fds[1], STDOUT_FILENO) < 0)
		ft_exit(d, EXIT_FAILURE);
	close(d->in_fd);
	close(d->fds[0]);
	close(d->fds[1]);
	execve(cmd_path(d), ft_split(d, d->av[d->index + 2], " \n\t\v\f\r"), d->env);
}

void	exec_cmd(t_data *d)
{
	if (d->index == 0)
		first_cmd(d);
	else if (d->index + 1 < d->nb_cmds)
		middle_cmds(d);
	else
		last_cmd(d);
}

void	pipex(t_data *d)
{
	printf("d->index = %i\n", d->index);
	printf("d->nb_cmds = %i\n", d->nb_cmds);
	while (d->index < d->nb_cmds)
	{
		if (d->index + 1 < d->nb_cmds)
			if (pipe(d->fds) < 0)
				ft_exit(d, EXIT_FAILURE);
		d->pid = fork();
		if (d->pid < 0)
			ft_exit(d, EXIT_FAILURE);
		if (d->pid == 0)
			exec_cmd(d);
		close(d->fds[0]);
		close(d->fds[1]);
		waitpid(d->pid, NULL, 0);
		d->index++;
	}
}
