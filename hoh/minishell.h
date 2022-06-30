#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libohw/includes/libft.h"

int cd(int argc, char *argv[]);
int	pwd(int argc, char *argv[]);
int echo(int argc, char *argv[]);
int env(int argc, char *argv[], t_list **env_list);
void    shell_exit(int status, t_list **env_list);
void	unset(int argc, char *argv[], t_list **env_list);
int env_export(int argc, char *argv[], t_list **env_list);
void    delnode(void *content);
void	init_env(t_list **env_list, char *env[]);
t_list	*is_exist(t_list *env_list, char *key);