### VARIABLES
#     check:
```
    "e"c"h"o      '-n'     "$USER hello" '$USER' $USER "world\""
```
 # CHECK IF BUILTIN
type -a echo
echo is a shell builtin
echo is /usr/bin/echo
echo is /bin/echo


# ECHO
echo$USER
minishell: command not found: echodtolmaco

# SET / UNSET VARIABLE

 - setvatiable:  export TEST=test
 - find variable: env | grep test
 - output: TEST=test
 - delete variable:  unset TEST
 -  env | grep test

 # VALID $VAR
 - "$USER"
 a-z A-Z 1-9 _  valid symols
 bla$VAR (bla$VAR)

 #  NOT VALID
  _ VAR (_ in begin)

 #TEXT
 //OK
 echo '$BLABLA'
$BLABLA

//OK
echo "$USER jhjhjvhjvgjg"
akurmyza jhjhjvhjvgjg

//OK
 echo "$USER'' " jhjhjvhjvgjg
akurmyza''  jhjhjvhjvgjg



  /*
	// start checking in both directions, before and after variable    "<--$VAR-->"
	  abcd "$USER    fsdgsd"
	VALID:
		$VAR
		"$VAR"
		"'$VAR"
	
	NOT_VALID:
		$USEr (Small letter) Retturn: empty line 
*/

//OK
echo "'"$USER"'"
'dtolmaco'

//OK
echo "abc$fgfgfgfgf dfdfdfd"
abc dfdfdfd

//OK
echo $USER $USER
dtolmaco dtolmaco

//OKs
 echo      a            b         USER
a bSER

//OK
echo -n '"abc'"
minishell: error while looking for matching quote




//OK
//    \=1 \\=1 \\\=2 \\\\=2 \\\\\=3
echo "we\\n"
we\n


//OK
echo "Hello$World!"
Hello!

//OK
echo '1\\2'
1\\2

//OK
echo '1\\2'
1\\2

//OK
echo b\"
b"

// OK
echo Hello \"World\"!
Hello "World"!

// OK
"ec""ho" 1234
1234

// OK
"ec" "ho" 1234
ec: command not found

//OK
echo
newline

// OK
echo -n, "-n", '-n'
no newline

// OK
echo "-n "
-n 

// OK
echo "hello \"world\""
hello "world"

// OK
echo "Hello\nWorld!"
Hello\nWorld!

// OK
echo Hello\nWorld!
HellonWorld!

// OK
echo \"
"

// OK
echo "-n" "-n"

// OK
echo "-n""-n"
-n-n

// OK
echo "-n" " -n"
 -n

// OK
echo " -n" "-n"
 -n -n

// OK
echo -nnnnnnnnnnnnn

// OK
echo "-n -n -n"
-n -n -n

// OK
echo -n -n -n -n