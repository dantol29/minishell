

# VALID heredoc

[x] minishell$ <<A
[x] echo <<             A			//  END: A (without spaces) 


[x] echo <<A $USER
	heredoc> A
	dtolmaco


## NOT VALID 
[ ] if heredoc with multiple pipes
[x] cat "<< <<" A
[x] """ echo <<A
[x]  <<"
[x] echo " <<A
[x] echo  <<A     "				    //  END = |A     "| 
[X] echo <<"A"						// Error?
[x] '<<>>' "<<" (text)
[x] if heredoc inside the quotes
[x] "echo <<A" minishell: error while looking for matching quote
[x]	a << A						//starts heredoc, print command not found for a
	heredoc> A
	zsh: command not found: a

[ ]echo <<< | echo <<A			//bash: syntax error near unexpected token `|'
[ ] echo <<A | echo <<<
		> A
		bash: syntax error near unexpected token `newline'

[ ] Current: ($ exit 42 42) completely exit from minishell
	$ exit 42 42
	exit
[ ] exit 42 42 (too many arguments)



## CAT AND HEREDOC -  prints  strings, after exit heredoc

[x] our_github_minishell cat <<A
    heredoc> dsaf
    heredoc> fsdaf
    heredoc> 111111111111
    heredoc> A
    dsaf
    fsdaf
    111111111111

[ ] CMD heredoc not working
[ ] heredoc  with pipes not working
[ ] <<A heredoc is not working (our: command not found)




