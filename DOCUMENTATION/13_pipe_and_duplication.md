###      13.      PIPE AND DUPLICATION
```
49. dup;       // Duplicate a file descriptor.
50. dup2;        // Duplicate a file descriptor to a specific descriptor number.
51. pipe;       // Create a pipe for interprocess communication.
```
________________________________________________________________
### _DUP_
```
int dup(int oldfd);
```
- Creates a copy of the file descriptor `oldfd`.
- Uses the lowest-numbered unused file descriptor for the new one.
- Both old and new descriptors refer to the same open file.
- They share file offset and status flags.
- Duplicate descriptor does not have the close-on-exec flag set.

**Return:**
- Success:  new file descriptor.
- Error:    -1, and `errno` is set appropriately.
___________________________________________________________
### _DUP2_      
```
int dup2(int oldfd, int newfd);
```
- Creates a copy of the file descriptor `oldfd` using the specified `newfd`.
- If `newfd` was previously open, it is closed before reuse.
- Closing and reusing `newfd` are performed atomically to avoid race conditions.

**Note:**
- If `oldfd` is not valid, the call fails, and `newfd` is not closed.
- If `oldfd` and `newfd` have the same value, `dup2()` does nothing and returns `newfd`.

**Return Value:**
- Success: Returns the new file descriptor.
- Error: Returns -1, and `errno` is set appropriately.

_____________________________________________________________
### _PIPE_
```
int pipe(int pipefd[2]);
```
- Creates a unidirectional data channel (pipe) for interprocess communication.
- Returns two file descriptors in the array `pipefd` (read end: `pipefd[0]`, write end: `pipefd[1]`).
- Data written to the write end is buffered until read from the read end.

**Return Value:**
- Success:  0.
- Error:  -1, `errno` is set appropriately, and `pipefd` is unchanged.