/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:41:06 by jiheo             #+#    #+#             */
/*   Updated: 2022/06/27 20:08:56 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

// extract는 인덱스 from_i부터 다음 space까지 정보를 추출하여 t_token 구조체 포인터를 반환한다
static
t_token	*extract_word(const char *src, int *from_i)
{
	const int	i = *from_i;
	char		*s;
	t_token		*res;

	while (src[*from_i])
	{
		if (src[*from_i] == ' ' || src[*from_i] == ';' || src[*from_i] == '|')
			break ;
		*from_i++;
	}
	s = strcpy(src, i, *from_i - 1);
	res = (t_token *)malloc(sizeof(t_token));
	res->type = WORD;
	res->str = s;
	return (res);
}

// extract_line는 인덱스 from_i부터 다음 d 전까지 정보를 추출하여 t_token 구조체 포인터를 반환한다
static
t_token	*extract_line(const char *src, int *from_i, char d)
{
	const int	i = *from_i;
	char		*s;
	t_token		*res;

	while (src[*from_i] && src[*from_i] != d)
		*from_i++;
	if (d == '"')
		s = double_strcpy(src, i, *from_i - 1);
	else if (d == '\'')
		s = single_strcpy(src, i, *from_i - 1);
	res = (t_token *)malloc(sizeof(t_token));
	res->type = WORD;
	res->str = s;
	return (res);
}

t_token	*tokenize(const char *src)
{
	
}
