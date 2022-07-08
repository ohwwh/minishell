// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   tree.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/06/27 15:41:12 by jiheo             #+#    #+#             */
// /*   Updated: 2022/07/08 17:18:34 by jiheo            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// // #include "tree.h"

// //	TODO:
// //		- Null guard
// //		- Error handling
// //		- Signal handling

// char	*range_strdup(t_meta *m)
// {
// 	return (ft_substr(m->src, m->from, m->to - m->from + 1));
// }

// bool	is_blank(char c)
// {
// 	return (c == ' ' || c == '\r' || c == '\n' || c == '\a' || c == '\t');
// }

// bool	is_not_sep(char c)
// {
// 	return (!(is_blank(c) || c == '>' || c == '<'));
// }

// bool	is_single_quotes(char c)
// {
// 	return (c == '\'');
// }

// bool	is_double_quotes(char c)
// {
// 	return (c == '"');
// }

// bool	is_quotes(char c)
// {
// 	return (is_single_quotes(c) || is_double_quotes(c));
// }

// char	*_join(t_meta *m, bool is_env, char *res)
// {
// 	char	*tmp;
// 	char	*dump;

// 	tmp = ft_substr(m->src, (unsigned int)m->from, m->to - m->from);
// 	dump = res;
// 	if (is_env)
// 		res = ft_strjoin(res, getenv(tmp));
// 	else
// 		res = ft_strjoin(res, tmp);
// 	if (tmp != NULL)
// 		free(tmp);
// 	if (dump != NULL)
// 		free(dump);
// 	return (res);
// }

// int	jump(char *s, int i, bool (*f)(char))
// {
// 	while (s[i] && f(s[i]))
// 		i++;
// 	return (i);
// }

// char	*join_and_rm(char *dst, char *src)
// {
// 	char	*tmp;

// 	tmp = dst;
// 	if (dst == NULL)
// 		return (ft_strdup(src));
// 	dst = ft_strjoin(dst, src);
// 	free(tmp);
// 	return (dst);
// }

// static
// void	jump_line(const char *s, int *i)
// {
// 	if (s[*i] == '\'')
// 		*i = jump(s, *i, is_single_quotes);
// 	else if (s[*i] == '"')
// 		*i = jump(s, *i, is_double_quotes);
// }

// static
// void	jump_word(const char *s, int *i)
// {
// 	*i = jump(s, *i, is_not_sep);
// }

// static
// void	jump_space(const char *s, int *i, int end)
// {
// 	while (s[*i] && is_blank(s[*i]))
// 		(*i)++;
// }

// char	*extract_line(char *s, int *i)
// {
// 	int	j;

// 	if (is_quotes(s[*i]))
// 	{
// 		j = *i + 1;
// 		jump_line(s, i);
// 		return (ft_substr(s, j, (*i)++ - j));
// 	}
// 	else
// 	{
// 		j = *i;
// 		jump_word(s, i);
// 		return (ft_substr(s, j, *i - j));
// 	}
// }

// char	*translate_line(char *s)
// {
// 	char	*tmp;
// 	int		i;
// 	char	*res = NULL;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '\'' || s[i] != '$')
// 		{
// 			tmp = extract_line(s, &i);
// 			res = join_and_rm(res, tmp);
// 			free(tmp);
// 		}
// 		if (s[i] == '$')
// 		{
// 			if (is_quotes(s[i + 1]) || !is_not_sep(s[i + 1]))
// 			{
// 				tmp = extract_line(s, &i);
// 			}
// 			i++;
// 		}
// 	}
// 	return (res);
// }

// char	**lst_to_arr(t_list *l)
// {
// 	char		**res;
// 	t_list_node	*n;
// 	int			i;

// 	res = (char **)malloc((l->len + 1) * sizeof(char *));
// 	if (res == NULL)
// 		return (NULL);
// 	res[l->len] = NULL;
// 	n = l->front;
// 	i = 0;
// 	while (n)
// 	{
// 		res[i++] = (char *)n->content;
// 		n = n->next;
// 	}
// 	return (res);
// }

// char	*extract(t_meta *m, int *i, bool (*f)(char))
// {
// 	t_meta	tmp_m;

// 	tmp_m.src = m->src;
// 	tmp_m.from = *i;
// 	while (m->src[*i] && f(m->src[*i]))
// 		(*i)++;
// 	tmp_m.to = *i - 1;
// 	if (tmp_m.from > tmp_m.to)
// 		return (NULL);
// 	return (range_strdup(&tmp_m));
// }

// char	*handle_quotes(t_meta *m, int *i)
// {
// 	char	c;
// 	char	*s;

// 	c = m->src[(*i)++];
// 	s = extract(m, i, is_quotes);
// 	(*i)++;
// 	return (s);
// }

// char	*handle_word(t_meta *m, int *i)
// {
// 	return (extract(m, i, is_not_sep));
// }

// char	*handle_rd_cmd(t_meta *m, int *i)
// {
// 	t_node	*s;
// 	t_meta	tmp_m;

// 	if (m->src[*i] != '<' && m->src[*i] != '>')
// 		return (NULL);
// 	tmp_m.src = m->src;
// 	tmp_m.from = *i;
// 	(*i)++;
// 	if (m->src[*i - 1] == m->src[*i])
// 		(*i)++;
// 	tmp_m.to = *i - 1;
// 	return (range_strdup(&tmp_m));
// }

// t_node	*handle_cl(t_meta *m, int *i)
// {
// 	t_node	*cl_node = NULL;
// 	t_list	*arg_list = ft_lstnew();

// 	while (*i <= m->to)
// 	{
// 		jump_space(m->src, i, m->to);
// 		if (*i <= m->to && (m->src[*i] == '\'' || m->src[*i] == '"'))
// 			ft_lstadd_back(arg_list, (void *)handle_quotes(m, i));
// 		else if (*i <= m->to)
// 			ft_lstadd_back(arg_list, (void *)handle_word(m, i));
// 		if (m->src[*i] == '>' || m->src[*i] == '<')
// 			break ;
// 	}
// 	if (arg_list->len != 0)
// 	{
// 		cl_node = new_node(CL);
// 		cl_node->data = lst_to_arr(arg_list);
// 	}
// 	destroy_lst(arg_list);
// 	return (cl_node);
// }

// t_node	*handle_rd(t_meta *m, int *i)
// {
// 	t_node	*rd_node = NULL;
// 	t_node	*bridge_node;
// 	t_node	*tmp_node;
// 	t_meta	tmp_m;
// 	t_list	*arg_list;

// 	tmp_m.src = m->src;
// 	tmp_m.to = m->to;
// 	while (*i <= m->to)
// 	{
// 		arg_list = ft_lstnew();
// 		jump_space(m->src, i, m->to);
// 		if (m->src[*i] == '>' || m->src[*i] == '<')
// 		{
// 			ft_lstadd_back(arg_list, (void *)handle_rd_cmd(m, i));
// 			while (*i <= m->to && m->src[*i] != '>' && m->src[*i] != '<')
// 			{
// 				jump_space(m->src, i, m->to);
// 				tmp_m.from = *i;
// 				if (*i <= m->to && (m->src[*i] == '\'' || m->src[*i] == '"'))
// 				{
// 					ft_lstadd_back(arg_list, (void *)handle_quotes(&tmp_m, i));
// 					printf("%d\n", *i);
// 				}
// 				else if (*i <= m->to)
// 					ft_lstadd_back(arg_list, (void *)handle_word(&tmp_m, i));
// 			}
// 			if (arg_list->len != 0)
// 			{
// 				tmp_node = new_node(REDIR);
// 				tmp_node->data = lst_to_arr(arg_list);
// 			}
// 			if (rd_node == NULL)
// 				rd_node = tmp_node;
// 			else
// 			{
// 				bridge_node = new_node(REDIR);
// 				bridge_node->left = rd_node;
// 				bridge_node->right = tmp_node;
// 				rd_node = bridge_node;
// 			}
// 		}
// 		destroy_lst(arg_list);
// 	}
// 	return (rd_node);
// }

// t_node	*make_subtree(t_meta *m)
// {
// 	t_node	*p;
// 	t_node	*cl;
// 	t_node	*rd;
// 	int		i;

// 	i = m->from;
// 	cl = handle_cl(m, &i);
// 	rd = handle_rd(m, &i);
// 	if (cl == NULL && rd == NULL)
// 		return (NULL);
// 	else if (cl == NULL)
// 		return (rd);
// 	else if (rd == NULL)
// 		return (cl);
// 	else
// 	{
// 		p = new_node(PRC);
// 		p->left = rd;
// 		p->right = cl;
// 		return (p);
// 	}
// }

// t_tree	*parse_to_tree(char *s)
// {
// 	t_tree	*t;
// 	t_node	*n;
// 	t_node	*p;
// 	t_meta	m;
// 	int		i;
// 	const int	len = ft_strlen(s);

// 	t = new_tree();
// 	if (t == NULL)
// 		return (NULL);
// 	i = 0;
// 	n = NULL;
// 	m.src = s;
// 	while (s[i])
// 	{
// 		jump_space(s, &i, len);
// 		if (s[i] != '|')
// 		{
// 			m.from = i;
// 			while (s[i] && s[i] != '|')
// 			{
// 				if (s[i] == '\'' || s[i] == '"')
// 					jump_line(s, &i);
// 				i++;
// 			}
// 			m.to = i - 1;
// 			n = make_subtree(&m);
// 		}
// 		else
// 			i++;
// 		if (n == NULL) // syntax error: found pipeline with no command line
// 			continue ;
// 		if (t->root->left == NULL)
// 			t->root->left = n;
// 		else if (t->root->right == NULL)
// 			t->root->right = n;
// 		else
// 		{
// 			p = new_node(PIPE);
// 			p->left = t->root;
// 			p->right = n;
// 			t->root = p;
// 		}
// 		n = NULL;
// 	}
// 	free(s);
// 	return (t);
// }

// void	pre_traversal(t_node *n, void (*f)(t_node *child_n))
// {
// 	if (n == NULL)
// 		return ;
// 	pre_traversal(n->left, f);
// 	f(n);
// 	pre_traversal(n->right, f);
// }
