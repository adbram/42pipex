/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:19:24 by aberramo          #+#    #+#             */
/*   Updated: 2023/11/06 18:42:43 by aberramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*ft_strcpy(t_data *d, char *str)
{
	int		i;
	char	*str2;

	str2 = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!str2)
		ft_exit(d, "Strcpy malloc fail\n", EXIT_FAILURE);
	i = 0;
	while (str[i])
	{
		str2[i] = str[i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}
