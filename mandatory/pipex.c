/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:16:00 by aarribas          #+#    #+#             */
/*   Updated: 2022/07/31 10:10:30 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	parent_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
	while (pipex->cmd_path[i])
	{
		free(pipex->cmd_path[i]);
		i++;
	}
	free(pipex->cmd_path);
}

void	child_free(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (pipex->cmd_args[i++])
		free(pipex->cmd_args[i]);
	free(pipex->cmd_path);
}

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

static char	*path_cmd(char *envp[])
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

int	main(int ac, char *av[], char *envp[])
{
	t_pipex	pipex;

	if (ac != 5)
		return (1);
	pipex.infile_fd = open(av[1], O_RDONLY);
	pipex.outfile_fd = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.infile_fd < 0 || pipex.outfile_fd < 0)
		return (1);
	if (pipe(pipex.end) < 0)
		return (1);
	pipex.envp_path = path_cmd(envp);
	pipex.cmd_path = ft_split(pipex.envp_path, ':');
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
	parent_free(&pipex);
	return (0);
}
