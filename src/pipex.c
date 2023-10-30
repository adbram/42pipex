/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:35:28 by aberramo          #+#    #+#             */
/*   Updated: 2023/10/30 20:29:16 by aberramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	dup_first_cmd(t_data *d)
{
	// printf("[%i]first dup\n", d->index);
	close(d->fds[0]);
	if (dup2(d->in_fd, STDIN_FILENO) < 0)
		ft_exit(d, "dup st in\n", EXIT_FAILURE);
	if (dup2(d->fds[1], STDOUT_FILENO) < 0)
		ft_exit(d, "dup st out\n", EXIT_FAILURE);
}

void	dup_middle_cmds(t_data *d)
{
	// printf("[%i]middle dup\n", d->index);
	close(d->fds[0]);
	if (dup2(d->fd_tmp, STDIN_FILENO) < 0)
		ft_exit(d, "dup middle in\n", EXIT_FAILURE);
	if (dup2(d->fds[1], STDOUT_FILENO) < 0)
		ft_exit(d, "dup middle out\n", EXIT_FAILURE);
}

void	dup_last_cmd(t_data *d)
{
	// printf("[%i]last dup\n", d->index);
	close(d->fds[1]);
	if (dup2(d->fd_tmp, STDIN_FILENO) < 0)
		ft_exit(d, "dup last in\n", EXIT_FAILURE);
	if (dup2(d->out_fd, STDOUT_FILENO) < 0)
		ft_exit(d, "dup last out\n", EXIT_FAILURE);
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
	if (execve(d->path, d->cmd, d->env) < 0)
		ft_exit(d, "exec fail\n", EXIT_FAILURE);
}

void	pipex(t_data *d)
{
	while (d->index < d->nb_cmds)
	{
		// printf("[%i]START\n", d->index);
		if (d->index + 1 < d->nb_cmds)
			if (pipe(d->fds) < 0)
				ft_exit(d, "pipe fail\n", EXIT_FAILURE);
		d->pid = fork();
		if (d->pid < 0)
			ft_exit(d, "fork fail\n", EXIT_FAILURE);
		if (d->pid == 0)
			exec_cmd(d);
		if (d->fds[1])
			close(d->fds[1]);
		if (d->fd_tmp)
			close(d->fd_tmp);
		d->fd_tmp = d->fds[0];
		waitpid(d->pid, NULL, 0);
		// printf("[%i]END\n\n", d->index);
		d->index++;
	}
	close(d->fd_tmp);
}
