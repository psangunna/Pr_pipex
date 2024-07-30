/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psangunna <psanguna@student.42madrid>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:39:34 by psangunna         #+#    #+#             */
/*   Updated: 2024/07/09 18:39:39 by psangunna        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

static pid_t	ft_create_child(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error creating child process");
		exit(1);
	}
	return (pid);
}

static void	ft_execute_command(const char *cmd, char *env[])
{
	char	**command_array;
	char	*path;

	command_array = ft_split(cmd, ' ');
	if (!command_array)
	{
		ft_putstr_fd("Failed to split command string", 2);
		exit(1);
	}
	path = ft_get_path(command_array[0], env);
	if (path)
	{
		if (execve(path, command_array, env) == -1)
		{
			ft_putstr_fd("pipex: command not found: ", 2);
			ft_putendl_fd(command_array[0], 2);
			ft_free_array(command_array);
			free(path);
			exit(1);
		}
		free(path);
	}
	ft_free_array(command_array);
}

static void	ft_handle_child1(int fd[2], const char *comd1,
		const char *in_file, char *env[])
{
	int	fd_in;

	fd_in = open(in_file, O_RDONLY);
	if (fd_in == -1)
	{
		perror("Error opening input file");
		exit(1);
	}
	close(fd[READ_END]);
	ft_redirect_input_output(fd_in, STDIN_FILENO);
	ft_redirect_input_output(fd[WRITE_END], STDOUT_FILENO);
	ft_execute_command(comd1, env);
}

static void	ft_handle_child2(int fd[2], const char *comd2,
		const char *out_file, char *env[])
{
	int	fd_out;

	close(fd[WRITE_END]);
	ft_redirect_input_output(fd[READ_END], STDIN_FILENO);
	fd_out = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_out == -1)
	{
		perror("Error opening output file");
		exit(1);
	}
	ft_redirect_input_output(fd_out, STDOUT_FILENO);
	ft_execute_command(comd2, env);
}

int	main(int argc, char *argv[], char *env[])
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
	{
		ft_putstr_fd("Use:./pipex inputFile command1 command2 outputFile", 2);
		exit(1);
	}
	if (pipe(fd) == -1)
	{
		perror("Error creating pipe");
		exit(1);
	}
	pid1 = ft_create_child();
	if (pid1 == 0)
		ft_handle_child1(fd, argv[2], argv[1], env);
	pid2 = ft_create_child();
	if (pid2 == 0)
		ft_handle_child2(fd, argv[3], argv[4], env);
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
