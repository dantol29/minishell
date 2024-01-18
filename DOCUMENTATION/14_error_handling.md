###         14.      ERROR HANDLING
```
52. strerror;       // Get a descriptive string for an error code.
53. perror;         // Print a descriptive error message.
```
_____________________________________________________________
### _STRERROR_ 
```
function
```
- return string describing error number
- The strerror() function returns a pointer to a string that describes the  error
 code  passed in the argument errnum, possibly using the LC_MESSAGES part of the
current locale to select the appropriate language.

- 
 
**Return Value:**
- Success:
    - return  the  appropriate error description string,
        or an "Unknown error nnn" message if the error number is unknown.

- Error:
       - EINVAL The value of errnum is not a valid error number. ("Invalid argument".)

       - ERANGE Insufficient storage was  supplied  to  contain  the  error  description string.
        - this string must  not be modified by the application,
             but may be modified by a subsequent call to strerror().
        - No other library function, including perror(3), will modify this string.
___________________________
### _PERROR_
```
void perror(const char *s);
```
-  print a system error message
 - produces a message on standard error
 describing the last error encountered during a call 
 to a system or library  function.
- First (if s is not NULL and *s is not a null byte ('\0')),
    the argument   string s is printed, followed by a colon and a blank.
- Then  an  error message corresponding to the current value of errno and a new-line.
- To  be  of most use, the argument string should include the name of the
    function that incurred the error.
 
**Return Value:**
- Success: Note  that errno is undefined after a successful system call or library function call:
    this call may  well change this variable, even though  it  succeeds,
    for  example  because  it internally used some other library  function that failed.
    Thus, if a failing call is not immediately  followed by a call to perror(),
    the value of errno should be saved.

- Error: When  a  system call fails, it usually returns -1 and sets the   variableerrno to a value describing what went  wrong.
(These  values  can  be   found in <errno.h>.) 
________________________________________________________________--