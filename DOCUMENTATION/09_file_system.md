###     9.      FILE SYSTEM
```
34. getcwd;         // Get the current working directory.
35. chdir;   // Change the current working directory.
```
____________________________________
### _GETCWD_
```
char *getcwd(char *buf, size_t size);
```

- Copies an absolute pathname of the current working directory to the array pointed to by buf, which is of length size.

**Return Value:**
- Success: a null-terminated string containing an absolute pathname of the current working directory
- Error: NULL, errno set appropriately
____________________________________
### _CHDIR_
```
int chdir(const char *path);
```
- changes the current working directory of the calling process to the directory specified in path.


**Return Value:**
- Success: 0
- Error: -1 is returned, and errno is set appropriately.
ERRORS
       Depending on the filesystem, other errors can be returned.  The more general errors for chdir()
       are listed below:

       EACCES Search permission is denied for one of the components of path.  (See  also  path_resolu‐
              tion(7).)

       EFAULT path points outside your accessible address space.

       EIO    An I/O error occurred.

       ELOOP  Too many symbolic links were encountered in resolving path.

       ENAMETOOLONG
              path is too long.

       ENOENT The directory specified in path does not exist.

       ENOMEM Insufficient kernel memory was available.

       ENOTDIR
              A component of path is not a directory.

       The general errors for fchdir() are listed below:

       EACCES Search permission was denied on the directory open on fd.

       EBADF  fd is not a valid file descriptor.

       ENOTDIR
              fd does not refer to a directory.
