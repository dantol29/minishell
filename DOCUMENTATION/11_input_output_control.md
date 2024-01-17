###     11.     I/O CONTROL
```
45. isatty;         // Check if a file descriptor refers to a terminal.
46. ttyname;        // Get the name of the terminal.
47. ioctl;           // Perform I/O control operations.
```
__________________________________________________
### _ISATTY_
```
int isatty(int fd);
```

- Check whether a given file descriptor refers to a terminal.

**Return Value:**
- Success: 1 if the file descriptor refers to a terminal
- Error: 0, errno is set to indicate the error
____________________________________
### _TTYNAME_
```
function
```
 - 
  
**Return Value:**
- Success:
- Error:
_____________________________________
### _IOCTL_
```
function
```
 - 
 
**Return Value:**
- Success:
- Error:
___________________