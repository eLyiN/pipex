/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:02:40 by aarribas          #+#    #+#             */
/*   Updated: 2022/10/04 17:52:12 by aarribas         ###   ########.fr       */
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
	pid_t	child1;
	pid_t	child2;
	int		end[2];
	int		infile_fd;
	int		outfile_fd;
	char	*envp_path;
	char	**cmd_path;
	char	**cmd_args;
	char	*cmd;
}			t_pipex;

// Functions
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
size_t		ft_strlen(const char *str);

// Child Process
void		child1_process(t_pipex *pipex, char *av[], char *envp[]);
void		child2_process(t_pipex *pipex, char *av[], char *envp[]);

// Utils
int			error_msg(char *err);
void		child_free(t_pipex *pipex);
void		parent_free(t_pipex *pipex);
char		*get_command(char **path, char *command);

#endif
