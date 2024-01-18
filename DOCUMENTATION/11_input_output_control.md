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
- tests whether fd is an open file descriptor referring to a terminal.

**Return Value:**
- Success: 1 if the file descriptor refers to a terminal
- Error: 0, errno is set to indicate the error
____________________________________
### _TTYNAME_
```
function
```
 - return name of a terminal
  
**Return Value:**
The return value may point to static data, possibly overwritten by the next call.

- Success:
    - returns a pointer to the null-terminated pathname of the terminal device
     that is open on the file descriptor fd,
     
- Error: NULL  (for  example,  if    fd is not connected to a terminal). 
       - EBADF  Bad file descriptor.

       - ENODEV fd refers to a slave pseudoterminal device but the corresponding pathname could
              not be found (see NOTES).

       - ENOTTY fd does not refer to a terminal device.

       - ERANGE (ttyname_r()) buflen was too small to allow storing the pathname.

_____________________________________
### _IOCTL_
```
function
```
 - control device
- The ioctl() system call manipulates the underlying device parameters of special files.
- In particular, many operating characteristics of character special files
  (e.g., terminals)  may  be controlled with ioctl() requests.
- The argument fd must be an open file   descriptor.

- The second argument is a device-dependent request code.
- The third argument is an  untyped  pointer  to memory.
It's traditionally char *argp (from the days before void * was valid C),
and will be so named for this discussion.

- An ioctl() request has encoded in it whether the argument is an in  parameter  or  out parameter,
and  the  size  of the argument argp in bytes.
Macros and defines used in specifying an ioctl() request are located in the file <sys/ioctl.h>.  


 
**Return Value:**
- Success: 0;
        - A few ioctl() requests use the return value  as
          an  output  parameter  and return a nonnegative value on success. 
- Error: -1 and errno is set appropriately.

       EBADF  fd is not a valid file descriptor.

       EFAULT argp references an inaccessible memory area.

       EINVAL request or argp is not valid.

       ENOTTY fd is not associated with a character special device.

       ENOTTY The specified request does not apply to the kind of object that  the  file  de‐
              scriptor fd references.

___________________