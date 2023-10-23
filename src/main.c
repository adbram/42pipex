/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:34:50 by aberramo          #+#    #+#             */
/*   Updated: 2023/10/23 19:48:50 by aberramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static t_data	*ft_init_data(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_exit(data, EXIT_FAILURE);
	data->ac = ac;
	data->av = av;
	return (data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = ft_init_data(ac, av);
	if (data->ac != 5)
		ft_exit(data, EXIT_FAILURE);
	ft_exit(data, EXIT_SUCCESS);
}
