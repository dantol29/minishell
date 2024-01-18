### 4.      FILE OPERATIONS
```
11. access;         // Check file accessibility.
12. open;           // Open a file.
13. read;           // Read from a file.
14. close;         // Close a file.
15. unlink;         // Delete a file.
```
_______________________________________________
### _ACCESS_
```
int access(const char *pathname, int mode);
```
- Checks  whether the calling process can access the file pathname. 0 is default mode.  
- Can the user who invoked me read/write/execute this file?

**Return Value:**
- Success: 0
- Error: -1 is returned, and  errno is set appropriately.
____________________________________________________
### _OPEN_
```
#include <fcntl.h>

int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);

```
- Opens a file descriptor.
 
**Return Value:**
- Success:
- Error:
____________________________________
### _READ_
```
ssize_t read(int fd, void *buf, size_t count);
```

 - read() attempts to read up to count bytes from file descriptor   fd into the  buffer starting at buf.
 - On files that support seeking, the read operation commences at  the  file offset,
    and  the  file offset is incremented by the number of bytes read.
    If the file offset is at or past the end of file, no bytes are  read,  and
    read() returns zero.
-  If  count  is  zero, read() may detect the errors described below.  In the
    absence of any errors, or if read() does not check for  errors,  a  read()
    with a count of 0 returns zero and has no other effects.
-   According  to  POSIX.1,  if count is greater than SSIZE_MAX, the result is
    implementation-defined; see NOTES for the upper limit on Linux.

 
**Return Value:**
- Success:
     - number of bytes read is returned (zero  indicates  end  of file),
    and the file position is advanced by this number.
    - It is not an error if this number is smaller than the number of bytes requested;
     this may happen  for  example  because fewer bytes are actually available right now
    (maybe because we were close to end-of-file, or  because  we  are  reading
     from  a  pipe, or from a terminal), or because read() was interrupted by a signal.  See also NOTES.

- Error:
   -  On error, -1 is returned, and errno is set appropriately.  In  this  case,
    it is left unspecified whether the file position (if any) changes.
____________________________________
### _CLOSE_
```
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
________________________________________________________
### _UNLINK_
```
#include <unistd.h>

int unlink(const char *pathname);
```
- Is used to delete the file.

**Return Value:**
- Success: 0
- Error: -1
