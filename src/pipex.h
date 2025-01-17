/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psangunna <psanguna@student.42madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:32:40 by psangunna         #+#    #+#             */
/*   Updated: 2024/08/01 13:32:45 by psangunna        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

# define READ_END 0
# define WRITE_END 1

void	ft_free_array(char **array);
char	*ft_get_path(const char *cmd, char *paths_array[]);
char	*ft_get_set_paths(char *env[]);
void	ft_redirect_input_output(int old_fd, int new_fd);
#endif
