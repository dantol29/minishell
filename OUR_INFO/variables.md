### VARIABLES

-

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
