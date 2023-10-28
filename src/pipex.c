/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:35:28 by aberramo          #+#    #+#             */
/*   Updated: 2023/10/28 19:56:08 by aberramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	dup_first_cmd(t_data *d)
{
	// printf("first_dup\nd->index = %i\n\n", d->index);
	if (dup2(d->in_fd, STDIN_FILENO) < 0)
		ft_exit(d, "dup st\n", EXIT_FAILURE);
	if (dup2(d->fds[1], STDOUT_FILENO) < 0)
		ft_exit(d, "dup st\n", EXIT_FAILURE);
	close(d->in_fd);
	close(d->fds[1]);
	d->fd_tmp = d->fds[0];
}

void	dup_middle_cmds(t_data *d)
{
	// printf("middle_dup\nd->index = %i\n\n", d->index);
	if (dup2(d->fd_tmp, STDIN_FILENO) < 0)
		ft_exit(d, "dup middle\n", EXIT_FAILURE);
	if (dup2(d->fds[1], STDOUT_FILENO) < 0)
		ft_exit(d, "dup middle\n", EXIT_FAILURE);
	close(d->fd_tmp);
	close(d->fds[1]);
	d->fd_tmp = d->fds[0];
}

void	dup_last_cmd(t_data *d)
{
	// printf("last_dup\nd->index = %i\n\n", d->index);
	if (dup2(d->fd_tmp, STDIN_FILENO) < 0)
		ft_exit(d, "dup last tmp\n", EXIT_FAILURE);
	if (dup2(d->out_fd, STDOUT_FILENO) < 0)
		ft_exit(d, "dup last out_fd\n", EXIT_FAILURE);
	close(d->fd_tmp);
	close(d->out_fd);
}

void	exec_cmd(t_data *d)
{
	if (d->index == 0)
		dup_first_cmd(d);
	else if (d->index + 1 < d->nb_cmds)
		dup_middle_cmds(d);
	else
		dup_last_cmd(d);
	d->cmd = ft_split(d, d->av[d->index + 2], " \n\t\v\f\r");
	cmd_path(d);
	execve(d->path, d->cmd, d->env);
}

void	pipex(t_data *d)
{
	while (d->index < d->nb_cmds)
	{
		if (d->index + 1 < d->nb_cmds)
			if (pipe(d->fds) < 0)
				ft_exit(d, "pipe fail\n", EXIT_FAILURE);
		d->pid = fork();
		if (d->pid < 0)
			ft_exit(d, "fork fail\n", EXIT_FAILURE);
		if (d->pid == 0)
			exec_cmd(d);
		close(d->fds[0]);
		close(d->fds[1]);
		waitpid(d->pid, NULL, 0);
		d->index++;
	}
}
