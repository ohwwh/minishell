/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:41:15 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/09 16:17:50 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../Libft/libft.h"

typedef enum e_node_type
{
	PIPE,
	PRC,
	REDIR,
	CL,
}	t_node_type;

typedef struct s_meta
{
	char	*src;
	int		from;
	int		to;
}	t_meta;

typedef struct s_node
{
	t_node_type		type;
	char			**data;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_tree
{
	t_node	*root;
}	t_tree;

t_tree	*new_tree(void);
t_node	*new_node(t_node_type nt, char **data);
t_meta	*new_meta(char *s, int f, int t);

char	**lst_to_arr(t_list *l);
void	destroy_strings(char **strs);
void	destroy_nodes(t_node *n);
void	destroy_tree(t_tree *t);
void	destroy_lst(t_list *lst);

int		find_c(char *src, int from, char c);

char	*extract(char *s, int *p_from);
char	*extract_rd(char *s, int *p_from);

char	*translate(char *s);

t_tree	*parse(char *s);

void	print_meta(t_meta *m);
void	print_info(t_node *n);

bool	is_blank(char c);
bool	is_sep(char c);
void	ignore_space(char *s, int *i);
void	ignore_until_c(char *s, int *i, char c);

char	*join_and_rm_all(char *s1, char *s2);

#endif // TREE_H