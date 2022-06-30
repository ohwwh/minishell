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