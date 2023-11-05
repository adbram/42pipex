/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 23:27:52 by aberramo          #+#    #+#             */
/*   Updated: 2023/11/05 18:51:45 by aberramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

t_data	*init_data(int ac, char **av, char **env)
{
	t_data	*d;

	d = (t_data *)malloc(sizeof(t_data));
	if (!d)
		ft_exit(d, "Init malloc fail\n", EXIT_FAILURE);
	d->ac = ac;
	d->av = av;
	d->env = env;
	d->fds[0] = -1;
	d->fds[1] = -1;
	d->nb_cmds = ac - 3;
	d->in_fd = -1;
	d->out_fd = -1;
	d->fd_tmp = -1;
	d->in_file = av[1];
	d->out_file = av[ac - 1];
	d->cmd = NULL;
	d->path = NULL;
	d->env_paths = NULL;
	d->i = 0;
	d->pids = (pid_t *)malloc(sizeof(pid_t) * d->nb_cmds);
	if (!d->pids)
		ft_exit(d, "Init malloc fail\n", EXIT_FAILURE);
	return (d);
}

int	main(int ac, char **av, char **env)
{
	t_data	*d;

	if (ac != 5)
		ft_exit(NULL, "Ac != 5\n", EXIT_FAILURE);
	d = init_data(ac, av, env);
	pipex(d);
	ft_exit(d, NULL, EXIT_SUCCESS);
}
