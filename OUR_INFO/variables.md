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

 #TEXT
 echo '$BLABLA'
$BLABLA
echo '$BLABLA'
$BLABLA
echo "$USER jhjhjvhjvgjg"
akurmyza jhjhjvhjvgjg

 echo "$USER'' " jhjhjvhjvgjg
akurmyza''  jhjhjvhjvgjg

echo "$USER'' " jhjhjvhjvgjg "$USER"
akurmyza''  jhjhjvhjvgjg akurmyza

 #NOT VALID
  _VAR