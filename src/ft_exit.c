/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:36:53 by aberramo          #+#    #+#             */
/*   Updated: 2023/10/28 18:31:14 by aberramo         ###   ########.fr       */
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

void	ft_exit(t_data *d, char *msg, int status)
{
	if (status == EXIT_FAILURE)
	{
		ft_putstr_fd("Error\n", 2);
		if (msg)
			ft_putstr_fd(msg, 2);
	}
	if (d->in_fd)
		close(d->in_fd);
	if (d->out_fd)
		close(d->out_fd);
	if (d)
		free(d);
	exit(status);
}
