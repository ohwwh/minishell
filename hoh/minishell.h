#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libohw/includes/libft.h"

int		cd(char *envp[], char **command);
int		pwd(char **command);
int 	echo(char **command);
void    shell_exit(int status, char *envp[]);
char	*cat_env(char *key, char *value, char *envp[]);
char	*get_value(char *envp[], char *key);
char	*cut_value(char *str, char *envp[]);
char	**get_paths(char const *s, char c, char *command, char *envp[]);
int		shell_pipe(char **command1, char **command2, char *envp[]);
int		execute_fork(char *envp[], char **command);
void	free_arr(char **arr);
int 	env_export(char ***envp, char **command);
int	env_export_string(char ***envp, char *command);
int		env(char *envp[], char **command);
int		count_env(char *envp[]);
void	init_env(char **envp_new[], char *envp[]);
int		is_exist(char *envp[], char *key);
void    unset(char ***envp, char **command);