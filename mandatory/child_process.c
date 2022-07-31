/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:33:55 by aarribas          #+#    #+#             */
/*   Updated: 2022/07/31 10:22:07 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child1_process(t_pipex pipex, char *av[], char *envp[])
{
	dup2(pipex.infile_fd, STDIN_FILENO);
	dup2(pipex.end[1], STDOUT_FILENO);
	close(pipex.end[0]);
	pipex.cmd_args = ft_split(av[2], ' ');
	pipex.cmd = get_command(pipex.cmd_path, pipex.cmd_args[0]);
	if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
	{
		child_free(&pipex);
		err("command not found");
	}
}

void	child2_process(t_pipex pipex, char *av[], char *envp[])
{
	dup2(pipex.outfile_fd, STDOUT_FILENO);
	dup2(pipex.end[0], STDIN_FILENO);
	close(pipex.end[1]);
	pipex.cmd_args = ft_split(av[3], ' ');
	pipex.cmd = get_command(pipex.cmd_path, pipex.cmd_args[0]);
	if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
	{
		child_free(&pipex);
		err("command not found");
	}
}

void	err(char *err)
{
	perror(err);
	exit(1);
}
