### 2.       INPUT / OUTPUT
```
7. printf;          // Print formatted output to the standard output.
8. write;           // Write to a file descriptor.
```
___________________________________________________________
### _PRINTF_
```
#include <stdio.h>

int	ft_printf(const char *format, ...);
```
- Prints information on the STDOUT

**Return Value:**
- Success: number of bytes written
- Error: -1
____________________________________
### _WRITE_
```
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
```
- Writes characters to the file descriptor

**Return Value:**
- Success: number of bytes written
- Error: -1
_____________________________________________
