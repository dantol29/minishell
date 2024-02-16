add NEW TODO's to the TOP. []=todo [x] = done

Start minishell: make && ./minishell

Bonus
[ ] Use &&, || and parenthesis with commands and ensure minishell behaves the same way bash does.
[ ] Use wildcards in arguments in the current working directory.
[X] Surprise! (or not...) Set the USER environment variable.
[X] echo "'$USER'" should print the value of the USER variable.
[X] echo '"$USER"' should print "$USER".

Optional
[ ] x=y    echo $x     y  (local variables)
[ ] export in alphabetical order

16.02
[ ] exit code 130 after cat
[ ] exit code 130 after heredoc
[ ] when ctrl+c is pressed after blocking command (cat) minishell$ is displayed 2 times
[X] exit 42 42 (mini: exit: too many arguments) (Alena)
[x] cd ".""."
[x] cd ".""/"".""."
[x] cd $PWD hi (msini: cd: too many arguments) (Alena)
[ ] clean memory  in redirections

15.02
[x] /bin/ls "-l" "-a"
[x] echo $?HELLO
[x] cat <<EOF | grep "ABC" ()
    > ABC
    > EOF
    ABC
[x] export GHOST=123 | env (segfault)
[x] CLEANNNN FREAKING memory !!!!!!!
[x] separate exit to exit.c
[x] exit code 130 works after ctrl+c
[x] < Makefile
[x] space before echo
[x] ls | cat << A | wc -l
[x] ls | cat << A | cat <<B | wc -l
[x] cat << A | wc -l 
[x] <<A <<B multiple heredocs (almost works) (<< : command not found)

14.02
[x] wc -l <<A
[x] << A, cat << A (basic heredoc working)
[x] cat << A | wc -l (working, but exits)
[x] minishell $ cd abc | cd def 

13.02
[x] A LOT of memory cleaned !!
[x] count and save heredocs
[x] $EMPTY echo a
[x] $? echo a
[x] heredoc: start rewriting, finds all eof, can write in tmp_heredoc.txt(need to add launch cmd)

12.02
[x] memory cleaning
[x] find a lot of bugs for heredoc

11.02
[x] cat << A
	> "$USER"	
	> '$USER'
	> A
	"dtolmaco"
	'dtolmaco'
[x] heredoc ctrl+c
[x] heredoc ctrl+\
[x] export hello , export =, export 123, export GHOST=123 | env | grep GHOST (exit code 1)
[x] cd $PWD, cd $OLDPWD, cd 123123
[x] exit hello (exit code 2), exit 42 world (exit code 1)
[x] echo $
[x] echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<" 

10.01
[x] wc -l < 2.txt > 4.txt
[x] >> redirect output in append mode
[x] < redirect input :)))))

09.01
[x] ctrl-\ does nothing
[x] ctrl+c exit heredoc (130)
[x] ls "" "-l" "-a" (ls: cannot access '': No such file or directory)
[x] awk '{print $1}' Makefile

08.01
[x] norminette code cleaning
[x] syntax error - exit code 1
[x] export ls="ls -l -F"
[x] unset PATH - commands should not work

29.01 - 07.01 // holidays

28.01
[x] divide split_pipe function
[x] exit - exit from parent process
[x] echo "cat lol.c | cat > lol.c"
[x] PIPES!!!! :)))))))
https://github.com/dantol29/minishell.git+


27.01
[x] > redirect output
[x] exit errors (non-integer arguments, too many arg)
[x] echo $USER$USER
[x] expr $USER$USER
[x] expr $? + $?

26.01
[x] exit code 130 after ctrl+c
[x] "/bin/ls" '/bin/ls' "/bin/ls" "-l""a"
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
