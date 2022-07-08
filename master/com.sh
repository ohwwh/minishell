#gcc -lreadline -lohw -L/opt/homebrew/opt/readline/lib -L./libohw -I./libohw/incs -I/opt/homebrew/opt/readline/include minishell.c env_utils.c getpaths.c cd.c echo.c env.c exit.c export.c pwd.c unset.c -o minishell
gcc -lreadline -lohw -L/Users/hoh/.brew/opt/readline/lib -L./libohw -I./libohw/incs -I/Users/hoh/.brew/opt/readline/include \
	minishell.c env_utils.c getpaths.c cd.c echo.c env.c exit.c export.c pwd.c unset.c pipe.c print.c tree.c utils.c find.c advlst.c destroy.c extract.c new_data.c\
	-o minishell
