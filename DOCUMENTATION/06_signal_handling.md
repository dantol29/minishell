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
#include <signal.h>

sighandler_t signal(int signum, sighandler_t handler);
```
- Is used to establish a signal handler, which is a function that will be called in response to a specific signal being received by the process.
- Signum: The signal number (e.g., SIGINT, SIGTERM) for which you want to establish the handler.
- Handler: The function to be called when the specified signal is received. It should be a function with the signature void handler(int).
  
**Return Value:**
- Success: the previous value of the signal handler
- Error: -1
____________________________________
### _SIGACTION_
```
#include <signal.h>

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```
- Is used to change the action taken by a process.
-  the new action for signal signum is installed from act, the previous action is saved in oldact.

**Return Value:**
- Success: 0
- Error: -1, errno is set appropriately
____________________________________
### _SIGEMPTYSET_
```
#include <signal.h>

int sigemptyset(sigset_t *set);
```
 - Is used to initialize an empty set of signals
 
**Return Value:**
- Success: 0
- Error: -1, errno is set appropriately
_____________________________
### _SIGADDSET_
```
#include <signal.h>

int sigaddset(sigset_t *set, int signum);
```
- Is used to add a specific signal to a signal set.

**Return Value:**
- Success: 0
- Error: -1, errno is set appropriately
________________________________________
### _KILL_
```
#include <signal.h>

int kill(pid_t pid, int sig);
```
- Is used to send a signal to a process or a group of processes

**Return Value:**
- Success: 0 
- Error: -1, errno is set appropriately
