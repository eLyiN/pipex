/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:33:55 by aarribas          #+#    #+#             */
/*   Updated: 2022/07/18 09:45:16 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
		child_free(&pipex);
		perror("Execve fail on child1");
		exit(1);
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
		child_free(&pipex);
		perror("Execve fail on child2");
		exit(1);
	}
}
