/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:19:19 by jiheo             #+#    #+#             */
/*   Updated: 2022/06/27 16:43:09 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	exit_with_error(const char *msg, t_error_type et)
{
	if (et == SYNTAX)
		printf("Syntax error > ");
	else if (et == SYS)
		printf("System error > ");
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}
