/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:41:15 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/01 17:15:55 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "Libft/libft.h"

typedef enum e_node_type
{
	ROOT,
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
	char			*cmd;
	char			**arg;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_tree
{
	t_node	*root;
}	t_tree;

t_tree	*new_tree(void);
void	destroy_nodes(t_node *n);
void	destroy_tree(t_tree *t);
t_node	*new_node(t_node_type nt);
t_meta	*new_meta(char *s, int f, int t);

t_node	*make_subtree(t_meta *m);
t_tree	*parse_to_tree(char *s);
void	pre_traversal(t_node *n, void (*f)(t_node *child_n));
void	print_info(t_node *n);

#endif // TREE_H