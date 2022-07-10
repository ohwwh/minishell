/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 08:10:25 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/11 08:24:19 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include "../tree.h"

int main()
{
    t_tree  *t;
    char    *cmd;

    cmd = NULL;
    while (1)
    {
        cmd = readline("tree_test$ ");
        if (cmd == NULL)
            exit(EXIT_SUCCESS);
        t = parse(ft_strdup(cmd));
        pre_traversal(t->root, print_info);
        destroy_tree(t);
        free(cmd);
        cmd = NULL;
    }
}
