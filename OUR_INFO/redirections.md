[ ] echo ooooooo>>fil.txt >> file.txt >> 1.txt - writes to all of them (creates new if neccessary)
[ ] echo hell > > fil.txt				     	  zsh: parse error near `>'
[ ]	echo DDDDDDDDDDDD>2.txt NNNNNN				(writes DDDDDDDDDDDD NNNNNN in txt)
[ ]  echo DDDDDDDDDDDD>2.txt NNNNNN>3.txt		(write in exist 2.txt, creates 3.txt and writes )