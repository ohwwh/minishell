/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:28:30 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/09 20:12:35 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tree.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\r' || c == '\n' || c == '\a' || c == '\t');
}

bool	is_sep(char c)
{
	return (is_blank(c) || c == '>' || c == '<' || c =='|');
}

void	ignore_space(char *s, int *i)
{
	while (s[*i] && is_blank(s[*i]))
		(*i)++;
}

void	ignore_until_c(char *s, int *i, char c)
{
	(*i)++;
	while (s[*i] && s[*i] != c)
		(*i)++;
}
