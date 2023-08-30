# Minishell

This project features a simple bash shell, capable of executing almost all the commands as the original bash shell does.

## Description

This project aims to replicate a bash shell with almost all of its capabilities. It uses the readline library to read from the standard input, while executing all the needed commands via forking its parent process into multiple child processes, each of which will execute one command. Every process is connected using pipes, while the parent process manages to retrieve the right outputs, exit status, as well as control the handling of signals as needed.

The commands used can be any of the existing commands from the standard bash, as well as all the syntax accepted by it. Only the logical operators "&&", "||" and ";" are not accepted.

The bash itself works by parsing the string received, dividing it into multiple commands by the pipe symbol ("|"), and subdividing each of those into "tokens", in order to differentiate the main command from its arguments or the existance of any kind of redirection. The parent process then forks into several child processes, one for each command, and them are then looked up in the bash command folder, and if able, executed. All these workflow happens in parallel, as original bash does, while keeping the connections between them using pipes. It also accepts input and output redirections, as well as heredoc redirections.

After all the commands are executed, the parent process retrieves all the needed data and exit codes, modifying any of the environment variables if needed, and admits a new set of commands. It also handles all the typical signals, such as "Ctrl+C", or "Ctrl+\" the way a standard shell does.

## Prerequisites

Before using this program, you need to make sure you have installed the last version of the [readline library](https://tiswww.case.edu/php/chet/readline/rltop.html).

## Build and Run the project

This project uses a Makefile in order to create the needed executable. Simply run "make" to generate the executable. You can then launch the shell using:

```
./minishell
```

After the shell is launched, you can start using it as a normal shell, as it were a standard bash shell.

## To do

* Fix heredoc variable expansion. no expande variables en EOF
* Fix open file execution. Should stop the program.
* Fix "export B", without "=" symbol. Should add a variable to export command, but not to env.
* Exit status of syntax error is not set. May have somo other exit status wrong.
* Fix bug in cd command if the parent folder is deleted.
* Add ";", "&&" and "||" funcionalities.

## Authors

This project was developed in collaboration with [SichuanVilly](https://github.com/SichuanVilly)

## License

MIT
