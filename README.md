# Interactive POSIX Shell
### File Descriptions
- headers.h - Contains all the include files, function definitions and extern variables
- main.cpp - Driver code which decides which methods to call
- prompt.cpp - Displays the shell prompt
- parse_input.cpp - Parses and tokenizes the input
- cmd_handler.cpp - Decides which command to call on the basis of parsed input
- background.cpp - Forks and runs processes in a child process
- cd.cpp - Code for changing directories
- ls.cpp - Code for listing all items
- pinfo.cpp - Gives process information
- pipe.cpp - Handles pipes in input
- pwd.cpp - Gets current working directory
- redirection.cpp - Handles input/output redirection
- search.cpp - Searches for a file in current directory recursively
- sig_handler.cpp - Handles signals ctrl+z, ctrl+c, ctrl+d
- makefile - Configuration file for compiling all cpp files
- history.cpp - Handles the execution of the history command. Stores a maximum of 20 commands, and maintains history across sessions by storing in a file


### Execution
- You can run the program by executing the following commands in the terminal (LINUX) 

```shell
make
./a.out
```

### Assumptions
- Pipes and I/O redirection operators will be preceded and succeeded by spaces
- Assuming that the user always runs the file from the directory where a.out is located

***

