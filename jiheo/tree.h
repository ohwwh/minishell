/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:41:15 by jiheo             #+#    #+#             */
/*   Updated: 2022/06/30 19:13:03 by jiheo            ###   ########.fr       */
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
	t_meta			*meta;
}	t_node;

typedef struct s_tree
{
	t_node			*root;
	struct s_tree	*next;
}	t_tree;

t_tree	*new_tree(int n);
void	destroy_nodes(t_node *n);
void	destroy_tree(t_tree *t);
t_node	*new_node(t_node_type nt);
t_node	*get_empty_leaf(t_node *n);

int		count_pipes(t_meta *m);
t_tree	*parse_to_tree(t_meta *m);
void	parse_cl(t_meta *m, t_tree *n);

#endif // TREE_H