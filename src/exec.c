/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 00:04:18 by aberramo          #+#    #+#             */
/*   Updated: 2023/11/05 21:04:58 by aberramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	dup_first_cmd(t_data *d)
{
	d->in_fd = open(d->in_file, O_RDONLY);
	if (d->in_fd < 0)
		ft_exit(d, "Open infile fail\n", EXIT_FAILURE);
	ft_close(&d->fds[0]);
	if (dup2(d->in_fd, STDIN_FILENO) < 0)
		ft_exit(d, "Dup dup_first_cmd STDIN\n", EXIT_FAILURE);
	if (dup2(d->fds[1], STDOUT_FILENO) < 0)
		ft_exit(d, "Dup dup_first_cmd STDIN\n", EXIT_FAILURE);
}

void	dup_middle_cmd(t_data *d)
{
	ft_close(&d->fds[0]);
	if (dup2(d->fd_tmp, STDIN_FILENO) < 0)
		ft_exit(d, "Dup dup_middle_cmd STDIN\n", EXIT_FAILURE);
	if (dup2(d->fds[1], STDOUT_FILENO) < 0)
		ft_exit(d, "Dup dup_middle_cmd STDIN\n", EXIT_FAILURE);
}

void	dup_last_cmd(t_data *d)
{
	d->out_fd = open(d->out_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (d->out_fd < 0)
		ft_exit(d, "Open outfile fail\n", EXIT_FAILURE);
	if (dup2(d->fd_tmp, STDIN_FILENO) < 0)
		ft_exit(d, "Dup dup_last_cmd STDIN\n", EXIT_FAILURE);
	if (dup2(d->out_fd, STDOUT_FILENO) < 0)
		ft_exit(d, "Dup dup_last_cmd STDIN\n", EXIT_FAILURE);
}

void	exec_cmd(t_data *d)
{
	if (d->i == 0)
		dup_first_cmd(d);
	else if (d->i + 1 < d->nb_cmds)
		dup_middle_cmd(d);
	else
		dup_last_cmd(d);
	d->cmd = ft_split(d, d->av[d->i + 2], " \n\t\v\f\r");
	d->path = get_path(d);
	if (execve(d->path, d->cmd->tab, d->env) < 0)
		ft_exit(d, "Exec fail\n", EXIT_FAILURE);
	free(d->path);
	d->path = NULL;
	free_tab(d->cmd);
	d->cmd = NULL;
}
