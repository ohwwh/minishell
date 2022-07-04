#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libohw/includes/libft.h"

int cd(char *envp[], char **command);
int	pwd(char **command);
int echo(char **command);
void    shell_exit(int status, char *envp[]);
char	*cat_env(char *key, char *value);
char	*get_value(char *envp[], char *key);
char	*cut_value(char *str);
char	**get_paths(char const *s, char c, char *command);
int	shell_pipe(char **command1, char **command2, t_list *env_list, char *envp[]);
int	excute_fork(char *envp[], char **command);
void	free_arr(char **command);
int env_export(char ***envp, char **command);
int	env_export_string(char ***envp, char *command);
int	env(char *envp[], char **command);
int	count_env(char *envp[]);
void	init_env(char **envp_new[], char *envp[]);
int	is_exist(char *envp[], char *key);
void    unset(char ***envp, char **command);