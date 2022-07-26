/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:01:08 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/26 21:53:19 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_global_set	g_set;

void	print_errmsg(char *s)
{
	g_set.errno_temp = 258;
	if (!s || (s[0] == 0 || is_blank(s[0])))
		printf("minishell: syntax error near unexpected token `newline'\n");
	else
		printf("minishell: syntax error near unexpected token `%s'\n", s);
}
