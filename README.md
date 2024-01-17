# MINISHELL
____________________________________________
## FUNCTION USED TO CREATE MINISHELL


PROCESS CONTROL
```
fork; // Create a new process.
wait; // Wait for a child process to terminate.
waitpid; // Wait for a specific child process to terminate.
wait3; // Wait for a child process and retrieve status information.
wait4; // Wait for a specific child process and retrieve status information.
execve; // Execute a program.
exit; // Exit a program.
```
SIGNAL HANDLING
```
signal; // Set a signal handler.
sigaction; // Handle signals with extended functionality.
```
DIRECTORY OPERATIONS
```
opendir; // Open a directory.
readdir; // Read a directory entry.
closedir; // Close a directory.
```
FILE INFORMATION
```
stat; // Retrieve file information.
lstat; // Retrieve file information (follows symbolic links).
fstat; // Retrieve file information (from an open file descriptor).
```
TERMINAL HANDLING
```
tcsetattr; // Set terminal attributes.
tcgetattr; // Get terminal attributes.
tgetent; // Get terminal capabilities.
tgetflag; // Get terminal flag.
tgetnum; // Get terminal number.
tgetstr; // Get terminal string.
tgoto; // String capabilities for cursor positioning.
tputs; // Output terminal capabilities.
```
I/O CONTROL
```
isatty; // Check if a file descriptor refers to a terminal.
ttyname; // Get the name of the terminal.
ioctl; // Perform I/O control operations.
```
ENVIRONMENT
```
getenv; // Retrieve the value of an environment variable.
```
FILE OPERATIONS
```
access; // Check file accessibility.
open; // Open a file.
read; // Read from a file.
close; // Close a file.
unlink; // Delete a file.
```
PROCESS TERMINATION
```
kill; // Send a signal to a process.
```
ERROR HANDLING
```
strerror; // Get a descriptive string for an error code.
perror; // Print a descriptive error message.
```
MEMORY ALLOCATION
```
malloc; // Allocate memory dynamically.
free; // Deallocate previously allocated memory.
```
INPUT/OUTPUT
```
printf; // Print formatted output.
write; // Write to a file descriptor.
```

## PROCESS CONTROL
### _FORK_
```
#include <sys/types.h>
#include <unistd.h>


pid_t fork(void);
```

- Creates  a new process by duplicating the calling process. 
- The new process is referred to as the child process.  
- The calling process is referred to as the parent process.

**Return Value:**
- Success: On success, the PID of the child process is returned in the parent, and 0 is returned in the child.
- Error: 0
____________________________________
### _WAITPID_
```
#include <sys/types.h>
#include <sys/wait.h>


pid_t waitpid(pid_t pid, int *wstatus, int options);
```

 - Is used to wait for the child termination.

**Return Value:**
- Success: the process ID of the child
- Error: -1
____________________________________
### _WAIT_
```
include


function
```

**Return Value:**
- Success:
- Error:
____________________________________
### _WAIT3_
```
include


function
```

**Return Value:**
- Success:
- Error:
____________________________________
### _WAIT4_
```
include


function
```

**Return Value:**
- Success:
- Error:
________________________________
### _EXECVE_

```
#include <unistd.h>


int execve(const char *pathname, char *const argv[], char *const envp[]);
```

-Executes the program referred to by pathname. 
-This causes the program that is currently being run by the calling process  to  be  replaced  with  a  new  program,

**Return Value:**
- Success:
- Error: -1, and errno is set appropriately.
____________________________________
## SIGNAL HANDLING
### _SIGNAL_
```
include


function
```
 
**Return Value:**
- Success:
- Error:
____________________________________
### _SIGACTION_
```
include


function
```
 
**Return Value:**
- Success:
- Error:
____________________________________
## DIRECTORY OPERATIONS
### _OPENDIR_
```
#include <sys/types.h>
#include <dirent.h>


DIR *opendir(const char *name);
```

 - opens a directory stream corresponding to the directory name, and returns a pointer to the directory stream.  
 - The stream is positioned at the first entry in the directory.

**Return Value:**
- Success:  a pointer to the directory stream.
- Error: NULL is returned,  and  errno  is set appropriately.

_________________________________________________________________
### _READDIR_
```
 #include <dirent.h>


struct dirent *readdir(DIR *dirp);
```

 - The  readdir()  function returns a pointer to a dirent structure
representing the next directory entry in the directory stream pointed to by dirp.
-In the glibc implementation, the dirent structure is defined as follows:
```

           struct dirent {
               ino_t          d_ino;       /* Inode number */
               off_t          d_off;       /* Not an offset; see below */
               unsigned short d_reclen;    /* Length of this record */
               unsigned char  d_type;      /* Type of file; not supported
                                              by all filesystem types */
               char           d_name[256]; /* Null-terminated filename */
           };
```

**Return Value:**
- Success: a pointer to a dirent structure.   (This  structure  may  be statically allocated;
            do not ttempt to free(3) it.)        
            If  the end of the directory stream is reached, NULL is returned and errno is not changed.
- Error:  NULL is returned and errno is set appropriately.
       To  distinguish  end   of  stream  from  an  error, set errno to zero before calling readdir() and then check the  value of errno if NULL is returned.

_________________________________________________

### _CLOSEDIR_
```
include


function
```
 
**Return Value:**
- Success:
- Error:

_________________________________
## FILE INFORMATION
### _STAT_
```
include


function
```
 
**Return Value:**
- Success:
- Error:
____________________________________
### _LSTAT_
```
include


function
```
   
**Return Value:**
- Success:
- Error:
____________________________________
### _FSTAT_
```
include


function
```

**Return Value:**
- Success:
- Error:
____________________________________
## MEMORY ALLOCATION
____________________________________
### _MALLOC_
```
include


function
```
 
**Return Value:**
- Success:
- Error:
____________________________________
### _FREE_
```
include


function
```
 
**Return Value:**
- Success:
- Error:
____________________________________
## INPUT/OUTPUT
### _PRINTF_
```
include


function
```
 
**Return Value:**
- Success:
- Error:
____________________________________
### _WRITE_
```
include


function
```
  
**Return Value:**
- Success:
- Error:
____________________________________
## FILE OPERATIONS
### _OPEN_
```
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);

```
 
**Return Value:**
- Success:
- Error:
____________________________________
### _READ_
```
#include <unistd.h>


ssize_t read(int fd, void *buf, size_t count);
```

 - read() attempts to read up to count bytes from file descriptor fd into the
       buffer starting at buf.
 - On files that support seeking, the read operation commences  at  the  file
       offset,  and  the  file offset is incremented by the number of bytes read.
       If the file offset is at or past the end of file, no bytes are  read,  and
       read() returns zero.
   -  If  count  is  zero, read() may detect the errors described below.  In the
       absence of any errors, or if read() does not check for  errors,  a  read()
       with a count of 0 returns zero and has no other effects.
   -   According  to  POSIX.1,  if count is greater than SSIZE_MAX, the result is
       implementation-defined; see NOTES for the upper limit on Linux.

 
**Return Value:**
- Success:
   -number of bytes read is returned (zero  indicates  end  of file), and the file position is advanced by this number.
   -It is not an error if this number is smaller than the number of bytes requested;
   this may happen  for  example  because fewer bytes are actually available right now
       (maybe because we were close to end-of-file, or  because  we  are  reading
       from  a  pipe, or from a terminal), or because read() was interrupted by a
       signal.  See also NOTES.

- Error:
  -  On error, -1 is returned, and errno is set appropriately.  In  this  case,
       it is left unspecified whether the file position (if any) changes.

____________________________________
### _CLOSE_
```
#include <unistd.h>


int close(int fd);
```
 - closes a file descriptor, so that it no longer refers to any file and may be reused.
 -Any record locks (see fcntl(2)) held on the file it was associated with,
 and owned  by  the  process, are removed (regardless of the file descriptor that was used to obtain the lock).
-If  fd  is  the  last  file  descriptor  referring  to  the underlying open file description (see open(2)), 
 the resources associated with the open file description are freed;
 -if the file descripor was the last reference to a file which has been removed using unlink(2), the file is deleted.

**Return Value:**
- Success: 0
- Error: -1 and errno is set appropriately.
____________________________________
### _ACCESS_
```
#include <unistd.h>


int access(const char *pathname, int mode);
```

 - Checks  whether the calling process can access the file pathname. 0 is default mode.  
-Can the user who invoked me read/write/execute this file?

**Return Value:**
- Success: 0
- Error: -1 is returned, and  errno is set appropriately.
____________________________________
### _READLINE_

```
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


char *readline(const char *prompt);
```

 - Read a line from the terminal and return it, using prompt as a prompt.  
 -If prompt is NULL or the empty string, no prompt is issued.

**Return Value:**
- Success: the text of the line read
- Error: NULL
____________________________________
### _GETCWD_
```
#include <unistd.h>


char *getcwd(char *buf, size_t size);
```

Copies an absolute pathname of the current working directory to the array pointed to by buf, which is of length size.

**Return Value:**
- Success: a null-terminated string containing an absolute pathname of the current working directory
- Error: NULL, errno set appropriately
____________________________________


### _GETENV_
```
#include <stdlib.h>


char *getenv(const char *name);
```

- Searches the environment list to find the environment variable name.

**Return Value:**
- Success: a pointer to the value  in  the  environment
- Error: NULL
____________________________________

### _ISATTY_
```
include


int isatty(int fd);
```

- Check whether a given file descriptor refers to a terminal.

**Return Value:**
- Success: 1 if the file descriptor refers to a terminal
- Error: 0, errno is set to indicate the error
____________________________________

### _SIGEMTYSET_
```
include


function
```

**Return Value:**
- Success:
- Error:
____________________________________
### _SIGADDSET_
```
include


function
```

**Return Value:**
- Success:
- Error:
____________________________________
### _KILL_
```
include


function
```

**Return Value:**
- Success:
- Error:
____________________________________
### _CHDIR_
```
include


function
```
 
**Return Value:**
- Success:
- Error:
____________________________________

### _UNLINK_
```
include


function
```

**Return Value:**
- Success:
- Error:
____________________________________
### _rl_clear_history_
```
include


function
```

**Return Value:**
- Success:
- Error:
____________________________________
### _rl_on_new_line_
```
include


function
```

**Return Value:**
- Success:
- Error:
____________________________________
### _rl_replace_line_ 
```
include


function
```
 
**Return Value:**
- Success:
- Error:
____________________________________
### _rl_redisplay_
```
include


function
```

**Return Value:**
- Success:
- Error:
____________________________________
### _ADD_HISTORY_
```
include


function
```

**Return Value:**
- Success:
- Error:
_____________________________________________________
Alena
_____________________________________________________________
### _DUP_
```
#include <unistd.h>


int dup(int oldfd);
```
      
 **Description**
- Creates a copy of the file descriptor `oldfd`.
- Uses the lowest-numbered unused file descriptor for the new one.
- Both old and new descriptors refer to the same open file.
- They share file offset and status flags.
- Duplicate descriptor does not have the close-on-exec flag set.

**Return:**
- Success:  new file descriptor.
- Error:    -1, and `errno` is set appropriately.
___________________________________________________________
### _DUP2_      
```
#include <unistd.h>


int dup2(int oldfd, int newfd);
```

 **Description**
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
### _PIPE_
```
#include <unistd.h>


int pipe(int pipefd[2]);
```
 **Description**
- Creates a unidirectional data channel (pipe) for interprocess communication.
- Returns two file descriptors in the array `pipefd` (read end: `pipefd[0]`, write end: `pipefd[1]`).
- Data written to the write end is buffered until read from the read end.

**Return Value:**
- Success:  0.
- Error:  -1, `errno` is set appropriately, and `pipefd` is unchanged.

____________________________________________________

### _STRERROR_
```
include


function
```

 **Description**
 - 
 
**Return Value:**
- Success:
- Error:
___________________________
### _PERROR_
```
include


function
```

 **Description**
 - 
 
**Return Value:**
- Success:
- Error:
____________________________________
### _TTYNAME_
```
include


function
```

 **Description**
 - 
  
**Return Value:**
- Success:
- Error:
____________________________________
### _TTYSLOT_
```
include


function
```

 **Description**
 - 
 
**Return Value:**
- Success:
- Error:
____________________________________
### _IOCTL_
```
include


function
```

 **Description**
 - 
 
**Return Value:**
- Success:
- Error:
____________________________________
### _TCSETATTR_
```
include


function
```

 **Description**
 - 
 
**Return Value:**
- Success:
- Error:
____________________________________
### _TCGETATTR_
```
include


function
```

 **Description**
 - 
 
**Return Value:**
- Success:
- Error:
____________________________________
### _TGETENT_
```
include


function
```

 **Description**
 - 
 
**Return Value:**
- Success:
- Error:
____________________________________
### _TGETFLAG_
```
include


function
```

 **Description**
 - 
 
**Return Value:**
- Success:
- Error:
____________________________________
### _TGETNUM_
```
include


function
```

 **Description**
 - 
 
**Return Value:**
- Success:
- Error:
____________________________________
### _TGETSTR_
```
include


function
```

 **Description**
 - 
 
**Return Value:**
- Success:
- Error:
____________________________________
### _TGOTO_
```
include


function
```

 **Description**
 - 
 
**Return Value:**
- Success:
- Error:
____________________________________
### _TPUTS_
**_include_
```
function
```

 **Description**
 - 
 
**Return Value:**
- Success:
- Error:


____________________________________
# _EXIT_ 
```
exit [n]
```
 **Description**
 - The  exit  utility  shall cause the shell to exit from its current execution environment with the
       exit status specified by the unsigned decimal integer n.
   - If the current execution environment is  a  subshell  environment,
     the  shell shall exit from the subshell environment with the specified
      exit status and continue in the environment from which that  subshell  environment  was  invoked;
  - otherwise,  the  shell utility shall terminate with the specified exit status.
  - If n is specified, but its value is not between 0 and 255 inclusively, the exit status is undefined.

STDERR
       The standard error shall be used only for diagnostic messages.

____________________________________
