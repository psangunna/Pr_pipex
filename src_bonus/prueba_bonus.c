#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1

void	ft_handle_input(int i, const char *in_file, int pipe_fd[2], int prev_pipe_fd[2]);
void	ft_handle_output(int i, int num_commands, const char *out_file, int pipe_fd[2]);
void	ft_redirect_input_output(int old_fd, int new_fd);
void	ft_execute_command(const char *command, char *env[]);
//void	ft_create_pipes_and_childs(int num_commands, pid_t pids[], char *argv[], char *env[]);
void	ft_create_pipes_and_childs(int num_commands, char *argv[], char *env[], int prev_pipe_fd[2])

void	ft_create_pipes_and_childs(int num_commands, char *argv[], char *env[], int prev_pipe_fd[2])
{
	int		pipe_fd[2];
	pid_t	pid;
	int		i;

	i = 0;
	while ( i < num_commands)
	{
		if (i < num_commands - 1)
		{
			if (pipe(pipe_fd) == -1)
				exit(1);
			prev_pipe_fd[READ_END] = pipe_fd[READ_END];
			prev_pipe_fd[WRITE_END] = pipe_fd[WRITE_END];
		}
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
			ft_handle_input(i, argv[1], pipe_fd, prev_pipe_fd);
			ft_handle_output(i, num_commands, argv[argc - 1], pipe_fd);
			//execute_command(argv[i + 2], env);
		}
	}
}

int	main(int argc, char *argv[], char *env[])
{
	int		i;
	int		num_commands;
	int		prev_pipe_fd[2];

	if (argc != 5)
	{
		ft_putstr_fd("Use:./pipex inputFile command1 command2 outputFile", 2);
		exit(1);
	}
	num_commands = argc - 3;
	ft_create_pipes_and_childs(num_commands, argv, env, prev_pipe_fd);
	    // Cerrar descriptores de archivo en el padre después de crear todos los hijos
    close(prev_pipe_fd[READ_END]);
    close(prev_pipe_fd[WRITE_END]);
	i = 0;
	while (i < num_commands)
	{
		wait(NULL);
		i++;
	}
	return (0);
}

void	ft_redirect_input_output(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("Error redirecting input/output");
		exit(1);
	}
	close(old_fd);
}

void ft_handle_input(int i, const char *in_file, int pipe_fd[2], int prev_pipe_fd[2])
{
    int fd_in;

    if (i == 0)
    {
        fd_in = open(in_file, O_RDONLY);
        if (fd_in == -1)
        {
            perror("Error opening input file");
            exit(1);
        }
        ft_redirect_input_output(fd_in, STDIN_FILENO);
    }
    else
    {
        close(prev_pipe_fd[WRITE_END]);
        ft_redirect_input_output(prev_pipe_fd[READ_END], STDIN_FILENO);
    }
}

void ft_handle_output(int i, int num_commands, const char *out_file, int pipe_fd[2])
{
    int fd_out;

    if (i == num_commands - 1)
    {
        fd_out = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fd_out == -1)
        {
            perror("Error opening output file");
            exit(1);
        }
        ft_redirect_input_output(fd_out, STDOUT_FILENO);
    }
    else
    {
        close(pipe_fd[READ_END]);
		ft_redirect_input_output(pipe_fd[WRITE_END], STDOUT_FILENO);
    }
}
