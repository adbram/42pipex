/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:02:44 by aberramo          #+#    #+#             */
/*   Updated: 2023/10/30 20:39:58 by aberramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	get_paths(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (d->env[i])
	{	
		if (ft_strncmp(d->env[i], "PATH=", 5) == 0)
		{
			d->paths = ft_split(d, d->env[i], "=:");
			// get_path(d);
			//
			int	j;

			j = 0;
			if (d->paths != NULL)
				while (d->paths[j])
				{
					if (j > 0)
					{
						d->path = ft_strjoin(d, d->paths[j], d->cmd[0]);
						if (access(d->path, X_OK) == 0)
							return ;
						free(d->path);
					}
					j++;
				}
			ft_exit(d, "no accessible path\n", EXIT_FAILURE);
			//
			return ;
		}
		i++;
	}
	ft_exit(d, "no PATH in env\n", EXIT_FAILURE);
}

void	get_path(t_data *d)
{
	int	i;

	i = 0;
	while (d->paths[i])
	{
		if (i > 0)
		{
			d->path = ft_strjoin(d, d->paths[i], d->cmd[0]);
			if (access(d->path, X_OK) == 0)
				return ;
			free(d->path);
		}
		i++;
	}
	ft_exit(d, "no accessible path\n", EXIT_FAILURE);
}

void	cmd_path(t_data *d)
{
	get_paths(d);
	ft_freetab(d->paths);
}
