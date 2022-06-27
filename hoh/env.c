#include "./libohw/includes/libft.h"



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
    }
}