add NEW TODO's to the TOP. []=todo [x] = done
info about exit codes https://www.redhat.com/sysadmin/exit-codes-demystified
ctr+c - exit code 130
command not found - exit code 127
error - exit code 1
success - exit code 0

27.01
[ ] ctrl-\ does nothing
[ ] check heredoc with pipe/pipes
[ ] check if gnl has to be in the libft

26.01
[ ] < redirect input
[ ] > redirect output
[ ] >> redirect output in append mode
[ ] cat >> file.txt | cat >> bla.txt only first redirection is done
[ ] echo $? + $? (expr)
[ ] divide split_pipe function
[x] exit code 130 after ctrl+c
[x] "bin/ls" '/bin/ls'
[x] if just export print all env
[x] if something after env return error
[x] add \0  for ft split_pipes for substrings[j](array of arrays)
[x] stop cat after cat << A

25.01
[x] exit code 1 (error)
[x] exit code 0 (success)
[x] exit code 127 (command not found)
[x] echo $?
[x] cat << A (print everything that is entered)
[x] cat << A file.txt (print only file.txt)
[x] check if command exists between pipes
[x] split pipes


24.01
[x] divide line between pipes and save in substrings
[x] heredoc error handling
[x] quotes logic for commands "echo a"
[x] check and count pipes

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
