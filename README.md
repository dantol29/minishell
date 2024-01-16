# Minishell
## Development
```
1. Interpret: shell reads commands from stdin and executes them.
2. Terminate: shell executes any shutdown commands, frees ups any memory, and terminates.
```

## Functions used to create the minishell
1. _check if shell is running in interactive mode_
```
int isatty(int fd);
```
Check whether a given file descriptor refers to a terminal.
The function returns 1 if the file descriptor refers to a terminal, and 0 otherwise.

2. _print a message and store user input_
```
char *readline(const char *prompt);
```
Prints a string to the user before they enter a command. 

3. _get the current working directory_
```
char *getcwd(char *buf, size_t size);
```
The function returns a pointer to the provided buffer if successful and NULL on failure.
If the buffer size is too small to hold the entire path, NULL is also returned.

rl_clear_history

rl_on_new_line

rl_replace_line

rl_redisplay

add_history

access

fork

wait

waitpid

wait3

wait4

signal

sigaction

sigemptyset

sigaddset

kill

chdir

stat

lstat

fstat

unlink

execve

getenv
_______


dup

dup2

pipe

opendir

readdir

closedir

strerror

perror

ttyname

ttyslot

ioctl

tcsetattr

tcgetattr

tgetent

tgetflag

tgetnum

tgetstr

tgoto

tputs

printf

malloc

free

write

open

read

close

exit
