###     8.          FILE INFORMATION
```
31. stat;         // Retrieve file information.
32. lstat;        // Retrieve file information (follows symbolic links).
33. fstat;        // Retrieve file information (from an open file descriptor).
```
____________________________
### _STAT_
```
int stat(const char *pathname, struct stat *statbuf);

```
- man 2 stat
- display file or file system status
- return information about a file, in the buffer pointed to by statbuf. 
- No permissions are required on the file itself,
  but permission is required on all of the directories in pathname that lead to the file.
- retrieve information about the file pointed to by pathname;

 
**Return Value:**
- Success: 0
- Error: -1 is returned, and errno is set appropriately
____________________________________
### _LSTAT_
```
int lstat(const char *pathname, struct stat *statbuf);
```
- man 2 lstat
-  lstat() is identical to stat(), except that if pathname is a symbolic link, then it returns information about the link itself, not the file that the link  refers  to. 
- No permissions are required on the file itself,
  but permission is required on all of the directories in pathname that lead to the file.
**Return Value:**
- Success: 0
- Error: -1 is returned, and errno is set appropriately
____________________________________
### _FSTAT_
```
 int fstat(int fd, struct stat *statbuf);
```
- man 2 fstst
-  return information about a file, in the buffer pointed to by statbuf. 
- No permissions are required on the file itself, 
     but permission is required on all of the directories in pathname that lead to the file.

- retrieve information about the file pointed to by pathname; 
- fstat() is identical to stat(), except that the file about which information is to be retrieved is specified by the file descriptor fd.


**Return Value:**
- Success: 0
- Error: -1 is returned, and errno is set appropriately