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
_____________________________________________________________

# DUP

`int dup(int oldfd);`
      
*#include <unistd.h>*

- Creates a copy of the file descriptor `oldfd`.
- Uses the lowest-numbered unused file descriptor for the new one.
- Both old and new descriptors refer to the same open file.
- They share file offset and status flags.
- Duplicate descriptor does not have the close-on-exec flag set.

**Return:**
- Success:  new file descriptor.
- Error:    -1, and `errno` is set appropriately.

___________________________________________________________
# DUP2              
`int dup2(int oldfd, int newfd);`

*#include <unistd.h>*

- Creates a copy of the file descriptor `oldfd` using the specified `newfd`.
- If `newfd` was previously open, it is closed before reuse.
- Closing and reusing `newfd` are performed atomically to avoid race conditions.

**Note:**
- If `oldfd` is not valid, the call fails, and `newfd` is not closed.
- If `oldfd` and `newfd` have the same value, `dup2()` does nothing and returns `newfd`.

**Return Value:**
- Success: Returns the new file descriptor.
- Error: Returns -1, and `errno` is set appropriately.

_____________________________________________________________
# PIPE

`int pipe(int pipefd[2]);`

*#include <unistd.h>*

- Creates a unidirectional data channel (pipe) for interprocess communication.
- Returns two file descriptors in the array `pipefd` (read end: `pipefd[0]`, write end: `pipefd[1]`).
- Data written to the write end is buffered until read from the read end.

**Return Value:**
- Success:  0.
- Error:  -1, `errno` is set appropriately, and `pipefd` is unchanged.

____________________________________________________
# OPENDIR
`DIR *opendir(const char *name);`

*#include <sys/types.h>*
*#include <dirent.h>*

 - opens a directory stream corresponding to the directory name, and returns a pointer to the directory stream.  
 - The stream is positioned at the first entry in the directory.

**Return Value:**
-Success:  a pointer to the directory stream.
- Error: NULL is returned,  and  errno  is set appropriately.

_________________________________________________________________
#READDIRV


**Return Value:**
- Success:
- Error:
_________________________________________________
# CLOSEDIR

**Return Value:**
- Success:
- Error:

_________________________________
# STRERROR

**Return Value:**
- Success:
- Error:
___________________________
# PERROR

**Return Value:**
- Success:
- Error:
____________________________________

# TTYNAME

**Return Value:**
- Success:
- Error:
____________________________________
#TTYSLOT
```ttyslot```

**Return Value:**
- Success:
- Error:
____________________________________
# IOCTL


**Return Value:**
- Success:
- Error:
____________________________________
# TCSETATTR


**Return Value:**
- Success:
- Error:
____________________________________
# TCGETATTR


**Return Value:**
- Success:
- Error:
____________________________________
# TGETENT

**Return Value:**
- Success:
- Error:
____________________________________
# TGETFLAG

**Return Value:**
- Success:
- Error:
____________________________________
# TGETNUM

**Return Value:**
- Success:
- Error:
____________________________________
#TGETSTR


**Return Value:**
- Success:
- Error:
____________________________________
# TGOTO


**Return Value:**
- Success:
- Error:
____________________________________
# TPUTS

**Return Value:**
- Success:
- Error:
____________________________________
# PRINTF

**Return Value:**
- Success:
- Error:
____________________________________
# MALLOC

**Return Value:**
- Success:
- Error:
____________________________________
# FREE

**Return Value:**
- Success:
- Error:
____________________________________
# WRITE

**Return Value:**
- Success:
- Error:
____________________________________
# OPEN

**Return Value:**
- Success:
- Error:
____________________________________
# READ

**Return Value:**
- Success:
- Error:
____________________________________
# CLOSE

**Return Value:**
- Success:
- Error:
____________________________________
# EXIT

**Return Value:**
- Success:
- Error:
____________________________________
