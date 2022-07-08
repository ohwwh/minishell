/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:07:05 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/08 09:34:27 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void	print_meta(t_meta *m)
{
	for (int i = m->from; i <= m->to; i++)
		printf("%c", m->src[i]);
	printf("\n");
}

void	print_info(t_node *n)
{
	int	i;

	if (!n || !(n->data) || !((n->data)[0]))
		return ;
	if (n->type == CL)
		printf("type: COMMAND LINE\n");
	else if (n->type == REDIR)
		printf("type: REDIRECTION\n");
	printf("cmd: %s\n", (n->data)[0]);
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
