[x] expr
	expr: missing operand

[x]	expr +  $? + 2
	4

[x] expr $? + + 2
	2

[x] expr - $? + 2
	expr: syntax error: unexpected argument ‘0’

[x]	 expr -2+$?
	-2+0

[x]  expr + + + + $? + 2
	expr: non-integer argument

[x]  expr $USER
	dtolmaco

[x] expr $USER  $USER
	expr: syntax error: unexpected argument ‘dtolmaco’

[x]  expr abc
	abc

[x] expr + abc
	abc
