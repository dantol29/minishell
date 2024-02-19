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

### Arithmetic Operations:
# Addition
expr 10 + 5

# Subtraction
expr 20 - 8

# Multiplication
expr 6 \* 3   # * is a special character, so it needs to be escaped with \

# Division
expr 24 / 4

# Modulus (Remainder)
expr 17 % 4

### Comparison:

# Equal to
expr 5 = 5

# Not equal to
expr 10 != 7

# Greater than
expr 15 \> 10   # > is a special character, so it needs to be escaped with \

# Less than
expr 12 \< 20   # < is a special character, so it needs to be escaped with \

### String Operations:
# Concatenation
expr "Hello, " : "Hello, " + "World"

# Substring
expr "Hello World" : '.\{5\}'   # Matches the first 5 characters

# String Length
expr length "OpenAI"

# Searching for Substrings
expr index "Hello" "ll"   # Returns the position of the first occurrence of "ll"

### Using Variables:
x=10
y=5
expr $x + $y


### Increment/Decrement:
# Increment
x=5
x=$(expr $x + 1)
echo $x

# Decrement
x=8
x=$(expr $x - 1)
echo $x


