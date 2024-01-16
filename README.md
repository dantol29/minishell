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


```dup```
#include <unistd.h>

       The  dup() system call creates a copy of the file descriptor oldfd, using the lowest-numbered unused file descriptor for the new descriptor.

       After a successful return, the old and new file descriptors may be used interchangeably.  
      They  refer  to  the same open file description (see   open(2)) and thus share file offset and file status flags;
       for example,  if the file offset is modified by using lseek(2) on one of the file descriptors, the offset is also changed for the other.

       The two file descriptors do not share file descriptor flags (the close-on-exec  flag).
       The close-on-exec flag (FD_CLOEXEC; see fcntl(2)) for  the duplicate descriptor is off.
RETURN VALUE
       Success:  the new file descriptor. 
       Error: -1 is returned, and errno is set appropriately.



```dup2```

#include <unistd.h>

 The dup2() system call performs the same task as dup(), but instead  of    using  the lowest-numbered unused file descriptor,
 it uses the file descriptor number specified in newfd.  
If the file descriptor  newfd  was   previously open, it is silently closed before being reused.

 The  steps  of  closing  and reusing the file descriptor newfd are performed atomically. 
  This is  important,  because  trying  to  implement  equivalent  functionality  using close(2) and dup() would be subject to  race conditions,
  whereby newfd might be reused between the  two  steps.
   Such  reuse  could  happen because the main program is interrupted by a   signal handler that allocates a file descriptor,
   or because a  parallel  thread allocates a file descriptor.

  Note the following points:

       *  If  oldfd  is  not a valid file descriptor, then the call fails, and   newfd is not closed.

       *  If oldfd is a valid file descriptor, and newfd has the same value as  oldfd, then dup2() does nothing, and returns newfd.
          
RETURN VALUE
       Success:  the new file descriptor. 
       Error: -1 is returned, and errno is set appropriately.
       

```pipe```

```opendir```

```readdirv```

```closedir```

```strerror```

```perror```

```ttyname```

```ttyslot```

```ioctl```

```tcsetattr```

```tcgetattr```

```tgetent```

```tgetflag```

```tgetnum```

```tgetstr```

```tgoto```

```tputs```

```printf```

```malloc```

```free```

```write```

```open```

```read```

```close```

```exit```
