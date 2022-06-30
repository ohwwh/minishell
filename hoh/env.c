#include "./libohw/includes/libft.h"

t_list env_list;

void    print_env(void *content)
{
    char **str;

    str = (char **)content;
    printf("%s=", str[0]);
    printf("%s\n", str[1]);
}

int main(int argc, char *argv[], char *env[])
{
    int i;

    i = 0;
    if (argc != 1)
        return (write(1, "env: too many arguments\n", 24));
    while (env[i])
    {
        ft_putstr_fd(env[i], 1);
        write(1, "\n", 1);
        i ++;
    } //없애도 됨
    ft_lstiter(&env_list, &print_env);
}