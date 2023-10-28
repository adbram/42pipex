/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:35:41 by aberramo          #+#    #+#             */
/*   Updated: 2023/10/28 04:39:08 by aberramo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_data
{
	int		ac;
	char	**av;
	char	**env;
	int		fds[2];
	pid_t	pid;
	int		in_fd;
	int		out_fd;
	int		nb_cmds;
	int		index;
}	t_data;

typedef struct s_parsed
{
	char	**strs;
	int		 size;
}	t_parsed;

void		ft_exit(t_data *d, int status);
void		ft_putstr_fd(char *str, int fd);
char		**ft_split(t_data *d, char *str, char *charset);

void		pipex(t_data *d);

#endif