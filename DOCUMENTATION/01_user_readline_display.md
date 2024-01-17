###     1.      USER INTERACTION (Readline and Display)_
```
1. readline;             // Read a line of input using the Readline library.
2. rl_clear_history;     // Clear the history list for the current readline session.
3. rl_on_new_line;       // Notify Readline that the cursor has moved to a new line.
4. rl_replace_line;      // Replace the contents of the current Readline line.
5. rl_redisplay;        // Force Readline to re-display the current input line.
6. add_history;         // Add a line to the Readline history.

```
____________________________________
###  _READLINE_
```
char *readline(const char *prompt);
```

- Read a line from the terminal and return it, using prompt as a prompt.  
- If prompt is NULL or the empty string, no prompt is issued.

**Return Value:**
- Success: the text of the line read
- Error: NULL
_______________________________________________________
###  _RL_CLEAR_HISTORY_
```
function
```
_rl_clear_history_

**Return Value:**
- Success:
- Error:
____________________________________

###  _RL_ON_NEW_LINE_
```
function
```
_rl_on_new_line_

**Return Value:**
- Success:
- Error:
____________________________________

###  _RL_REPLACE_LINE_
```
function
```
 _rl_replace_line_ 

**Return Value:**
- Success:
- Error:
____________________________________
### _RL_REDISPLAY_
```
function
```
_rl_redisplay_
**Return Value:**
- Success:
- Error:
____________________________________
###  _ADD_HISTORY_
```
function
```

**Return Value:**
- Success:
- Error: