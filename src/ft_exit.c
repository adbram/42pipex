/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 23:31:07 by aberramo          #+#    #+#             */
/*   Updated: 2023/11/05 20:31:39 by aberramo         ###   ########.fr       */
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

int	ft_close(int *fd)
{
	int	ret;

	ret = 0;
	if (*fd > 0)
	{
		ret = close(*fd);
		*fd = -1;
	}
	return (ret);
}

void	close_fds(t_data *d)
{
	ft_close(&d->fds[0]);
	ft_close(&d->fds[1]);
	ft_close(&d->in_fd);
	ft_close(&d->out_fd);
	ft_close(&d->out_fd);
}

void	ft_exit(t_data *d, char *msg, int status)
{
	if (status == EXIT_FAILURE)
	{
		if (errno != 0)
			perror(msg);
		else
		{
			ft_putstr_fd("Error\n", STDERR_FILENO);
			if (msg)
				ft_putstr_fd(msg, STDERR_FILENO);
		}
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
