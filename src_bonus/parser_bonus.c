/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 00:39:09 by aberramo          #+#    #+#             */
/*   Updated: 2023/11/16 19:06:13 by aberramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

char	*is_path(t_data *d, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
		{
			if (access(str, X_OK) == 0)
				return (ft_strcpy(d, str));
			return (ft_exit(d, "Command fail", EXIT_FAILURE), NULL);
		}
		i++;
	}
	return (NULL);
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
			ft_exit(d, "PATH element in env empty", EXIT_FAILURE);
		}
		i++;
	}
	ft_exit(d, "No PATH element in env", EXIT_FAILURE);
}

char	*get_path(t_data *d)
{
	int		j;
	char	*path;

	path = is_path(d, d->cmd->tab[0]);
	if (path != NULL)
		return (path);
	get_env_paths(d);
	j = 0;
	while (j++ < d->env_paths->size)
	{
		if (d->env_paths->tab[j] == NULL)
			break ;
		path = ft_strjoin(d, d->env_paths->tab[j], d->cmd->tab[0], '/');
		if (access(path, X_OK) == 0)
		{
			free_tab(d->env_paths);
			d->env_paths = NULL;
			free(d->cmd->tab[0]);
			d->cmd->tab[0] = ft_strcpy(d, path);
			return (path);
		}
		free(path);
	}
	return (ft_exit(d, "Command fail", EXIT_FAILURE), NULL);
}
