gcc -g -lreadline -lohw \
-L./libohw \
-I./libohw/includes \
-I./ \
-L/Users/hoh/.brew/opt/readline/lib \
-I/Users/hoh/.brew/opt/readline/include \
minishell.c other/env_utils.c other/getpaths.c other/cd.c other/echo.c other/env.c other/exit.c \
other/export.c other/pwd.c other/unset.c other/pipe.c other/redir.c other/init.c other/pipe_command.c other/execute.c \
tree/print.c tree/tree.c tree/utils.c tree/find.c tree/advlst.c tree/destroy.c tree/extract.c tree/new_data.c \
tree/strings.c tree/translate.c tree/check.c \
-o minishell

#gcc -lreadline -lohw -L/opt/homebrew/opt/readline/lib -L./libohw -I./libohw/includes -I/opt/homebrew/opt/readline/include minishell.c env_utils.c getpaths.c cd.c echo.c env.c exit.c export.c pwd.c unset.c pipe.c print.c tree.c utils.c find.c advlst.c destroy.c extract.c new_data.c -o minishell

#-L/opt/homebrew/opt/readline/lib \
#-L./libohw \
#-I/opt/homebrew/opt/readline/include \
#-I./libohw/includes \