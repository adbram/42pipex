/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 00:39:09 by aberramo          #+#    #+#             */
/*   Updated: 2023/11/05 21:15:27 by aberramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	is_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	get_env_paths(t_data *d)
{
	int		i;

	i = 0;
	while (d->env[i])
	{	
		if (ft_strncmp(d->env[i], "PATH=", 5) == 0)
		{
			d->env_paths = ft_split(d, d->env[i], "=:");
			if (d->env_paths->size > 1)
				return ;
			free_tab(d->env_paths);
			d->env_paths = NULL;
			ft_exit(d, "PATH element in env empty\n", EXIT_FAILURE);
		}
		i++;
	}
	ft_exit(d, "No PATH element in env\n", EXIT_FAILURE);
}

char	*get_path(t_data *d)
{
	int		j;
	char	*path;

	if (d->cmd->size < 1)
		ft_exit(d, "Blank command\n", EXIT_FAILURE);
	if (is_path(d->cmd->tab[0]) == 1)
		return (ft_strcpy(d, d->cmd->tab[0]));
	get_env_paths(d);
	j = 1;
	while (j < d->env_paths->size)
	{
		if (j > 0)
		{
			path = ft_strjoin(d, d->env_paths->tab[j], d->cmd->tab[0], '/');
			if (access(path, X_OK) == 0)
			{
				free_tab(d->env_paths);
				d->env_paths = NULL;
				return (path);
			}
			free(path);
		}
		j++;
	}
	return (ft_exit(d, "No path\n", EXIT_FAILURE), NULL);
}
