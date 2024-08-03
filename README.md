# Pipex
__Pipex__
# Index
- [Description](#description)
	- [Allowed functions](#allow)
	- [Project files](#pr_files)
		- [Header file](#hd_file)
		- [Helper functions](#hp_file)
	- [Buffer size](#buff_file)
	- [Compilation](#compilation)
	- [Usage](#usage)
	- [Notes](#notes)
### _Description_ <a name="description"></a>
**Pipex** is a pipe handling project in C. This program replicates the behavior of the shell construction *'< file1 cmd1 | cmd2 > file2'*. The program takes four arguments: *infile*, *command1*, *command2*, and *outfile*.  
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
