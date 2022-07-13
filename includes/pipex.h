/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:02:40 by aarribas          #+#    #+#             */
/*   Updated: 2022/07/13 20:09:02 by aarribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* write, read, close access, pipe, dup, dup2, execve, fork */
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

/* to get_next_line */
# include "../get_next_line/get_next_line.h"

#endif
