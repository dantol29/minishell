###      10.    TERMINAL HANDLING
```
36. tcsetattr; // Set terminal attributes.
37. tcgetattr; // Get terminal attributes.
38. tgetent; // Get terminal capabilities.
39. tgetflag; // Get terminal flag.
40. tgetnum; // Get terminal number.
41. tgetstr; // Get terminal string.
42. tgoto; // String capabilities for cursor positioning.
43. tputs; // Output terminal capabilities.
44. ttyslot; // Get slot in the utmp file.
```
____________________________________
### _TCSETATTR_
```
int tcsetattr(int fd, int optional_actions, 
                      const struct termios *termios_p);
```
- Gets the terminal attributes.
- Usage: Retrieves the current terminal settings, often used before modifying the settings with tcsetattr.  
 - The  termios  functions describe a general terminal interface
 that is provided to control asynchronous communications ports.

- described here have a termios_p argument that is a pointer to  a  termios structure,that at least the following members:
```

           tcflag_t c_iflag;      /* input modes */
           tcflag_t c_oflag;      /* output modes */
           tcflag_t c_cflag;      /* control modes */
           tcflag_t c_lflag;      /* local modes */
           cc_t     c_cc[NCCS];   /* special characters */
```

    The  values  that may be assigned to these fields are described below.
    In the case of   the first four bit-mask fields, the definitions of some of the associated  flags
    that   may   be   set   are  exposed  only  if  a  specific  feature  test  macro
    (see  feature_test_macros(7)) is defined, as noted in brackets ("[]").
-   Use: Used to modify terminal attributes. For example, it can be used to set the terminal to raw mode, disabling canonical processing and echoing.
 ```
 #include <termios.h>

int main() {
    struct termios term;
    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        perror("tcgetattr");
        return 1;
    }

    // Modify the terminal attributes as needed, e.g., set to raw mode.

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) == -1) {
        perror("tcsetattr");
        return 1;
    }

    return 0;
}
 ```
**Return Value:**
- Success: 0, success if any of the requested changes could be successfully carried out.
    - Therefore, when making multiple changes it may be necessary 
    to follow  this  call  with  a further call to tcgetattr() 
     to check that all changes have been performed successfully.
- Error: -1     on failure and set errno to indicate the error.

____________________________________
### _TCGETATTR_
```
int tcsetattr(int fd, int optional_actions,
                     const struct termios *termios_p);

```
-  Gets the terminal attributes.
-  Usage: Retrieves the current terminal settings, often used before modifying the settings with tcsetattr.
 -   The  termios  functions describe a general terminal interface that is provided to control asynchronous communications ports.
- uses the same termios structure as tcsetattr
- Retrieves the current terminal attributes associated with a given file descriptor.


**Return Value:**
- Success: 0
- Error: -1     on failure and set errno to indicate the error.
____________________________________
### _TGETENT_
```
int tgetent (char *bp, const char *name);
```
- Initializes the termcap database.
- Usage: Essential for programs requiring knowledge of terminal capabilities. bp is a buffer that receives the termcap entry.
 - The tgetent subroutine looks up the termcap entry for name, The emulation ignores the buffer pointer bp.
 
**Return Value:**
- Success: Returns 1 for success, 
            0 if the terminal is not found, 
- Error:  -1
____________________________________
### _TGETFLAG_
```
int tgetflag(const char *id);
```
- The tgetflag subroutine gets the boolean entry for id.
- Checks if a specific boolean capability is supported.
- Usage: Determines if a certain feature is available in the terminal's capabilities.
 
**Return Value:**
- Success: 1 if the capability is present
- Error: 0
____________________________________
### _TGETNUM_
```
int tgetnum(const char *id);
```
 - The tgetnum subroutine gets the numeric entry for id.
 - Retrieves numeric values related to terminal capabilities.
- Usage: Useful for obtaining information like the number of columns in the terminal.
 
**Return Value:**
- Success: the numeric value for the capability
- Error: -1 if not found.
____________________________________
### _TGETSTR_
```
char *tgetstr(const char *id, char **area);
```
- Retrieves string values related to terminal capabilities.
- Usage: Commonly used for obtaining escape sequences for specific actions, such as clearing the screen.
 - The tgetstr subroutine gets the string entry for id. If area is not a null pointer and does not point to a null pointer, the tgetstr subroutine copies the string entry into the buffer pointed to by *area and advances the variable pointed to by area to the first byte after the copy of the string entry.
 
**Return Value:**
- Success: string for the capability,
- Error: NULL if not found.
____________________________________
### _TGOTO_
```
char *tgoto(const char *cm, int col, int row);
```
- The tgoto subroutine instantiates the parameters col and row into the capability cap and returns a pointer to the resulting string.
- Generates cursor addressing sequences based on parameters.
- Usage: Constructs sequences to position the cursor at specific locations on the screen.
**Return Value:**
- Success: OK || Returns the constructed sequence.
- Error: ERR.
____________________________________
### _TPUTS_
```
int tputs(const char *str, int affcnt, int (*putc)(int));
```
- Outputs strings to the terminal, interpreting termcap codes.
- Usage: Sends terminal-specific sequences, like clearing the screen, to achieve visual effects.
 
**Return Value:**
- Success: Returns the number of characters written
- Error: -1
____________________________________
### _TTYSLOT_
```
int ttyslot(void);
```
 - Determines the slot number of the user's terminal in the utmp file.
- Usage: Identifies the user's terminal and obtains related information.
 
**Return Value:**
- Success: the slot number
- Error: -1