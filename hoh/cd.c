#include "./libohw/includes/libft.h"
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
        chdir("/~");
    else if (chdir(argv[1]) == -1)
        return (printf("cd: %s: No such file or directory\n", argv[1]));
}