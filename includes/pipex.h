/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:02:40 by aarribas          #+#    #+#             */
/*   Updated: 2022/07/31 10:18:13 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* write, read, close access, pipe, dup, dup2, execve, fork */
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

/*malloc, free , exit */
# include <stdlib.h>

/* waitpid, wait*/
# include <sys/wait.h>

/*strerror */
# include <string.h>

/* to perror */
# include <stdio.h>

/*t_list*/

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		end[2];
	int		infile_fd;
	int		outfile_fd;
	char	*envp_path;
	char	**cmd_path;
	char	**cmd_args;
	char	*cmd;
}			t_pipex;

/*functions from libft*/
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
size_t		ft_strlen(const char *str);

/*child functions*/
void		child1_process(t_pipex pipex, char *av[], char *envp[]);
void		child2_process(t_pipex pipex, char *av[], char *envp[]);
char		*get_command(char **path, char *command);
void		child_free(t_pipex *pipex);
void		err(char *err);

#endif
