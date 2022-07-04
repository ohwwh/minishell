#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libohw/includes/libft.h"

int cd(t_list **env_list, char **command);
int	pwd(char **command);
int echo(char **command);
int env(t_list **env_list, char **command);
void    shell_exit(int status, t_list **env_list);
void	unset(t_list **env_list, char **command);
int env_export(t_list **env_list, char **command);
void    delnode(void *content);
void	init_env(t_list **env_list, char *env[]);
t_list	*is_exist(t_list *env_list, char *key);
char    *get_env(t_list *env_list, char *key);
char	**get_paths(char const *s, char c, char *command);
int	shell_pipe(char **command1, char **command2, t_list *env_list, char *envp[]);
int	excute_fork(t_list **env_list, char **command, char *envp[]);

int env_export_new(char ***envp, char **command);
int	env_new(char *envp[], char **command);
int	count_env(char *envp[]);
void	init_env_new(char **envp_new[], char *envp[]);
int	is_exist_new(char *envp[], char *command);
void    unset_new(char ***envp, char **command);