[x] expr
	expr: missing operand

[ ]	expr +  $? + 2
	4

[ ] expr $? + + 2
	2

[x] expr - $? + 2
	expr: syntax error: unexpected argument ‘0’

[ ]	 expr -2+$?
	-2+0

[ ]  expr + + + + $? + 2
	expr: non-integer argument

[ ]  expr $USER
	dtolmaco

[ ] expr $USER  $USER
	expr: syntax error: unexpected argument ‘dtolmaco’

[ ]  expr abc
	abc

[ ] expr + abc
	abc

[ ] expr + abc
	abc