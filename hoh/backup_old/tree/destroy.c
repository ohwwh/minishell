/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:12:43 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/11 12:45:58 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tree.h"

void	destroy_strings(char **strs)
{
	int	i;

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

void	destroy_tree(t_tree *t)
{
	if (t == NULL)
		return ;
	destroy_nodes(t->root);
	free(t);
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
