/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psangunna <psanguna@student.42madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:53:10 by psangunna         #+#    #+#             */
/*   Updated: 2024/08/05 13:35:16 by pamela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_handle_here_doc(char *delimiter)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		close(fd[READ_END]);
		ft_read_and_write_lines(fd[WRITE_END], delimiter);
	}
	else
	{
		close(fd[WRITE_END]);
		ft_redirect_input_output(fd[READ_END], STDIN_FILENO);
		wait(NULL);
	}
}

static void	ft_managment_files(int argc, char *argv[], int *fd_out, int ind)
{
	int	fd_in;

	if (ind == 3)
	{
		*fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (*fd_out == -1)
			exit(1);
		ft_handle_here_doc(argv[2]);
	}
	else
	{
		fd_in = open(argv[1], O_RDONLY);
		if (fd_in == -1)
		{
			perror("Error opening input file");
			exit(1);
		}
		*fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (*fd_out == -1)
			exit(1);
		ft_redirect_input_output(fd_in, STDIN_FILENO);
	}
}

static void	ft_execute_command(const char *cmd, char *env[])
{
	char	**command_array;
	char	*paths;
	char	*right_path;
	char	**paths_array;

	command_array = ft_split(cmd, ' ');
	paths = ft_get_set_paths(env);
	paths_array = ft_split(paths, ':');
	right_path = ft_get_path(command_array[0], paths_array);
	ft_free_array(paths_array);
	if (execve(right_path, command_array, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(command_array[0], 2);
		ft_free_array(command_array);
		free(right_path);
		exit(1);
	}
}

static void	ft_crear_pipes(int i, int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid;

	while (i < argc - 2)
	{
		if (pipe(fd) == -1)
			exit(1);
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
			close(fd[READ_END]);
			ft_redirect_input_output(fd[WRITE_END], STDOUT_FILENO);
			ft_execute_command(argv[i], env);
		}
		else
		{
			close(fd[WRITE_END]);
			ft_redirect_input_output(fd[READ_END], STDIN_FILENO);
			wait(NULL);
			i++;
		}
	}
}

int	main(int argc, char *argv[], char *env[])
{
	int	num_ind;
	int	fd_out;

	if (argc < 5)
	{
		ft_putstr_fd("Use:./pipex infile comnd1 comd2 .. comdn outfile\n", 1);
		exit(1);
	}
	num_ind = 2;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
		{
			ft_putstr_fd("Use:./pipex here\\_doc LIMITADOR comdo comd1 \
					outfile\n", 1);
			exit(1);
		}
		num_ind = 3;
	}
	ft_managment_files(argc, argv, &fd_out, num_ind);
	ft_crear_pipes(num_ind, argc, argv, env);
	ft_redirect_input_output(fd_out, STDOUT_FILENO);
	ft_execute_command(argv[argc - 2], env);
	return (0);
}
