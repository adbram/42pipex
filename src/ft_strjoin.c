/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 19:09:19 by aberramo          #+#    #+#             */
/*   Updated: 2023/10/28 19:53:39 by aberramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(t_data *d, char *s1, char *s2)
{
	int		join_len;
	char	*joined;
	int		i;
	int		j;

	join_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = (char *)malloc(sizeof(char) * join_len + 1);
	if (!joined)
		ft_exit(d, "malloc strjoin\n", EXIT_FAILURE);
	i = 0;
	j = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	joined[i] = '/';
	i++;
	while (s2[j])
	{
		joined[i + j] = s2[j];
		j++;
	}
	joined[i + j] = '\0';
	return (joined);
}
