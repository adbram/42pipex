/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 01:58:09 by aberramo          #+#    #+#             */
/*   Updated: 2023/10/28 04:38:55 by aberramo         ###   ########.fr       */
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

static int	ft_strscount(char *str, char *charset)
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

static int	ft_splitlen(char *str, int j, char *charset)
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

static void	ft_strscpy(t_data *d, t_parsed *p, char *str, char *charset)
{
	int		i;
	int		j;
	int		k;
	int		str_len;

	i = 0;
	j = 0;
	while (i < p->size)
	{
		str_len = ft_splitlen(str, j, charset);
		p->strs[i] = (char *)malloc(sizeof(char) * str_len + 1);
		if (!p->strs[i])
			return (ft_splitclear(p), ft_exit(d, EXIT_FAILURE));
		while (ft_ischarset(str[j], charset))
			j++;
		k = 0;
		while (k < str_len)
		{
			p->strs[i][k] = str[j];
			j++;
			k++;
		}
		p->strs[i][k] = '\0';
		i++;
	}
}

char	**ft_split(t_data *d, char *str, char *charset)
{
	t_parsed	*parsed;

	parsed = (t_parsed *)malloc(sizeof(t_parsed));
	if (!parsed)
		ft_exit(d, EXIT_FAILURE);
	parsed->size = ft_strscount(str, charset);
	parsed->strs = (char **)malloc(sizeof(char *) * parsed->size);
	if (!parsed->strs)
	{
		ft_splitclear(parsed);
		ft_exit(d, EXIT_FAILURE);
	}
	ft_strscpy(d, parsed, str, charset);
	return (parsed->strs);
}
