/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psangunna <psanguna@student.42madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:56:11 by psangunna         #+#    #+#             */
/*   Updated: 2024/08/04 17:56:18 by psangunna        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
void	ft_read_and_write_lines(int write_fd, char *delimiter);
#endif
