/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:36:53 by aberramo          #+#    #+#             */
/*   Updated: 2023/10/30 20:24:03 by aberramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	ft_freetab(char **tab)
{
	int	i;

	if (tab)
	{
		i = 0;
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	ft_close_fds(t_data *d)
{
	if (d->in_fd)
		close(d->in_fd);
	if (d->out_fd)
		close(d->out_fd);
	if (d->fds[0])
		close(d->fds[0]);
	if (d->fds[1])
		close(d->fds[1]);
	if (d->fd_tmp)
		close(d->fd_tmp);
}

void	ft_exit(t_data *d, char *msg, int status)
{
	if (status == EXIT_FAILURE)
	{
		ft_putstr_fd("Error\n", 2);
		if (msg && errno != 0)
			perror(msg);
		else if (msg)
			ft_putstr_fd(msg, 2);
	}
	if (d)
	{
		if (d->cmd)
			ft_freetab(d->cmd);
		if (d->paths)
			ft_freetab(d->paths);
		if (d->path)
			free(d->path);
		ft_close_fds(d);
		free(d);
	}
	exit(status);
}
