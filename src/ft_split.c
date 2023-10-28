/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 01:58:09 by aberramo          #+#    #+#             */
/*   Updated: 2023/10/28 18:32:06 by aberramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	ft_ischarset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strscount(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && ft_ischarset(str[i], charset))
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && !ft_ischarset(str[i], charset))
			i++;
	}
	return (count);
}

int	ft_splitlen(char *str, int j, char *charset)
{
	int	len;
	int	i;

	len = 0;
	i = j;
	while (str[i] != '\0' && ft_ischarset(str[i], charset))
		i++;
	while (str[i] != '\0' && !ft_ischarset(str[i], charset))
	{
		len++;
		i++;
	}
	return (len);
}

void	ft_strscpy(t_data *d, char **strs, char *str, int strs_size, char *charset)
{
	int		i;
	int		j;
	int		k;
	int		str_len;

	i = 0;
	j = 0;
	while (i < strs_size)
	{
		str_len = ft_splitlen(str, j, charset);
		strs[i] = (char *)malloc(sizeof(char) * str_len + 1);
		if (!strs[i])
		{
			ft_freetab(strs);
			ft_exit(d, "in strcpy\n", EXIT_FAILURE);
		}
		while (ft_ischarset(str[j], charset))
			j++;
		k = 0;
		while (k < str_len)
		{
			strs[i][k] = str[j];
			j++;
			k++;
		}
		strs[i][k] = '\0';
		i++;
	}
}

char	**ft_split(t_data *d, char *str, char *charset)
{
	int		strs_size;
	char	**strs;

	strs_size = ft_strscount(str, charset);
	strs = (char **)malloc(sizeof(char *) * strs_size + sizeof(int));
	if (!strs)
		ft_exit(d, "split malloc\n", EXIT_FAILURE);
	ft_strscpy(d, strs, str, strs_size, charset);
	strs[strs_size] = 0;
	return (strs);
}
