/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:35:41 by aberramo          #+#    #+#             */
/*   Updated: 2023/10/30 20:26:18 by aberramo         ###   ########.fr       */
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
# include <errno.h>

typedef struct s_data
{
	int		ac;
	char	**av;
	char	**env;
	int		fds[2];
	int		fd_tmp;
	pid_t	pid;
	int		in_fd;
	int		out_fd;
	int		nb_cmds;
	int		index;
	char	**cmd;
	char	**paths;
	char	*path;
}	t_data;

void		pipex(t_data *d);
void		exec_cmd(t_data *d);
void		dup_first_cmd(t_data *d);
void		dup_middle_cmds(t_data *d);
void		dup_last_cmd(t_data *d);

void		cmd_path(t_data *d);
void		get_path(t_data *d);
void		get_paths(t_data *d);

void		ft_exit(t_data *d, char *msg, int status);
void		ft_freetab(char **tab);
void		ft_close_fds(t_data *d);

char		**ft_split(t_data *d, char *str, char *charset);
char		*ft_strjoin(t_data *d, char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, int n);
void		ft_putstr_fd(char *str, int fd);

#endif