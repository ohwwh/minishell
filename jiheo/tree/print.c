/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:56:10 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/08 18:04:09 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void	print_meta(t_meta *m)
{
	printf("start: %d, end: %d\n", m->from, m->to);
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
