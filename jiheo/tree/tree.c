/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:06:23 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/09 17:23:30 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void	add_subtree(t_tree *org, t_node *sub)
{
	t_node	*n;

	if (sub == NULL)
		return ;
	if (org->root->left == NULL)
		org->root->left = sub;
	else if (org->root->right == NULL)
		org->root->right = sub;
	else
	{
		n = new_node(PIPE, NULL);
		n->left = org->root;
		n->right = sub;
		org->root = n;
	}
}

t_node	*create_cl(t_meta *m, int *i)
{
	t_node	*n;
	t_list	*l;

	n = NULL;
	l = ft_lstnew();
	if (l == NULL)
		return (NULL);
	while (*i <= m->to)
	{
		ignore_space(m->src, i);
		if (m->src[*i] == '<' || m->src[*i] == '>')
			break ;
		if (*i <= m->to)
			ft_lstadd_back(l, (void *)extract(m->src, i));
	}
	if (l->len != 0)
		n = new_node(CL, lst_to_arr(l));
	destroy_lst(l);
	return (n);
}

t_node	*conn_node(t_node *org, t_node *new)
{
	t_node	*n;

	if (org == NULL)
		return (new);
	n = new_node(REDIR, NULL);
	n->left = org;
	n->right = new;
	return (n);
}

t_node	*create_rd(t_meta *m, int *i)
{
	t_node	*n;
	t_list	*l;

	n = NULL;
	while (*i <= m->to)
	{
		l = ft_lstnew();
		ignore_space(m->src, i);
		if (m->src[*i] == '<' || m->src[*i] == '>')
		{
			ft_lstadd_back(l, (void *)extract_rd(m->src, i));
			printf("check\n");
			while (*i <= m->to && !is_sep(m->src[*i]))
			{
				printf("check 222\n");
				ignore_space(m->src, i);
				printf("check 333\n");
				if (*i <= m->to)
					ft_lstadd_back(l, (void *)extract(m->src, i));
			}
			if (l->len != 0)
				n = conn_node(n, new_node(REDIR, lst_to_arr(l)));
		}
		destroy_lst(l);
	}
	return (NULL);
}

void	create_subnode(t_node *n, t_meta *m, int *p_from)
{
	int	i;

	if (n == NULL)
		return (NULL);
	i = *p_from;
	while (i <= m->to)
	{
		
	}
}

t_node	*create_prc(char *s, int *i)
{
	t_node	*n;
	t_meta	m;

	m.src = s;
	m.from = *i;
	m.to = find_c(s, *i, '|') - 1;
	n = new_node(PRC, NULL);
	if (n == NULL)
		return (NULL);
	n->right = create_cl(&m, i);
	n->left = create_rd(&m, i);
	return (n);
}

t_tree	*parse(char *s)
{
	t_tree		*t;
	int			i;

	t = new_tree();
	if (t == NULL)
		return (NULL);
	printf("input: %s\n", s);
	i = 0;
	while (s[i])
	{
		ignore_space(s, &i);
		if (s[i] != '|')
			add_subtree(t, create_prc(s, &i));
		else
			i++;
	}
	free(s);
	return (t);
}
