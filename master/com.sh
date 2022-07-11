#gcc -lreadline -lohw -L/opt/homebrew/opt/readline/lib -L./libohw -I./libohw/incs -I/opt/homebrew/opt/readline/include minishell.c env_utils.c getpaths.c cd.c echo.c env.c exit.c export.c pwd.c unset.c -o minishell
gcc -lreadline -lohw -L/Users/hoh/.brew/opt/readline/lib -L./libohw -I./libohw/incs -I/Users/hoh/.brew/opt/readline/include \
	minishell.c env_utils.c getpaths.c cd.c echo.c env.c exit.c export.c pwd.c unset.c pipe.c \
	 ./tree/print.c ./tree/tree.c ./tree/utils.c ./tree/find.c ./tree/advlst.c ./tree/destroy.c ./tree/extract.c ./tree/new_data.c \
	 ./tree/translate.c ./tree/strings.c \
	-o minishell
