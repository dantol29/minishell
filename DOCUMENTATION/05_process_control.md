### 5.      PROCESS CONTROL
```
16. fork; // Create a new process.
17. wait; // Wait for a child process to terminate.
18. waitpid; // Wait for a specific child process to terminate.
19. wait3; // Wait for a child process and retrieve status information.
20. wait4; // Wait for a specific child process and retrieve status information.
21. execve; // Execute a program.
22. exit; // Exit a program.
```
________________________________________
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
### _WAIT_
```
#include <sys/types.h>
#include <sys/wait.h>

pid_t wait(int *status);
```
- Simply waits for any child process to terminate.

**Return Value:**
- Success: the process ID of the terminated child process
- Error: -1
____________________________________
### _WAITPID_
```
#include <sys/types.h>
#include <sys/wait.h>

pid_t waitpid(pid_t pid, int *wstatus, int options);
```

 - Is used to wait for the child termination.

**Return Value:**
- Success: the process ID of the terminated child process
- Error: -1
____________________________________
### _WAIT3_
```
#include <sys/types.h>
#include <sys/wait.h>

pid_t wait3(int *status, int options, struct rusage *rusage);
```
- Wait for a child process and retrieve status information.

**Return Value:**
- Success: the process ID of the terminated child process
- Error: -1
____________________________________
### _WAIT4_
```
#include <sys/types.h>
#include <sys/wait.h>

pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);
```
- Wait for a specific child process and retrieve status information. 

**Return Value:**
- Success: the process ID of the terminated child process
- Error: -1
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
# _EXIT_ 
```
#include <unistd.h>

exit [n]
```
 - The  exit  utility  shall cause the shell to exit from its current execution             
    environment with the exit status specified by the unsigned decimal integer n.
- If the current execution environment is  a  subshell  environment,
    the  shell shall exit from the subshell environment with the specified
    exit status and continue in the environment from which that  subshell  environment  was  invoked;
  - otherwise,  the  shell utility shall terminate with the specified exit status.
  - If n is specified, but its value is not between 0 and 255 inclusively, the exit status is undefined.

STDERR
       The standard error shall be used only for diagnostic messages
