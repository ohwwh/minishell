/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:06:23 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/09 19:59:52 by jiheo            ###   ########.fr       */
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
	char	*cmd;
	char	**data;

	cmd = extract_rd(m->src, i);
	if (cmd == NULL)
		return (NULL);
	data = (char **)malloc(sizeof(char *) * 3);
	if (data == NULL)
		return (NULL);
	ignore_space(m->src, i);
	data[0] = cmd;
	data[1] = extract(m->src, i);
	data[2] = NULL;
	return (new_node(REDIR, data));
}

void	create_subnode(t_node *prc, t_meta *m, int *p_from)
{
	int		i;
	t_list	*cl_list;
	char	*s;

	if (prc == NULL)
		return ;
	cl_list = ft_lstnew();
	i = *p_from;
	while (i <= m->to)
	{
		ignore_space(m->src, &i);
		if (m->src[i] == '>' || m->src[i] == '<')
			prc->left = conn_node(prc->left, create_rd(m, &i));
		else
			if (i <= m->to)
				ft_lstadd_back(cl_list, (void *)extract(m->src, &i));
	}
	if (cl_list->len != 0)
		prc->right = new_node(CL, lst_to_arr(cl_list));
	*p_from = i;
	destroy_lst(cl_list);
}

t_node	*create_prc(char *s, int *i)
{
	t_node	*n;
	t_meta	m;

	m.src = s;
	m.from = *i;
	m.to = find_c(s, *i, '|') - 1;
	if (m.to <= m.from)
		return (NULL);
	n = new_node(PRC, NULL);
	create_subnode(n, &m, i);
	if (n->left == NULL && n->right == NULL)
		destroy_nodes(n);
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
