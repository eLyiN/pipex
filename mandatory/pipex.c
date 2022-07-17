/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:16:00 by aarribas          #+#    #+#             */
/*   Updated: 2022/07/17 09:48:31 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_command(char **path, char *command)
{
	char	*tmp;
	char	*cmd;

	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		cmd = ft_strjoin(tmp, command);
		free(tmp);
		if (access(cmd, 0) == 0)
			return (cmd);
		free(cmd);
		path++;
	}
	return (NULL);
}

void	child1_process(t_pipex pipex, char *av[], char *envp[])
{
	dup2(pipex.infile_fd, STDIN_FILENO);
	if (pipex.infile_fd < 0)
	{
		perror("Dup2 error infile");
		return ;
	}
	dup2(pipex.end[1], STDOUT_FILENO);
	close(pipex.end[0]);
	pipex.cmd_args = ft_split(av[2], ' ');
	pipex.cmd = get_command(pipex.cmd_path, pipex.cmd_args[0]);
	if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
	{
		free(pipex.cmd);
		free(pipex.cmd_path);
		exit(0);
	}
}

void	child2_process(t_pipex pipex, char *av[], char *envp[])
{
	dup2(pipex.outfile_fd, STDOUT_FILENO);
	if (pipex.outfile_fd < 0)
	{
		perror("Dup2 error outfile");
		return ;
	}
	dup2(pipex.end[0], STDIN_FILENO);
	close(pipex.end[1]);
	pipex.cmd_args = ft_split(av[3], ' ');
	pipex.cmd = get_command(pipex.cmd_path, pipex.cmd_args[0]);
	if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
	{
		free(pipex.cmd);
		free(pipex.cmd_path);
		exit(0);
	}
}

static char	*path_cmd(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

void	parsing_arg(t_pipex pipex, char **envp)
{
	pipex.envp_path = path_cmd(envp);
	pipex.cmd_path = ft_split(pipex.envp_path, ':');
}

int	main(int ac, char *av[], char *envp[])
{
	t_pipex	pipex;

	if (ac != 5)
		return (-1);
	pipex.infile_fd = open(av[1], O_RDONLY);
	pipex.outfile_fd = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.infile_fd < 0 || pipex.outfile_fd < 0)
		return (-1);
	if (pipe(pipex.end) < 0)
		return (-1);
	parsing_arg(pipex, envp);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		child1_process(pipex, av, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		child2_process(pipex, av, envp);
	close(pipex.end[0]);
	close(pipex.end[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
}
