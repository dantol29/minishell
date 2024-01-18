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
#include <readline/readline.h>
#include <readline/history.h>

void rl_clear_history(void);
```

- Is used to clear the history list maintained by Readline.

**Return Value:**
- Success: void
- Error: void
____________________________________
###  _RL_ON_NEW_LINE_
```
#include <readline/readline.h>
#include <readline/history.h>

void rl_on_new_line();
```

 - The prompt will be displayed on a new line before the user's input.
 - If is not set, the prompt is typically displayed on the same line as the input.

**Return Value:**
- Success: void
- Error: void
____________________________________
###  _RL_REPLACE_LINE_
```
#include <readline/readline.h>

void rl_replace_line(const char *text, int clear_undo);
```

- Is used to replace the current input line with a new line.

**Return Value:**
- Success: void
- Error: void
____________________________________
### _RL_REDISPLAY_
```
#include <readline/readline.h>

void rl_redisplay(void);
```

- Is used to refresh the display of the current input line.

**Return Value:**
- Success: void
- Error: void
____________________________________
###  _ADD_HISTORY_
```
#include <readline/readline.h>
#include <readline/history.h>

void add_history(const char *line);
```

- Is used to add a line to the history list.
- The history list in Readline keeps track of previously entered command lines, allowing users to recall and re-execute them.

**Return Value:**
- Success: void
- Error: void
