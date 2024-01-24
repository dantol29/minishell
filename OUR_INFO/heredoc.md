

# VALID heredoc

[x] minishell$ <<A
[x] echo <<             A			//  END: A (without spaces) 


[x] echo <<A $USER
	heredoc> A
	dtolmaco


## NOT VALID 
[x] """ echo <<A
[x]  <<"
[x] echo " <<A
[x] echo  <<A     "				    //  END = |A     "| 
[X] echo <<"A"						// Error?
[x] '<<>>' "<<" (text)
[ ] if heredoc with multiple pipes
[x] if heredoc inside the quotes
[x] "echo <<A" minishell: error while looking for matching quote
[x]	a << A						//starts heredoc, print command not found for a
	heredoc> A
	zsh: command not found: a

[ ]echo <<< | echo <<A			//bash: syntax error near unexpected token `|'
[ ] echo <<A | echo <<<
		> A
		bash: syntax error near unexpected token `newline'








