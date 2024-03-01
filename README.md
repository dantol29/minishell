# miniSHELL
Fully functional shell for your command-line needs!

## How to compile
```
make && ./minishell
```
____________________________________________
## Functions used

### 1. USER INTERACTION (Readline and Display)
1. readline;            // Read a line of input using the Readline library.
2. rl_clear_history;    // Clear the history list for the current readline session.
3. rl_on_new_line;      // Notify Readline that the cursor has moved to a new line.
4. rl_replace_line;         // Replace the contents of the current Readline line.
5. rl_redisplay;        // Force Readline to re-display the current input line.
6. add_history;         // Add a line to the Readline history.

### 2. INPUT/OUTPUT
7. printf;           // Print formatted output to the standard output.
8. write;           // Write to a file descriptor.

### 3. MEMORY ALLOCATION
9. malloc;          // Allocate memory dynamically.
10. free;           // Deallocate previously allocated memory.

### 4. FILE OPERATIONS
11. access;         // Check file accessibility.
12. open;           // Open a file.
13. read;           // Read from a file.
14. close;           // Close a file.
15. unlink;         // Delete a file.

### 5. PROCESS CONTROL
16. fork;           // Create a new process.
17. waitpid;        // Wait for a specific child process to terminate.
18. execve;         // Execute a program.
19. exit;            // Exit a program.

### 6. SIGNAL HANDLING
22. signal;         // Set a signal handler.

### 7. FILE SYSTEM
23. getcwd;         // Get the current working directory.
24. chdir;          // Change the current working directory.

### 8. PIPE AND DUPLICATION
25. dup;             // Duplicate a file descriptor.
26. dup2;           // Duplicate a file descriptor to a specific descriptor number.
27. pipe;           // Create a pipe for interprocess communication.

### 9. ERROR HANDLING
28. strerror;       // Get a descriptive string for an error code.
29. perror;         // Print a descriptive error message.
_________________________________________________________
