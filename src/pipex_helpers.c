/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psangunna <psanguna@student.42madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:39:57 by psangunna         #+#    #+#             */
/*   Updated: 2024/07/09 18:40:03 by psangunna        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

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

static char	*ft_get_set_paths(char *env[])
{
	int	i;
	int	j;
	int	r;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
		{
			j++;
		}
		r = ft_strncmp(env[i], "PATH", j);
		if (r == 0)
			return ((env[i] + j + 1));
		i++;
	}
	return (0);
}

static char	*ft_get_right_path(const char *path, const char *cmd)
{
	char	*path_aux;
	char	*right_path;

	path_aux = ft_strjoin(path, "/");
	if (path_aux)
	{
		right_path = ft_strjoin(path_aux, cmd);
		free(path_aux);
		if (right_path)
		{
			if (access(right_path, F_OK | X_OK) == 0)
			{
				return (right_path);
			}
			free(right_path);
		}
	}
	return (0);
}

/*Funciones llamadas dentro de la función execute_command */
char	*ft_get_path(const char *cmd, char *env[])
{
	int		i;
	char	*right_path;
	char	*paths;
	char	**paths_array;

	paths = ft_get_set_paths(env);
	paths_array = ft_split(paths, ':');
	if (!paths_array)
	{
		ft_putstr_fd("Failed to split PATH variable", 2);
		return (0);
	}
	i = 0;
	while (paths_array[i])
	{
		right_path = ft_get_right_path(paths_array[i], cmd);
		if (right_path)
		{
			ft_free_array(paths_array);
			return (right_path);
		}
		i++;
	}
	ft_free_array(paths_array);
	return (0);
}
