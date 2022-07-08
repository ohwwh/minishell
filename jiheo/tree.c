/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:41:12 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/05 12:55:51 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

//	TODO:
//		- Handle memory leak ✅
//		- Null guard
//		- Error handling
//		- Signal handling

void	print_meta(t_meta *m)
{
	for (int i = m->from; i <= m->to; i++)
		printf("%c", m->src[i]);
	printf("\n");
}

char	*range_strdup(t_meta *m)
{
	char	*s;
	int		i;

	s = (char *)malloc((m->to - m->from + 2) * sizeof(char));
	if (s == NULL)
		return (NULL);
	i = m->from;
	while (i <= m->to)
	{
		s[i - m->from] = m->src[i];
		i++;
	}
	s[i] = 0;
	return (s);
}

bool	is_blank(char c)
{
	return (c == ' ' || c == '\r' || c == '\n' || c == '\a' || c == '\t');
}

char	*_join(t_meta *m, bool is_env, char *res)
{
	char	*tmp;
	char	*dump;

	tmp = ft_substr(m->src, (unsigned int)m->from, m->to - m->from);
	dump = res;
	if (is_env)
		res = ft_strjoin(res, getenv(tmp));
	else
		res = ft_strjoin(res, tmp);
	if (tmp != NULL)
		free(tmp);
	if (dump != NULL)
		free(dump);
	return (res);
}

static
void	jump_string(const char *s, int *i)
{
	const char	c = s[*i];

	while (s[*i] && s[*i] != c)
		(*i)++;
}

static
void	jump_space(const char *s, int *i, int end)
{
	while (*i <= end && is_blank(s[*i]))
		(*i)++;
}

char	*translate_line(char *s)
{
	t_meta	m;
	int		i = 0;
	char	*res = NULL;
	char	*tmp;
	char	*dump;

	m.src = s;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			m.from = i;
			while (s[i] && s[i] != '\'')
				i++;
			m.to = i;
			res = _join(&m, false, res);
		}
		if (s[i] != '$')
		{
			m.from = i;
			while (s[i] && s[i] != '$')
				i++;
			m.to = i;
			res = _join(&m, false, res);
		}
		if (s[i] == '$')
		{
			m.from = ++i;
			while (s[i] && ft_isalnum(s[i]))
				i++;
			m.to = i;
			res = _join(&m, true, res);
		}
	}
	return (res);
}

t_meta	*new_meta(char *s, int f, int t)
{
	t_meta	*m;

	m = (t_meta *)malloc(sizeof(t_meta));
	if (m == NULL)
		return (NULL);
	m->from = f;
	m->src = s;
	m->to = t;
	return (m);
}

t_tree	*new_tree(void)
{
	t_tree	*t;

	t = (t_tree *)malloc(sizeof(t_tree));
	if (t == NULL)
		return (t);
	t->root = new_node(PIPE);
	return (t);
}

void	destroy_tree(t_tree *t)
{
	if (t == NULL)
		return ;
	destroy_nodes(t->root);
}

void    destroy_strings(char **strs)
{
	int     i;

	i = 0;
	while (strs && strs[i] != NULL)
		free(strs[i++]);
}

void	destroy_nodes(t_node *n)
{
	if (n == NULL)
		return ;
	destroy_nodes(n->left);
	destroy_nodes(n->right);
	destroy_strings(n->data);
	free(n->data);
	free(n);
}

t_node	*new_node(t_node_type nt)
{
	t_node  *n;

	n = (t_node *)malloc(sizeof(t_node));
	n->data = NULL;
	n->type = nt;
	n->left = NULL;
	n->right = NULL;
	return (n);
}

char	**lst_to_arr(t_list *l)
{
	char		**res;
	t_list_node	*n;
	int			i;

	res = (char **)malloc((l->len + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	res[l->len] = NULL;
	n = l->front;
	i = 0;
	while (n)
	{
		res[i++] = (char *)n->content;
		n = n->next;
	}
	return (res);
}

char	*handle_quotes(t_meta *m, int *i)
{
	char	c;
	t_meta	tmp_m;
	char	*src;

	src = m->src;
	c = src[*i];
	tmp_m.src = src;
	tmp_m.from = ++(*i);
	while (*i <= m->to && src[*i] != c)
		(*i)++;
	if (!(src[*i]))
		return (NULL);
	tmp_m.to = *i - 1;
	if (tmp_m.from > tmp_m.to)
		return (NULL);
	(*i)++;
	return (range_strdup(&tmp_m));
}

char	*handle_word(t_meta *m, int *i)
{
	t_meta	tmp_m;
	char	*src;

	src = m->src;
	tmp_m.src = src;
	tmp_m.from = *i;
	while (*i <= m->to && !is_blank(src[*i]) && src[*i] != '>' && src[*i] != '<')
		(*i)++;
	tmp_m.to = *i - 1;
	if (tmp_m.from > tmp_m.to)
		return (NULL);
	return (range_strdup(&tmp_m));
}

void	destroy_lst(t_list *lst)
{
	t_list_node	*n;
	t_list_node	*target;

	if (lst == NULL)
		return ;
	n = lst->front;
	while (n)
	{
		target = n;
		n = n->next;
		free(target);
		target = NULL;
	}
	free(lst);
	lst = NULL;
}

char	*handle_rd_cmd(t_meta *m, int *i)
{
	t_node	*s;
	t_meta	tmp_m;

	if (m->src[*i] != '<' && m->src[*i] != '>')
		return (NULL);
	tmp_m.src = m->src;
	tmp_m.from = *i;
	(*i)++;
	if (m->src[*i - 1] == m->src[*i])
		(*i)++;
	tmp_m.to = *i - 1;
	return (range_strdup(&tmp_m));
}

t_node	*handle_cl(t_meta *m, int *i)
{
	t_node	*cl_node = NULL;
	t_list	*arg_list = ft_lstnew();

	while (*i <= m->to)
	{
		jump_space(m->src, i, m->to);
		if (m->src[*i] == '\'' || m->src[*i] == '"')
			ft_lstadd_back(arg_list, (void *)handle_quotes(m, i));
		else
			ft_lstadd_back(arg_list, (void *)handle_word(m, i));
		if (m->src[*i] == '>' || m->src[*i] == '<')
			break ;
	}
	if (arg_list->len != 0)
	{
		cl_node = new_node(CL);
		cl_node->data = lst_to_arr(arg_list);
	}
	destroy_lst(arg_list);
	return (cl_node);
}

t_node	*handle_rd(t_meta *m, int *i)
{
	t_node	*rd_node = NULL;
	t_node	*bridge_node;
	t_node	*tmp_node;
	t_meta	tmp_m;
	t_list	*arg_list;

	tmp_m.src = m->src;
	tmp_m.to = m->to;
	while (*i <= m->to)
	{
		arg_list = ft_lstnew();
		jump_space(m->src, i, m->to);
		if (m->src[*i] == '>' || m->src[*i] == '<')
		{
			ft_lstadd_back(arg_list, (void *)handle_rd_cmd(m, i));
			while (*i <= m->to && m->src[*i] != '>' && m->src[*i] != '<')
			{
				jump_space(m->src, i, m->to);
				tmp_m.from = *i;
				if (m->src[*i] == '\'' || m->src[*i] == '"')
					ft_lstadd_back(arg_list, (void *)handle_quotes(&tmp_m, i));
				else
					ft_lstadd_back(arg_list, (void *)handle_word(&tmp_m, i));
				(*i)++;
			}
			if (arg_list->len != 0)
			{
				tmp_node = new_node(REDIR);
				tmp_node->data = lst_to_arr(arg_list);
			}
			if (rd_node == NULL)
				rd_node = tmp_node;
			else
			{
				bridge_node = new_node(REDIR);
				bridge_node->left = rd_node;
				bridge_node->right = tmp_node;
				rd_node = bridge_node;
			}
		}
		destroy_lst(arg_list);
	}
	return (rd_node);
}

t_node	*make_subtree(t_meta *m)
{
	t_node	*p;
	t_node	*cl;
	t_node	*rd;
	int		i;

	i = m->from;
	cl = handle_cl(m, &i);
	rd = handle_rd(m, &i);
	if (cl == NULL && rd == NULL)
		return (NULL);
	else if (cl == NULL)
		return (rd);
	else if (rd == NULL)
		return (cl);
	else
	{
		p = new_node(PRC);
		p->left = rd;
		p->right = cl;
		return (p);
	}
}

t_tree	*parse_to_tree(char *s)
{
	t_tree	*t;
	t_node	*n;
	t_node	*p;
	t_meta	m;
	int		i;
	const int	len = ft_strlen(s);

	t = new_tree();
	if (t == NULL)
		return (NULL);
	i = 0;
	n = NULL;
	m.src = s;
	while (s[i])
	{
		jump_space(s, &i, len);
		if (s[i] != '|')
		{
			m.from = i;
			while (s[i] && s[i] != '|')
			{
				if (s[i] == '\'' || s[i] == '"')
					jump_string(s, &i);
				i++;
			}
			m.to = i - 1;
			n = make_subtree(&m);
		}
		else
			i++;
		if (n == NULL) // syntax error: found pipeline with no command line
			continue ;
		if (t->root->left == NULL)
			t->root->left = n;
		else if (t->root->right == NULL)
			t->root->right = n;
		else
		{
			p = new_node(PIPE);
			p->left = t->root;
			p->right = n;
			t->root = p;
		}
		n = NULL;
	}
	free(s);
	return (t);
}

void	pre_traversal(t_node *n, void (*f)(t_node *child_n))
{
	if (n == NULL)
		return ;
	pre_traversal(n->left, f);
	f(n);
	pre_traversal(n->right, f);
}

void	print_info(t_node *n)
{
	int	i;

	if (!(n && n->data && n->data[0]))
		return ;
	if (n->type == CL)
		printf("type: COMMAND LINE\n");
	else if (n->type == REDIR)
		printf("type: REDIRECTION\n");
	printf("cmd: %s\n", n->data[0]);
	i = 1;
	while ((n->data)[i])
	{
		printf("args[%d]: %s\n", i, (n->data)[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_tree	*t;

	t = parse_to_tree(translate_line(argv[1]));
	pre_traversal(t->root, print_info);
	destroy_tree(t);
}
