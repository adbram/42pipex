/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 23:31:07 by aberramo          #+#    #+#             */
/*   Updated: 2023/11/05 19:02:50 by aberramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	free_tab(t_tab *t)
{
	int	i;

	if (t != NULL)
	{
		if (t->tab != NULL)
		{
			i = 0;
			while (i < t->size)
			{
				free(t->tab[i]);
				i++;
			}
			free(t->tab);
		}
		free(t);
	}
}

void	close_fds(t_data *d)
{
	if (d->fds[0] > 0)
		close(d->fds[0]);
	if (d->fds[1] > 0)
		close(d->fds[1]);
	if (d->in_fd > 0)
		close(d->in_fd);
	if (d->out_fd > 0)
		close(d->out_fd);
	if (d->fd_tmp > 0)
		close(d->out_fd);
}

void	ft_exit(t_data *d, char *msg, int status)
{
	if (status == EXIT_FAILURE)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		if (msg)
			ft_putstr_fd(msg, STDERR_FILENO);
	}
	if (d != NULL)
	{
		close_fds(d);
		if (d->path != NULL)
			free(d->path);
		if (d->cmd != NULL)
			free_tab(d->cmd);
		if (d->env_paths != NULL)
			free_tab(d->env_paths);
		if (d->pids != NULL)
			free(d->pids);
		free(d);
	}
	exit(status);
}
