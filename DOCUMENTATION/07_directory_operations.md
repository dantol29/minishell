###      7.      DIRECTORY OPERATIONS
```
28. opendir;        // Open a directory.
29. readdir;        // Read a directory entry.
30. closedir;       // Close a directory.
```
________________________________________________

### _OPENDIR_
```
DIR *opendir(const char *name);
```
- opens a directory stream corresponding to the directory name,
and returns a pointer to the directory stream.  
- The stream is positioned at the first entry in the directory.

**Return Value:**
- Success:  a pointer to the directory stream.
- Error: NULL is returned,  and  errno  is set appropriately.
_________________________________________________________________
### _READDIR_
```
struct dirent *readdir(DIR *dirp);
```
- The  readdir()  function returns a pointer to a dirent structure
    representing the next directory entry in the directory stream pointed to by dirp
- In the glibc implementation, the dirent structure is defined as follows:
```

           struct dirent {
               ino_t          d_ino;       /* Inode number */
               off_t          d_off;       /* Not an offset; see below */
               unsigned short d_reclen;    /* Length of this record */
               unsigned char  d_type;      /* Type of file; not supported
                                              by all filesystem types */
               char           d_name[256]; /* Null-terminated filename */
           };
```
**Return Value:**
- Success: a pointer to a dirent structure.
            (This  structure  may  be statically allocated; do not ttempt to free(3) it.)        
            If  the end of the directory stream is reached, NULL is returned and errno is not changed.
- Error:  NULL is returned and errno is set appropriately.
         To  distinguish  end   of  stream  from  an  error, set errno to zero before calling readdir()
            and then check the  value of errno if NULL is returned.
_________________________________________________
### _CLOSEDIR_
```
function
```
-
 
**Return Value:**
- Success:
- Error: