gcc -lreadline -lohw -L/opt/homebrew/opt/readline/lib -L./libohw -I./libohw/incs -I/opt/homebrew/opt/readline/include minishell.c export_new.c getenv.c getpaths.c cd.c echo.c env.c exit.c export.c pwd.c unset.c -o minishell
