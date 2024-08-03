# Pipex
__Pipex__ is a pipe handling project in C. This README provides details on the implementation, usage, compilation instructions, code and logic used for the project.
# Index
- [Description](#description)
	- [Allowed functions](#allow)
	- [Project files](#pr_files)
  	- [Compilation](#compilation)
	- [Usage](#usage)
	- [Notes](#notes)
 - [Logic and Implementation](#logic)
	- [High-Level Overview](#h_level)
	- [Detail steps](#detail)
	- [Pseudo Code](#pseudo)
	- [Sequence Diagram of get_next_line Function and Subfunctions](#diagram)
	- [Code explanation](#code)
- [Bonus](#bonus)
	- [Bonus Requirements](#b_req)
	- [Bonus files](#b_files)
	- [Compilation for Bonus Part](#b_compilation)
	- [Usage for Bonus Part](#b_usage)
- [Acknowledgements](#ack)
### _Description_ <a name="description"></a>
This program replicates the behavior of the shell construction *< infile cmd1 | cmd2 > outfile*. The program takes four arguments: *infile*, *command1*, *command2*, and *outfile*. 
  
The program should perform the same operation as the following shell command:  
``
$> < infile command1 | command2 > outfile
``
#### Allowed Functions <a name="allow"></a>
* **open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid**
* **ft_printf**
* **libft**
#### Project Files <a name="pr_files"></a>
* **Makefile**
* **Header files (*.h)**: pipex.h
* **Source code files (*.c)**: pipex.c, pipex_helpers.c
#### Compilation <a name="compilation"></a>
To compile the project, use the included **Makefile**. The available targets are:
* **make**: Compiles the program.
* **make clean**: Removes object files.
* **make fclean**: Removes object files and the executable.
* **make re**: Cleans and recompiles the program.
#### Usage <a name="usage"></a>
The program should be executed as follows:  
`` ./pipex infile command1 command2 ``
* **infile** and **outfile** are file names.
* **command1** and **command2** are shell commands with their respective parameters.
#### Notes <a name="notes"></a>
* The **Makefile** that compiles the source files. It should not relink.
* Handle errors meticulously to avoid unexpected program exits (segmentation fault, bus error, double free, etc.).
* The program must not have memory leaks.
* In case of doubt, handle errors as the shell command would: *<infile cmd1 | cmd2 > outfile*
### _Logic and Implementation_ <a name="logic"></a>
#### High-Level Overview <a name="h_level"></a>
This **Pipex** project simulates a shell pipeline. It reads from an inout file, executes the first command, pipes its output to the second command, and writes the final output to an output file. The project involves process creation, piping, file redirection, and command execution.  

The implementation of this project follows a sequential code approach. Each step in the process is executed in a linear order:

* **File Handling**: Open the input and output files in a defined sequence.
* **Pipe Creation**: Create pipes before forking processes.
* **Process Forking**: Fork processes to execute commands sequentially.
* **Command Execution**: Execute commands in a specific order, ensuring each command completes before moving to the next.
* **Resource Cleanup**: Close files and pipes and wait for processes to finish in a controlled sequence.
#### Detailed Steps <a name="detail"></a>
1. **To check the number of arguments**.  
2. **To create a pipe**: Set up a pipe to connect the two processes.  
3. **First child process**:  
* Open the input file.
* Redirect input and output.
* Execute the first command.  
4. **Second child process**:  
* Redirect input from the pipe.
* Open the output file.
* Redirect output.
* Execute the second command.  
5. **Parent process**:  
* Wait for both child processes to finish.
* Close the pipe ends.  
#### Pseudo Code <a name="pseudo"></a>
* **Main function**  

    	Main function (argc, argv, env)
		    If argc != 5
		        Print usage error
		        Exit with error
		
		    Create pipe(fd)
		    If pipe creation fails
		        Print error
		        Exit with error
		
		    Create first child process (pid1)
		    If pid1 == 0 (child process)
		        Handle first process
		        Exit
		    Close write end of pipe in parent
		    Wait for first child to finish
		
		    Create second child process (pid2)
		    If pid2 == 0 (child process)
		        Handle second process
		        Exit
		    Close read end of pipe in parent
		    Wait for second child to finish
		    Return 0     
  * **Processes functions and Command function**  
	
		Handle_first_process function(fd, command1, infile, env)
		    Open infile for reading
		    If file open fails
		        Print error
		        Exit with error
		    Close read end of pipe
		    Redirect infile to STDIN
		    Redirect pipe write end to STDOUT
		    Execute command1

		Handle_second_process function(fd, command2, outfile, env)
		    Close write end of pipe
		    Redirect pipe read end to STDIN
		    Open outfile for writing
		    If file open fails
		        Print error
		        Exit with error
		    Redirect outfile to STDOUT
		    Execute command2

		Execute_command function(cmd, env)
		    Split cmd into command_array
		    Get paths from env
		    Split paths into paths_array
		    Find right_path in paths_array
		    If execve fails
		        Print command not found error
		        Free allocated memory
		        Exit with error

#### Sequence Diagram of get_next_line Function and Subfunctions <a name="diagram"></a>  
```mermaid
sequenceDiagram
    participant Main as Main Function
    participant Process1 as First Process
    participant Process2 as Second Process
    participant File as File Handling
    participant Execute as Execute Command
    participant Pipe as Pipe Management

    Main->>Pipe: Create pipe
    Pipe-->>Main: Pipe created

    Main->>Process1: Fork first process
    Process1->>File: Open input file
    File-->>Process1: Input file opened
    Process1->>Pipe: Close read end of pipe
    Process1->>Pipe: Redirect stdin to input file
    Process1->>Pipe: Redirect stdout to pipe
    Process1->>Execute: Execute command1
    Execute->>Execute: Split command into arguments
    Execute->>Execute: Get paths from environment
    Execute->>Execute: Split paths into array
    Execute->>Execute: Find right path for command
    Execute->>Execute: Execute command with execve
    Execute-->>Process1: Command executed
    Process1-->>Main: Exit first process

    Main->>Pipe: Close write end of pipe
    Main->>Process2: Fork second process
    Process2->>Pipe: Redirect stdin to pipe
    Process2->>File: Open output file
    File-->>Process2: Output file opened
    Process2->>Pipe: Close write end of pipe
    Process2->>Pipe: Redirect stdout to output file
    Process2->>Execute: Execute command2
    Execute->>Execute: Split command into arguments
    Execute->>Execute: Get paths from environment
    Execute->>Execute: Split paths into array
    Execute->>Execute: Find right path for command
    Execute->>Execute: Execute command with execve
    Execute-->>Process2: Command executed
    Process2-->>Main: Exit second process

    Main->>Main: Wait for both processes to finish
    Main-->>Main: Cleanup and exit
````
#### Code Explanation <a name="code"></a>
* **ft_execute_command**: Splits the command string into an array, finds the correct path for the command, and executes it using **execve**. If execve fails, it shows an error and exits.
* **ft_handle_first_process**: Handles the first child process by opening the input file, redirecting input and output, and executing the first command.
* **ft_handle_second_process**: Handles the second child process by redirecting input from the pipe, opening the output file, redirecting output, and executing the second command.
* **main**: The main function manages the entire process by creating the pipe, forking the child processes, and waiting for them to finish.  
  
*Additional Functions*
* **ft_get_set_paths**: Retrieves the value of the **PATH** environment variable from an environment array.  
* **ft_get_path**: Finds the correct path for a given command by searching through the directories in **PATH**.  
* **ft_redirect_input_output**: Redirect file descriptors.  
* **ft_free_array**: Frees all strings in an array and then the array itself.   
* **ft_create_process**: Creates a child process using f**fork**. If **fork** fails, it prints an error and exits.  

### *Acknowledgements* <a name="ack"></a>
### _Bonus Part_ <a name="bonus"></a>  
To enhance the functionality of this project with these additional features:
#### Bonus Requirements <a name="b_req"></a>
* **Multiple pipes**:  
``$ ./pipex infile command1 command2 command3 ... commandN outfile``  
Should behave as:  
``$ < infile command1 | command2 | command3 ... | commandN > outfile``

* **"here document"**:  
``$ ./pipex here_doc LIMITER command command1 file``  
Should behave as:  
``command << LIMITER | command1 >> file``
#### Bonus Files <a name="b_files"></a>
In addition to the mandatory files, you need to deliver the following files for the bonus part:
* **Header bonus file (*_bonus.h)**: pipex_bonus.h
* **Source code bonus file (*_bonus.c)**: pipex_bonus.c, pipex_helpers_bonus.c
#### Compilation for Bonus Part<a name="b_compilation"></a>
To compile the bonus part, use the included **Makefile**. The available targets are:
* **make bonus**: Compiles the bonus part.
* **make clean**: Removes object files.
* **make fclean**: Removes object files and the executable.
* **make rebonus**: Cleans and recompiles the bonus part.
### *Acknowledgements* <a name="ack"></a>
This project is part of the curriculum at [42 Madrid](https://www.42madrid.com/). Thanks to the 42 Network for providing the resources and guidance to complete this project.
