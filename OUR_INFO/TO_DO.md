add new TODO's from beginning. []=todo [x] = done

[ ] Not interpret unclosed quotes or special characters which are not required by the
        subject such as \ (backslash) or ; (semicolon).
[ ] ; semicolon 
[ ] exitocde Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
[ ] ctrl-\ does nothing.

24.01
[ ] check if gnl has to be in the libft
[ ]	echo $?
[ ] Fix history
[ ] cat << (prints what was entered)
[ ] exit code  https://www.redhat.com/sysadmin/exit-codes-demystified
# Heredoc
[ ] '>>' ">>"
[ ] if heredoc with multiple pipes
[ ] if heredoc inside the quotes
# PIPE
[ ] is real pipe |
[ ] echo | - error
[ ] ||
[ ] "|" '|'
[ ] change ft check_pipe_symbol(char *line). 
        To check if it is real pipe. Not : double ||, that is some command between, if it is not in "|"
[ ] echo asdvs |     (error)

23.01
[x] echo. no empty space after invalid $VAR
[x] Make cd function (save old pwd, new pwd), cd -, cd ~, cd ..
[x] ctrl+c signal
[x] gfgffgfgf: command not found
[x] error handling with perror, strerror and errno
[x] << (heredoc)
[x] echo << EOF AAAAAAAAAAAAAAAAAAA(after executing, prints AAAAAAAAAAAAAAAAAAa on the new line)
[x] organize echo.md

22.01
[x] pwd
[x] export
[x] print env
[x] unset  with no options
[x] echo -n || echo -n -n || echo -nnnnnnnn  -must display only new line
[x] /bin/echo (absolute path)
[x] Search and launch the right executable (ls, pwd, /bin/ls, /bin/pwd)


21.01
[x] print no line (write (1, "", 1);)
[x] echo -n, "-n", '-n'
[x] if just echo print a newline
[x] return new line if empty arguments
[x] "ec"ho" edge case
[x] \\ edge case
[x] \" edge case echo b\"
[x] echo skip empty space
[x] echo -n 
[x] Display proper error message echo (invalid command)
[x] Check if a quote is closed (error if not)
[x] Add .gitignore

20.01
[x]  read input, find $VAR, check if valid Variables (valid: "$USER", "'$USER'")

19.01
[x] free day


18.01

[x] complete adding library
[x] run simple commands with absolute path (e.g. /bin/ls, ../bin/ls)
[x] 01_finish writing documetation
[x] 02_finish writing documetation
[x] 03_finish writing documetation
[x] 04_finish writing documetation
[x] 05_finish writing documetation
[x] 06_finish writing documetation
[x] 07_finish writing documetation
[x] 08_finish writing documetation
[x] 09_finish writing documetation
[x] 10_finish writing documetation
[x] 11_finish writing documetation
[x] 12_finish writing documetation
[x] 13_finish writing documetation
[x] 14_finish writing documetation


17.01

[x] changing readmefile.md: made categories and sorted all 53 functions, 
[x] added MISSED function: SIGACTION,
[x] added header to header file
[x] made folder documentation and moved all function there, devided it in 14 files
[x] add header from all functions to minishell.h
[x]  organize  functions in library
[x] run simple commands without a path (e.g. ls, cat, grep, etc…)