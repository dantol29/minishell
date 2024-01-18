###  6.       SIGNAL HANDLING
```
23. signal; // Set a signal handler.
24. sigaction; // Handle signals with extended functionality.
25. sigemptyset; // Initialize an empty signal set.
26. sigaddset; // Add a signal to a signal set.
27. kill; // Send a signal to a process.
```
________________________________________________________________
### _SIGNAL_
```
sighandler_t signal(int signum, sighandler_t handler);
```
- Sets the disposition of the signal signum to handler and returns the previous disposition of the signal.
- Is used to establish a signal handler, which is a function that will be called in response to a specific signal being received by the process.
- Signum: The signal number (e.g., SIGINT, SIGTERM) for which you want to establish the handler.
- Handler: The function to be called when the specified signal is received. It should be a function with the signature void handler(int).
  
**Return Value:**
- Success: the previous value of the signal handler
- Error: -1
____________________________________
### _SIGACTION_
```
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```
- examines or modifies the action to be taken when the signal signum is received.
    It provides more control over signal handling than signal.
- Is used to change the action taken by a process.
-  the new action for signal signum is installed from act, the previous action is saved in oldact.

**Return Value:**
- Success: 0
- Error: -1, errno is set appropriately
____________________________________
### _SIGEMPTYSET_
```
int sigemptyset(sigset_t *set);
```
-  Initializes the signal set set to be an empty set with no signals included.
 - Is used to initialize an empty set of signals
 
**Return Value:**
- Success: 0
- Error: -1, errno is set appropriately
_____________________________
### _SIGADDSET_
```
int sigaddset(sigset_t *set, int signum);
```
- Is used to add a specific signal to a signal set.
- Adds the signal signum to the signal set set.

**Return Value:**
- Success: 0
- Error: -1, errno is set appropriately
________________________________________
### _KILL_
```
int kill(pid_t pid, int sig);
```
- Is used to send a signal to a process or a group of processes
-  The  default  signal for kill is TERM.  Use -l or -L to list available signals.  Particularly useful signals include HUP, INT, KILL, STOP, CONT, and 0.  Alternate signals may be specified in  three  ways:  -9,
       -SIGKILL  or  -KILL.  Negative PID values may be used to choose whole process groups; see the PGID column
       in ps command output.  A PID of -1 is special; it indicates all processes except the kill process  itself
       and init.


**Return Value:**
- Success: 0 
- Error: -1, errno is set appropriately
