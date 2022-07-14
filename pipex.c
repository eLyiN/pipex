/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:16:00 by aarribas          #+#    #+#             */
/*   Updated: 2022/07/15 00:00:54 by aarribas         ###   ########.fr       */
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
	dup2(fd2, STDIN_FILENO);
}
void	pipex(int fd1, int fd2, char *cmd1, char *cmd2)
{
	int		end[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	pipe(end);
	child1 = fork();
	if (child1 < 0)
		return (perror("Fork: "));
	if (child1 == 0)
		child1_process(fd1, cmd1);
	child2 = fork();
	if (child2 < 0)
		return (perror("Fork: "));
	if (child2 == 0)
		child2_process(fd2, cmd2);
	close(end[0]);
	close(end[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}

int	main(int ac, char *av[], char *envp[])
{
	int	fd1;
	int	fd2;

	if (ac != 5)
		return (-1);
	fd1 = open(*av[1], O_RDONLY);
	fd2 = open(*av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0)
		return (-1);
	pipex(fd1, fd2, av, envp);
}
