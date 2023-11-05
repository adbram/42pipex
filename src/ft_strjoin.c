/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:43:23 by aberramo          #+#    #+#             */
/*   Updated: 2023/11/03 15:13:28 by aberramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*ft_strjoin(t_data *d, char *s1, char *s2, char del)
{
	int		join_len;
	char	*joined;
	int		i;
	int		j;

	join_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = (char *)malloc(sizeof(char) * join_len + 1);
	if (!joined)
		ft_exit(d, "Malloc fail strjoin\n", EXIT_FAILURE);
	i = 0;
	j = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	joined[i] = del;
	i++;
	while (s2[j])
	{
		joined[i + j] = s2[j];
		j++;
	}
	joined[i + j] = '\0';
	return (joined);
}
