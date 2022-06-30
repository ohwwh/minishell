#include "minishell.h"
#include <string.h>

int main(void)
{
    char    **clear;

    clear = (char **)malloc(sizeof(char *) * 2);
	clear[0] = strdup("/usr/bin/clear");
    clear[1] = 0;
    execve("/usr/bin/clear", clear, 0);
}