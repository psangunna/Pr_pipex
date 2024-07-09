/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psangunna <psanguna@student.42madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:28:42 by psangunna         #+#    #+#             */
/*   Updated: 2024/07/09 17:28:58 by psangunna        ###   ########.fr       */
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
char	*ft_get_path(const char *cmd, char *env[]);
void	ft_redirect_input_output(int old_fd, int new_fd);
#endif
