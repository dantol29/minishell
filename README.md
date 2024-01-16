# Minishell
## Development
```
1. Interpret: shell reads commands from stdin and executes them.
2. Terminate: shell executes any shutdown commands, frees ups any memory, and terminates.
```

## Functions used to create the minishell
_check if shell is running in interactive mode_
```
int isatty(int fd);
```
Check whether a given file descriptor refers to a terminal.
The function returns 1 if the file descriptor refers to a terminal, and 0 otherwise.

readline

rl_clear_history

rl_on_new_line

rl_replace_line

rl_redisplay

add_history

printf

malloc

free

write

access

open

read

close

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

exit

getcwd

chdir

stat

lstat

fstat

unlink

execve

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

getenv

tcsetattr

tcgetattr

tgetent

tgetflag

tgetnum

tgetstr

tgoto

tputs

