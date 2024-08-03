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
This program replicates the behavior of the shell construction *'< infile cmd1 | cmd2 > outfile'*. The program takes four arguments: *infile*, *command1*, *command2*, and *outfile*.  
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
* **Header files (*.h)**
* **Source code files (*.c)**
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

    Funtion main (argc, argv, env)
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


#### Sequence Diagram of get_next_line Function and Subfunctions <a name="diagram"></a>
#### Code Explanation <a name="code"></a>
### *Acknowledgements* <a name="ack"></a>
### _Bonus Part_ <a name="bonus"></a>
#### Bonus Requirements <a name="b_req"></a>
#### Bonus Files <a name="b_files"></a>
#### Compilation for Bonus Part<a name="b_compilation"></a>
#### Usage for Bonus Part <a name="b_usage"></a>
This project is part of the curriculum at [42 Madrid](https://www.42madrid.com/). Thanks to the 42 Network for providing the resources and guidance to complete this project.
