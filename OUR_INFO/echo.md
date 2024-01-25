### VARIABLES
#     check:
```
    "e"c"h"o  '-n'   "$USER hello" '$USER' $USER "world\"" $?hello
```
## CHECK COMMAND IF it is BUILTIN
# type -a echo
# echo is a shell builtin
# echo is /usr/bin/echo
# echo is /bin/echo


# ECHO

[x] "echo a"                        $echo a: command not found

# SET / UNSET VARIABLE

# export TEST=test    		//set vatiable  
# env | grep test   		 //find variable:
# TEST=test         		 //output:
# unset TEST 				//delete variable:
# env | grep test			//check if variable was deleted

### VALID  VARIABLES: $VAR$VAR  "$VAR"	"'$VAR" must exist in ENV
###	a-z ||  A-Z || 1-9 ||  '_'  valid symols 
[x]  hello$VAR									$bla$VAR							
[x] "$USER"										$akurmyza
[x] echo '$BLABLA'								$BLABLA

#  NOT VALID VARIABLES: 
[x] _ $USER (_ in begin)						$_akurmyza: command not found
[x]$USEr (Small letter, not the same as valid $USER from env)  //  Retturn without empty line 
[x] HELLO$USER									$HELLOakurmyza: command not found
[x] echo "Hello$World!"							$Hello!
 
 # OUR TESTS
[x] echo "$USER jhjhjvhjvgjg"					$akurmyza jhjhjvhjvgjg
[x] echo "$USER'' " jhjhjvhjvgjg				$akurmyza''  jhjhjvhjvgjg
[x] echo "'"$USER"'"							$'dtolmaco'
[X] echo "abc$fgfgfgfgf dfdfdfd"				$abc dfdfdfd
[x] echo $USER $USER					 		$dtolmaco dtolmaco
[x]  echo      a         b       USER			$a bSER
[x] echo -n '"abc'"								$minishell: error while looking for matching quote

##  VALID ECHO = "EC""HO" = "E""CHO" 
[x] "ec""ho" 1234								$1234
[x] "ec" "ho" 1234								$ec: command not found

## "INSIDE DOUBLE QUOTES ALWAYS WRITE ALL"
[x] echo "Hello\nWorld!"						$Hello\nWorld!

## WRITE SIGN AFTER SLASH \ (\"= $ " )
[x] echo b\"									$b"
[x] echo Hello \"World\"!						$Hello "World"!
[x] echo "hello \"world\""						$hello "world"
[x] echo Hello\nWorld!							$HellonWorld!
[x]  \"											$"

##  WRITE SLASH AFTER SLASH \  \=1 \\=1 \\\=2 \\\\=2 \\\\\=3
[x] echo "we\\n"								$we\n
[x] echo '1\\2'									$1\\2
[x] echo '1\\2'									$1\\2

##  NEWLINE MUST BE ALWAYS 
[x] echo										$newline

## NO NEWLINE -n = NO NEWLINE AFTER IMPUT
[x] echo -n, "-n", '-n'							$no newline
[x] echo "-n "									$-n 
[x] echo "-n" "-n"								$
[x] echo "-n""-n"								$-n-n
[x] echo "-n" " -n"								$-n
[x] echo " -n" "-n"							    $-n -n
[x] echo -nnnnnnnnnnnnn							$
[x] echo "-n -n -n"								$-n -n -n
[x] echo -n -n -n -n