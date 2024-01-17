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
function
```
 
**Return Value:**
- Success:
- Error: