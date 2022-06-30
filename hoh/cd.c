#include "minishell.h"

int cd(int argc, char *argv[])
{
    if (argc == 1)
        chdir("/~");
    else if (chdir(argv[1]) == -1)
        return (printf("cd: %s: No such file or directory\n", argv[1]));
    return (0);
}