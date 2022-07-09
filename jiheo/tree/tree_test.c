/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:07:05 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/09 16:50:20 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void	pre_traversal(t_node *n, void (*f)(t_node *child_n))
{
	if (n == NULL)
		return ;
	pre_traversal(n->left, f);
	f(n);
	pre_traversal(n->right, f);
}

int	main(int argc, char **argv)
{
	// char *s;
	t_tree	*t;

	t = parse(ft_strdup(argv[1]));
	pre_traversal(t->root, print_info);
	destroy_tree(t);
	// int	i = 0;
	// printf("org: %s\n", argv[1]);
	// s = translate(ft_strdup(argv[1]));
	// printf("translated: %s\n", s);
	// free(s);
	// s = extract(ft_strdup(argv[1]), &i);
	// printf("extracted: %s\n", s);
	// free(s);
}
