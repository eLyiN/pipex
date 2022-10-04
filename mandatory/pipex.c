/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:16:00 by aarribas          #+#    #+#             */
/*   Updated: 2022/10/04 17:52:25 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*path_cmd(char *envp[])
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	init_pipex(t_pipex *pi, char **arg, char **envp)
{
	pipe(pi->end);
	pi->envp_path = path_cmd(envp);
	pi->cmd_path = ft_split(pi->envp_path, ':');
	pi->child1 = fork();
	if (pi->child1 < 0)
		return (perror("Fork: "));
	if (pi->child1 == 0)
		child1_process(pi, arg, envp);
	pi->child2 = fork();
	if (pi->child2 < 0)
		return (perror("Fork: "));
	if (pi->child2 == 0)
		child2_process(pi, arg, envp);
	close(pi->end[0]);
	close(pi->end[1]);
	waitpid(pi->child1, NULL, 0);
	waitpid(pi->child2, NULL, 0);
	parent_free(pi);
}

int	main(int ac, char *av[], char *envp[])
{
	t_pipex	pipex;

	if (ac != 5)
		return (1);
	pipex.infile_fd = open(av[1], O_RDONLY);
	pipex.outfile_fd = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.infile_fd < 0 || pipex.outfile_fd < 0)
		exit(0);
	init_pipex(&pipex, av, envp);
	return (0);
}
