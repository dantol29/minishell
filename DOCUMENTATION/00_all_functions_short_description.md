## ALLOWED FUNCTION  TO CREATE MINISHELL

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
17. wait;           // Wait for a child process to terminate.
18. waitpid;        // Wait for a specific child process to terminate.
19. wait3;          // Wait for a child process and retrieve status information.
20. wait4;          // Wait for a specific child process and retrieve status information.
21. execve;         // Execute a program.
22. exit;            // Exit a program.

### 6. SIGNAL HANDLING
23. signal;         // Set a signal handler.
24. sigaction;       // Handle signals with extended functionality.
25. sigemptyset;     // Initialize an empty signal set.
26. sigaddset;       // Add a signal to a signal set.
27. kill;           // Send a signal to a process.

### 7. DIRECTORY OPERATIONS
28. opendir;         // Open a directory.
29. readdir;         // Read a directory entry.
30. closedir;        // Close a directory.

### 8. FILE INFORMATION
31. stat;           // Retrieve file information.
32. lstat;          // Retrieve file information (follows symbolic links).
33. fstat;          // Retrieve file information (from an open file descriptor).

### 9. FILE SYSTEM
34. getcwd;         // Get the current working directory.
35. chdir;          // Change the current working directory.

### 10. TERMINAL HANDLING
36. tcsetattr;      // Set terminal attributes.
37. tcgetattr;      // Get terminal attributes.
38. tgetent;        // Get terminal capabilities.
39. tgetflag;       // Get terminal flag.
40. tgetnum;        // Get terminal number.
41. tgetstr;        // Get terminal string.
42. tgoto;          // String capabilities for cursor positioning.
43. tputs;          // Output terminal capabilities.
44. ttyslot;        // Get slot in the utmp file.

### 11. I/O CONTROL
45. isatty;         // Check if a file descriptor refers to a terminal.
46. ttyname;         // Get the name of the terminal.
47. ioctl;           // Perform I/O control operations.

### 12. ENVIRONMENT
48. getenv;         // Retrieve the value of an environment variable.

### 13. PIPE AND DUPLICATION
49. dup;             // Duplicate a file descriptor.
50. dup2;           // Duplicate a file descriptor to a specific descriptor number.
51. pipe;           // Create a pipe for interprocess communication.

### 14. ERROR HANDLING
52. strerror;       // Get a descriptive string for an error code.
53. perror;         // Print a descriptive error message.