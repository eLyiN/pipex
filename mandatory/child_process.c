/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:33:55 by aarribas          #+#    #+#             */
/*   Updated: 2022/10/04 17:48:19 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child1_process(t_pipex *pipex, char *av[], char *envp[])
{
	if (dup2(pipex->infile_fd, STDIN_FILENO) < 0)
		return (perror("Dup2: "));
	if (dup2(pipex->end[1], STDOUT_FILENO) < 0)
		return (perror("Dup2: "));
	close(pipex->end[0]);
	close(pipex->infile_fd);
	pipex->cmd_args = ft_split(av[2], ' ');
	pipex->cmd = get_command(pipex->cmd_path, pipex->cmd_args[0]);
	if (!pipex->cmd)
	{
		child_free(pipex);
		error_msg("Command not found.\n");
		exit(1);
	}
	if (execve(pipex->cmd, pipex->cmd_args, envp) == -1)
		return (perror("Execve: "));
}

void	child2_process(t_pipex *pipex, char *av[], char *envp[])
{
	if (dup2(pipex->outfile_fd, STDOUT_FILENO) < 0)
		return (perror("Dup2: "));
	if (dup2(pipex->end[0], STDIN_FILENO) < 0)
		return (perror("Dup2: "));
	close(pipex->end[1]);
	close(pipex->outfile_fd);
	pipex->cmd_args = ft_split(av[3], ' ');
	pipex->cmd = get_command(pipex->cmd_path, pipex->cmd_args[0]);
	if (!pipex->cmd)
	{
		child_free(pipex);
		error_msg("Command not found.\n");
		exit(1);
	}
	if (execve(pipex->cmd, pipex->cmd_args, envp) == -1)
		return (perror("Execve: "));
}
