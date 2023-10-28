/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:34:50 by aberramo          #+#    #+#             */
/*   Updated: 2023/10/28 03:59:43 by aberramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static t_data	*init_data(int ac, char **av, char **env)
{
	t_data	*d;

	d = (t_data *)malloc(sizeof(t_data));
	if (!d)
		ft_exit(d, EXIT_FAILURE);
	d->ac = ac;
	d->av = av;
	d->env = env;
	d->nb_cmds = ac - 3;
	d->in_fd = open(av[1], O_RDONLY);
	d->out_fd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 644);
	if (d->in_fd < 0 || d->out_fd < 0)
		ft_exit(d, EXIT_FAILURE);
	return (d);
}

int	main(int ac, char **av, char **env)
{
	t_data	*d;

	d = init_data(ac, av, env);
	if (d->ac != 5)
		ft_exit(d, EXIT_FAILURE);
	pipex(d);
	ft_exit(d, EXIT_SUCCESS);
}
