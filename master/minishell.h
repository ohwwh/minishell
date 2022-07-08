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
#include "tree.h"

int		cd(char *envp[], char **command);
int		pwd(char **command);
int 	echo(char **command);
void    shell_exit(int status, char *envp[]);
void	exit_shell(char *envp[], char **command);
int		isdigit_string(char *str);
int		isstring_string(char *str);
char	*cat_env(char *key, char *value, char *envp[]);
char	*get_value(char *envp[], char *key);
char	*cut_value(char *str, char *envp[]);
char	**get_paths(char const *s, char c, char *command, char *envp[]);
int	shell_pipe(t_node *left, t_node *right, char *envp[]);
int		execute_fork(char *envp[], char **command);
void	free_arr(char **arr);
int 	env_export(char ***envp, char **command);
int		env_export_string(char ***envp, char *command);
int		is_valid(char *command, char *arg);
int		env(char *envp[], char **command);
int		count_env(char *envp[]);
void	init_env(char **envp_new[], char *envp[]);
int		is_exist(char *envp[], char *key);
void    unset(char ***envp, char **command);