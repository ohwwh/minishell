/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 12:45:07 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/15 13:16:08 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_redir(char *s)
{
	return (ft_strcmp(s, "<<") == 0 || ft_strcmp(s, ">>") == 0 || \
			ft_strcmp(s, "<") == 0 || ft_strcmp(s, ">") == 0);
}

int	check_syntax(t_list *l)
{
	t_list_node	*n;
	bool		flag;

	n = l->front;
	flag = true;
	if (l == NULL || l->front == NULL)
		return (0);
	while (n)
	{
		if (is_redir((char *)n->content))
		{
			if (flag)
				flag = false;
			else
			{
				// syntax error
				printf("list syntax error\n");
				return (1);
			}
		}
		n = n->next;
	}
	return (0);
}
