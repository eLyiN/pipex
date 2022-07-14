/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:16:00 by aarribas          #+#    #+#             */
/*   Updated: 2022/07/14 09:18:26 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	child_process(int fd1, char *cmd1)
{
	dup2(fd1, STDIN_FILENO);
	if (fd1 < 0)
	{
		perror("Dup2 error");
		return (1);
	}
}
int	parent_process(int fd2, char *cmd2)
{
	dup2(fd1, STDIN_FILENO)
}
void	pipex(int fd1, int fd2, char *cmd1, char *cmd2)
{
	int		end[2];
	pid_t	parent;

	pipe(end);
	parent = fork();
	if (parent < 0)
		return (perror("Fork: "));
	if (parent == 0) //we are in child process
		child_process(fd1, cmd1);
	else //we are in parent process
		parent_process(fd2, cmd2);
}

int	main(int ac, char *av[])
{
	if (ac != 5)
		return (1);
}
