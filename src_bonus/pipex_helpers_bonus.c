/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helpers_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psangunna <psanguna@student.42madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:56:53 by psangunna         #+#    #+#             */
/*   Updated: 2024/08/04 17:56:57 by psangunna        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_redirect_input_output(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("Error redirecting input/output");
		exit(1);
	}
	close(old_fd);
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*ft_get_set_paths(char *env[])
{
	int	i;
	int	j;
	int	r;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		r = ft_strncmp(env[i], "PATH", j);
		if (r == 0)
			return ((env[i] + j + 1));
		i++;
	}
	return (0);
}

char	*ft_get_path(const char *cmd, char *paths_array[])
{
	int		i;
	char	*right_path;
	char	*path_aux;

	i = 0;
	while (paths_array[i])
	{
		path_aux = ft_strjoin(paths_array[i], "/");
		right_path = ft_strjoin(path_aux, cmd);
		free(path_aux);
		if (access(right_path, F_OK | X_OK) == 0)
			return (right_path);
		free(right_path);
		i++;
	}
	return (0);
}

void	ft_read_and_write_lines(int write_fd, char *delimiter)
{
	char	*ret;

	while (1)
	{
		ret = get_next_line(STDIN_FILENO);
		if (ret == NULL)
		{
			perror("get_next_line");
			exit(1);
		}
		if (ft_strncmp(ret, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(ret);
			exit(0);
		}
		ft_putstr_fd(ret, write_fd);
		free(ret);
	}
}
