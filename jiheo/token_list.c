/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:10:19 by jiheo             #+#    #+#             */
/*   Updated: 2022/06/28 22:37:07 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_token_list    *new_token_list()
{
    t_token_list    *l;

    l = (t_token_list *)malloc(sizeof(t_token_list));
    l->head = NULL;
    l->len = 0;
    return (l);
}

void    destroy_token_list(t_token_list *l)
{
    t_token *iter;
    t_token *target;

    iter = l->head;
    while (iter)
    {
        target = iter;
        iter = iter->next;
        free(target);
    }
}

t_token *new_token(char *str, t_token_type t)
{
    t_token *token;

    token = (t_token *)malloc(sizeof(t_token));
    if (token == NULL)
        exit_with_error("bad alloc", SYS);
    token->next = NULL;
    token->str = str;
    token->type = t;
    return (token);
}

void    append_token(t_token_list *l, t_token *ele)
{
    t_token *iter;

    iter = l->head;
    if (iter == NULL)
        l->head = ele;
    else
    {
        while (iter->next != NULL)
            iter = iter->next;
        iter->next = ele;
    }
    l->len++;
}
