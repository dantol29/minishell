[ ] echo ooooooo>>fil.txt >> file.txt >> 1.txt - writes to all of them (creates new if neccessary)
[ ] echo hell > > fil.txt				     	  zsh: parse error near `>'
[x]	echo DDDDDDDDDDDD>2.txt NNNNNN				(writes DDDDDDDDDDDD NNNNNN in txt)
[x]  echo DDDDDDDDDDDD>2.txt NNNNNN>3.txt		(write in exist 2.txt, creates 3.txt and writes )
[x] echo a > f.txt b > 1.txt c					writes to all of them (a b c)
[x] echo DDDDDDDDDDDD>     2.txt NNNNNN>3.txt (filename without spaces)