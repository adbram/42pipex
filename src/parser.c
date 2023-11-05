/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 00:39:09 by aberramo          #+#    #+#             */
/*   Updated: 2023/11/03 18:09:58 by aberramo         ###   ########.fr       */
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

char	*get_path(t_data *d)
{
	int		i;
	int		j;
	char	*path;

	if (is_path(d->cmd->tab[0]) == 1)
		return (ft_strcpy(d, d->cmd->tab[0]));
	i = 0;
	while (d->env[i])
	{	
		if (ft_strncmp(d->env[i], "PATH=", 5) == 0)
		{
			d->env_paths = ft_split(d, d->env[i], "=:");
			if (d->env_paths->size > 0)
			{
				j = 0;
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
			}
			free_tab(d->env_paths);
			d->env_paths = NULL;
			return (ft_exit(d, "No accessible path\n", EXIT_FAILURE), NULL);
		}
		i++;
	}
	return (ft_exit(d, "No PATH in env\n", EXIT_FAILURE), NULL);
}
