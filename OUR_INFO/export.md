[x] if just export print all env
[x] if something after env return error
[x] if something after export - ignore it
[x] export a=  a  (saves only a= stops on first empty space)

[x]minishell $ export x=file
	minishell $ cat Make$x

[x] minishell $ export MY_LS_VAR="ls -la"
	minishell $ $MY_LS_VAR
	total 84
	drwxr-xr-x 11 akurmyza 2022_berlin  4096 Feb 15 10:09 .
	drwxr-xr-x  3 akurmyza 2022_berlin   130 Jan 28 10:40 ..
	drwxrwxrwx  2 akurmyza 2022_berlin  4096 Jan 18 18:07 DOCUMENTATION
	drwxr-xr-x  8 akurmyza 2022_berlin  4096 Feb 15 09:58 .git