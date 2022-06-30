/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:41:12 by jiheo             #+#    #+#             */
/*   Updated: 2022/06/30 18:56:52 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

char	*range_strdup(const char *src, int from, int to)
{
	char	*s;
	int		i;

	s = (char *)malloc((to - from + 2) * sizeof(char));
	if (s == NULL)
		return (NULL);
	i = from;
	while (i <= to)
	{
		s[i - from] = src[i];
		i++;
	}
	s[i] = 0;
	return (s);
}

bool	is_blank(char c)
{
	return (c == ' ' || c == '\r' || c == '\n' || c == '\a' || c == '\t');
}

bool	is_seperator(char c)
{
	return (c == ';' || c == '>' || c == '<' || c == '|' || is_blank(c));
}

char	*translate_env(const char *src, int from, int to)
{
	int		left = from;
	int		right = from;
	char	*res;
	char	*tmp;
	char	*dump;

	res = NULL;
	while (right <= to)
	{
		if (src[right] != '$')
		{
			while (right <= to && src[right] != '$')
				right++;
			tmp = ft_substr(src, (unsigned int)left, right - left);
			dump = res;
			res = ft_strjoin(res, tmp);
			if (tmp != NULL)
				free(tmp);
			if (dump != NULL)
				free(dump);
			tmp = NULL;
			dump = NULL;
		}
		if (src[right] == '$')
		{
			left = right + 1;
			while (right <= to && ft_isalnum(src[++right]))
				;
			tmp = ft_substr(src, (unsigned int)left, right - left);
			dump = res;
			res = ft_strjoin(res, getenv(tmp));
			if (tmp != NULL)
				free(tmp);
			if (dump != NULL)
				free(dump);
			tmp = NULL;
			dump = NULL;
		}
		left = right;
	}
	return (res);
}

static
void	make_tree(t_node *node, int n)
{
	int	left_size;
	int	right_size;

	if (n <= 0 || node == NULL)
		return ;
	if (n > 2)
	{
		node->left = new_node(PIPE);
		node->right = new_node(PIPE);
	}
	else
	{
		node->left = new_node(PRC);
		if (n == 2)
			node->right = new_node(PRC);
		return ;
	}
	left_size = (n - 2) / 2 + (n - 2) % 2;
	left_size = (n - 2) / 2;
	make_tree(node->left, left_size);
	make_tree(node->right, right_size);
}

t_tree	*new_tree(int n)
{
	t_tree	*t;

	t = (t_tree *)malloc(sizeof(t_tree));
	if (t == NULL)
		return (t);
	t->next = NULL;
	if (n == 0)
		return (t);
	t->root = new_node(PIPE);
	make_tree(t->root, n);
	return (t);
}

void	destroy_tree(t_tree *t)
{
	if (t == NULL)
		return ;
	destroy_nodes(t->root);
	destroy_tree(t->next);
}

void    destroy_strings(char **strs)
{
	int     i;

	while (strs && strs[i] != NULL)
		free(strs[i++]);
}

void	destroy_nodes(t_node *n)
{
	if (n == NULL)
		return ;
	destroy_nodes(n->left);
	destroy_nodes(n->right);
	free(n->cmd);
	destroy_strings(n->arg);
	free(n->arg);
	free(n);
}

t_node	*new_node(t_node_type nt)
{
	t_node  *n;

	n = (t_node *)malloc(sizeof(t_node));
	n->arg = NULL;
	n->type = nt;
	n->cmd = NULL;
	n->left = NULL;
	n->right = NULL;
	return (n);
}

int		count_pipes(t_meta *m)
{
	int		i;
	char	c;
	int		res;

	i = m->from;
	res = 0;
	while (i <= m->to)
	{
		if (m->src[i] == ';')
			return (res);
		else if (m->src[i] == '\'' || m->src[i] == '"')
		{
			c = m->src[i++];
			while (i <= m->to && m->src[i] != c)
				i++;
			if (i > m->to)
				return (-1);
		}
		else
		{
			if (m->src[i] == '|')
				res++;
		}
		i++;
	}
	return (res);
}

bool	is_leaf(t_node *n)
{
	return (n->left == NULL && n->right == NULL && n->type != PIPE);
}

t_node	*get_empty_leaf(t_node *n)
{
	if (n == NULL)
		return (NULL);
	if (is_leaf(n))
		return (n);
	else if (n->right == NULL)
		return (get_empty_leaf(n->left));
}

t_tree	*parse_to_tree(t_meta *m)
{
	t_tree	*t;
	t_tree	*tmp_t;
	t_meta	new_m;
	int		i;

	if (m->from >= m->to)
		return (NULL);
	t = new_tree(count_pipes(m) + 1);
	if (t == NULL)
		return ;
	i = m->from;
	while (i <= m->to)
	{
		if (m->src[i] == ';')
		{
			new_m.from = i + 1;
			new_m.to = m->to;
			new_m.src = m->src;
			tmp_t = parse_to_tree(&new_m);
			t->next = tmp_t;
			return (t);
		}
		if (m->src[i] == '|')
		{
			new_m.from = m->from;
			new_m.to = i - 1;
			new_m.src = m->src;
			parse_cl(&new_m, t);
		}
		i++;
	}
}

void	parse_cl(t_meta *m, t_tree *t)
{
	int	i;
	t_node	*cmd;
	t_node	*rd;

	i = m->from;
	while (i <= m->to)
	{
		if (is_blank(m->src[i]))
			while (m->src[i] && is_blank(m->src[i]))
				i++;
		if (m->src[i] == '\'' || m->src[i] == '"')
		{
			char	c;
			int		s_i;
			while (m->src[i] && m->src[i] != c)
				i++;
			if (i >= m->to)
			{
				// syntax error: Invalid quotes
				return ;
			}
			
		}
	}
}
