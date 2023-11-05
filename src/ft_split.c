/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 01:06:23 by aberramo          #+#    #+#             */
/*   Updated: 2023/11/05 20:55:59 by aberramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	free_split(t_data *d, t_split *s, t_tab *t)
{
	if (s)
		free(s);
	if (t)
		free_tab(t);
	if (d)
		ft_exit(d, "Split malloc fail\n", EXIT_FAILURE);
}

int	is_charset(t_split *s, char c)
{
	int	i;

	i = 0;
	while (s->charset[i] != '\0')
	{
		if (s->charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	split_len(t_split *s)
{
	int	i;

	i = 0;
	while (s->str[i] != '\0')
	{
		while (s->str[i] != '\0' && is_charset(s, s->str[i]))
			i++;
		if (s->str[i] != '\0')
			s->size++;
		while (s->str[i] != '\0' && !is_charset(s, s->str[i]))
			i++;
	}
}

void	split_copy(t_data *d, t_split *s, t_tab *t)
{
	while (s->i < s->size)
	{
		s->k = 0;
		while (s->str[s->j] != '\0' && is_charset(s, s->str[s->j]))
			s->j++;
		while (s->str[s->j] != '\0' && !is_charset(s, s->str[s->j]))
		{
			s->k++;
			s->j++;
		}
		t->tab[s->i] = (char *)malloc(sizeof(char) * s->k + 1);
		if (!t->tab[s->i])
			free_split(d, s, t);
		s->j -= s->k;
		s->k = 0;
		while (s->str[s->j] != '\0' && !is_charset(s, s->str[s->j]))
		{
			t->tab[s->i][s->k] = s->str[s->j];
			s->j++;
			s->k++;
		}
		t->tab[s->i][s->k] = '\0';
		s->i++;
	}
	t->tab[s->i] = NULL;
}

t_tab	*ft_split(t_data *d, char *str, char *charset)
{
	t_split	*s;
	t_tab	*t;

	s = (t_split *)malloc(sizeof(t_split));
	if (!s)
		free_split(d, s, NULL);
	s->str = str;
	s->charset = charset;
	s->i = 0;
	s->j = 0;
	s->size = 0;
	t = (t_tab *)malloc(sizeof(t_tab));
	if (!t)
		free_split(d, s, t);
	split_len(s);
	t->size = s->size;
	t->tab = (char **)malloc(sizeof(char *) * (s->size + 1));
	if (!t->tab)
		free_split(d, s, t);
	split_copy(d, s, t);
	free(s);
	return (t);
}
