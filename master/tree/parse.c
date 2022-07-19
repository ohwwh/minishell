/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 12:54:27 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/19 20:08:15 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_jobqueue(t_list *l, t_node *n)
{
	if (n == NULL || l == NULL)
		return ;
	heredoc_jobqueue(l, n->left);
	if (n->data && n->data[0] && ft_strcmp(n->data[0], "<<") == 0)
		enqueue(l, n->data[1]);
	heredoc_jobqueue(l, n->right);
}

void	stop(char *s, t_tree *t, char *msg)
{
	if (msg != NULL)
		print_errmsg(msg);
	if (s != NULL)
		free(s);
	if (t != NULL)
		destroy_tree(t);
	s = NULL;
	t = NULL;
}

bool	process(char *s, int *i, char *envp[], t_tree *t)
{
	t_node	*tmp;
	bool	flag;

	if (s[*i] != '|')
	{
		tmp = create_prc(s, i, envp);
		if (tmp == NULL)
		{
			stop(s, t, NULL);
			return (NULL);
		}
		add_subtree(t, tmp);
		flag = false;
	}
	else
	{
		if (flag)
		{
			stop(s, t, "|");
			return (NULL);
		}
		flag = true;
		(*i)++;
	}
	return (flag);
}

t_tree	*parse(char *s, char *envp[])
{
	t_tree		*t;
	t_node		*tmp;
	int			i;
	bool		flag;

	flag = true;
	t = new_tree();
	i = 0;
	while (s[i])
	{
		ignore_space(s, &i);
		flag = process(s, &i, envp, t);
	}
	free(s);
	if (t != NULL)
		heredoc_jobqueue(t->queue, t->root);
	return (t);
}

