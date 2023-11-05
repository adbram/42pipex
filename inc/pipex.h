/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberramo <aberramo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:35:41 by aberramo          #+#    #+#             */
/*   Updated: 2023/11/03 23:24:07 by aberramo         ###   ########.fr       */
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

typedef struct s_tab
{
	int		size;
	char	**tab;
}	t_tab;

typedef struct s_split
{
	int		size;
	t_tab	*t;
	char	*str;
	char	*charset;
	int		i;
	int		j;
	int		k;
}	t_split;

typedef struct s_data
{
	int		ac;
	char	**av;
	char	**env;
	int		fds[2];
	int		fd_tmp;
	int		nb_cmds;
	int		i;
	pid_t	*pids;
	int		in_fd;
	int		out_fd;
	char	*in_file;
	char	*out_file;
	char	*path;
	t_tab	*env_paths;
	t_tab	*cmd;
}	t_data;

t_data	*init_data(int ac, char **av, char **env);

void	dup_first_cmd(t_data *d);
void	dup_middle_cmd(t_data *d);
void	dup_last_cmd(t_data *d);
void	exec_cmd(t_data *d);

void	free_tab(t_tab *t);
void	close_fds(t_data *d);
void	ft_exit(t_data *d, char *msg, int status);

void	free_split(t_data *d, t_split *s);
int		is_charset(t_split *s, char c);
void	split_len(t_split *s);
void	split_copy(t_data *d, t_split *s);
t_tab	*ft_split(t_data *d, char *str, char *charset);

void	ft_putstr_fd(char *str, int fd);
int		ft_strncmp(const char *s1, const char *s2, int n);
int		ft_strlen(char *str);
char	*ft_strcpy(t_data *d, char *str);
char	*ft_strjoin(t_data *d, char *s1, char *s2, char del);

int		is_path(char *str);
char	*get_path(t_data *d);

void	pipex(t_data *d);

#endif
