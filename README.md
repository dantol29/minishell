# Minishell
## Development
```
1. Interpret: shell reads commands from stdin and executes them.
2. Terminate: shell executes any shutdown commands, frees ups any memory, and terminates.
```

## Functions used to create the minishell
________________________________
### ISATTY
```
int isatty(int fd);
```
_check if shell is running in interactive mode_
Check whether a given file descriptor refers to a terminal.
The function returns 1 if the file descriptor refers to a terminal, and 0 otherwise.

**Return Value:**
- Success:
- Error:
____________________________________
### READLINE
```
char *readline(const char *prompt);
```
_print a message and store user input_
Prints a string to the user before they enter a command. 

**Return Value:**
- Success:
- Error:
____________________________________
### GETCWD
```
char *getcwd(char *buf, size_t size);
```
 _get the current working directory_
The function returns a pointer to the provided buffer if successful and NULL on failure.
If the buffer size is too small to hold the entire path, NULL is also returned.

**Return Value:**
- Success:
- Error:
____________________________________


____________________________________
### ACCESS
access

**Return Value:**
- Success:
- Error:
____________________________________
### FORK
fork

**Return Value:**
- Success:
- Error:
____________________________________
### WAIT
wait

**Return Value:**
- Success:
- Error:
____________________________________
### WAITPID
waitpid

**Return Value:**
- Success:
- Error:
____________________________________
### WAIT3
wait3

**Return Value:**
- Success:
- Error:
____________________________________
### WAIT4
wait4

**Return Value:**
- Success:
- Error:
____________________________________
### SIGNAL
signal

**Return Value:**
- Success:
- Error:
____________________________________
### SIGACTION
sigaction

**Return Value:**
- Success:
- Error:
____________________________________
### SIGEMTYSET 
sigemptyset

**Return Value:**
- Success:
- Error:
____________________________________
### SIGADDSET
sigaddset

**Return Value:**
- Success:
- Error:
____________________________________
### KILL
kill

**Return Value:**
- Success:
- Error:
____________________________________
### CHDIR
chdir

**Return Value:**
- Success:
- Error:
____________________________________
### STAT
stat

**Return Value:**
- Success:
- Error:
____________________________________
### LSTAT
lstat

**Return Value:**
- Success:
- Error:
____________________________________
### FSTAT
fstat

**Return Value:**
- Success:
- Error:
____________________________________
### UNLINK 
unlink

**Return Value:**
- Success:
- Error:
____________________________________
### EXECVE
`int execve(const char *pathname, char *const argv[], char *const envp[]);`

executes the program referred to by pathname.  This causes the
program that is currently being run by the calling process  to  be  re‐
placed  with  a  new  program,

**Return Value:**
- Success:
- Error: -1, and `errno` is set appropriately.
____________________________________
### GETENV

**Return Value:**
- Success:
- Error:
____________________________________
### rl_clear_history


**Return Value:**
- Success:
- Error:
____________________________________

### rl_on_new_line


**Return Value:**
- Success:
- Error:
____________________________________

### rl_replace_line 

**Return Value:**
- Success:
- Error:
____________________________________

### rl_redisplay

**Return Value:**
- Success:
- Error:
____________________________________
### ADD_HISTORY
add_history

**Return Value:**
- Success:
- Error:

Alena
_____________________________________________________________

### DUP

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
### DUP2              
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
### PIPE

`int pipe(int pipefd[2]);`

*#include <unistd.h>*

- Creates a unidirectional data channel (pipe) for interprocess communication.
- Returns two file descriptors in the array `pipefd` (read end: `pipefd[0]`, write end: `pipefd[1]`).
- Data written to the write end is buffered until read from the read end.

**Return Value:**
- Success:  0.
- Error:  -1, `errno` is set appropriately, and `pipefd` is unchanged.

____________________________________________________
### OPENDIR
`DIR *opendir(const char *name);`

*#include <sys/types.h>*
*#include <dirent.h>*

 - opens a directory stream corresponding to the directory name, and returns a pointer to the directory stream.  
 - The stream is positioned at the first entry in the directory.

**Return Value:**
- Success:  a pointer to the directory stream.
- Error: NULL is returned,  and  errno  is set appropriately.

_________________________________________________________________
### READDIR  readdir - read a directory
`struct dirent *readdir(DIR *dirp);`
 #include <dirent.h>
The  readdir()  function returns a pointer to a dirent structure
representing the next directory entry in the directory stream pointed to by dirp.
It returns NULL on reaching the end of the directory stream or if an error occurred.

       In the glibc implementation, the dirent structure is defined as follows:

           struct dirent {
               ino_t          d_ino;       /* Inode number */
               off_t          d_off;       /* Not an offset; see below */
               unsigned short d_reclen;    /* Length of this record */
               unsigned char  d_type;      /* Type of file; not supported
                                              by all filesystem types */
               char           d_name[256]; /* Null-terminated filename */
           };


**Return Value:**
- Success: a pointer to a dirent structure.   (This  structure  may  be statically allocated;
            do not ttempt to free(3) it.)        
            If  the end of the directory stream is reached, NULL is returned and errno is not changed.
- Error:  NULL is returned and errno is set appropriately.
       To  distinguish  end   of  stream  from  an  error, set errno to zero before calling readdir() and then check the  value of errno if NULL is returned.

_________________________________________________
### CLOSEDIR

**Return Value:**
- Success:
- Error:

_________________________________
### STRERROR

**Return Value:**
- Success:
- Error:
___________________________
### PERROR

**Return Value:**
- Success:
- Error:
____________________________________

### TTYNAME

**Return Value:**
- Success:
- Error:
____________________________________
### TTYSLOT

**Return Value:**
- Success:
- Error:
____________________________________
### IOCTL


**Return Value:**
- Success:
- Error:
____________________________________
### TCSETATTR


**Return Value:**
- Success:
- Error:
____________________________________
### TCGETATTR


**Return Value:**
- Success:
- Error:
____________________________________
### TGETENT

**Return Value:**
- Success:
- Error:
____________________________________
### TGETFLAG

**Return Value:**
- Success:
- Error:
____________________________________
### TGETNUM

**Return Value:**
- Success:
- Error:
____________________________________
#TGETSTR


**Return Value:**
- Success:
- Error:
____________________________________
### TGOTO


**Return Value:**
- Success:
- Error:
____________________________________
### TPUTS

**Return Value:**
- Success:
- Error:
____________________________________
### PRINTF

**Return Value:**
- Success:
- Error:
____________________________________
### MALLOC

**Return Value:**
- Success:
- Error:
____________________________________
### FREE

**Return Value:**
- Success:
- Error:
____________________________________
### WRITE

**Return Value:**
- Success:
- Error:
____________________________________
### OPEN

**Return Value:**
- Success:
- Error:
____________________________________
### READ

**Return Value:**
- Success:
- Error:
____________________________________
### CLOSE - close a file descriptor
 #include <unistd.h>

`int close(int fd);`

 closes a file descriptor, so that it no longer refers to any file and may be reused.
 Any record locks (see fcntl(2)) held on the file it was associated with,
 and owned  by  the  process, are removed (regardless of the file descriptor that was used to obtain the lock).

If  fd  is  the  last  file  descriptor  referring  to  the underlying open file description (see open(2)), 
 the resources associated with the open file description are freed;
 if the file descripor was the last reference to a file which has been removed using unlink(2), the file is deleted.

**Return Value:**
- Success: 0
- Error: -1 and errno is set appropriately.
____________________________________
# EXIT — cause the shell to exit
`exit [n]`
The  exit  utility  shall cause the shell to exit from its current execution environment with the
       exit status specified by the unsigned decimal integer n.  If the current execution environment is
       a  subshell  environment,  the  shell shall exit from the subshell environment with the specified
       exit status and continue in the environment from which that  subshell  environment  was  invoked;
       otherwise,  the  shell utility shall terminate with the specified exit status. If n is specified,
       but its value is not between 0 and 255 inclusively, the exit status is undefined.

STDERR
       The standard error shall be used only for diagnostic messages.

____________________________________
