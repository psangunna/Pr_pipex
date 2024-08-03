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
### *Acknowledgements* <a name="ack"></a>
This project is part of the curriculum at [42 Madrid](https://www.42madrid.com/). Thanks to the 42 Network for providing the resources and guidance to complete this project.
