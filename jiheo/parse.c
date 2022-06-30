/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:41:06 by jiheo             #+#    #+#             */
/*   Updated: 2022/06/30 13:11:00 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*range_strdup(const char *src, int from, int to)
{
	char	*s;
	int		i;

	s = (char *)malloc((to - from + 2) * sizeof(char));
	if (s == NULL)
		return (NULL);
	i = from;
	while (i <= to)
	{
		s[i - from] = src[i];
		i++;
	}
	s[i] = 0;
	return (s);
}

bool	is_blank(char c)
{
	return (c == ' ' || c == '\r' || c == '\n' || c == '\a' || c == '\t');
}

bool	is_seperator(char c)
{
	return (c == ';' || c == '>' || c == '<' || c == '|' || is_blank(c));
}

char	*find_env(const char *src, int from, int to)
{
	char	*key;
	char	*val;

	key = range_strdup(src, from, to);
	val = getenv(key);
	free(key);
	return (val);
}

void	handle_cmd_flag(const char c, bool *is_cmd)
{
	if (c == '|' || c == ';')
		*is_cmd = true;
	else
		*is_cmd = false;
}

char	*translate_env(const char *src, int from, int to)
{
	int		left = from;
	int		right = from;
	char	*res;
	char	*tmp;
	char	*dump;

	res = NULL;
	while (right <= to)
	{
		if (src[right] != '$')
		{
			while (right <= to && src[right] != '$')
				right++;
			tmp = ft_substr(src, (unsigned int)left, right - left);
			dump = res;
			res = ft_strjoin(res, tmp);
			if (tmp != NULL)
				free(tmp);
			if (dump != NULL)
				free(dump);
			tmp = NULL;
			dump = NULL;
		}
		if (src[right] == '$')
		{
			left = right + 1;
			while (right <= to && ft_isalnum(src[++right]))
				;
			tmp = ft_substr(src, (unsigned int)left, right - left);
			dump = res;
			res = ft_strjoin(res, getenv(tmp));
			if (tmp != NULL)
				free(tmp);
			if (dump != NULL)
				free(dump);
			tmp = NULL;
			dump = NULL;
		}
		left = right;
	}
	return (res);
}

t_token_list	*tokenize(const char *src)
{
	int				i;
	bool			is_cmd;
	t_token_list	*l;

	i = 0;
	is_cmd = true;
	l = new_token_list();
	while (src[i])
	{
		if (is_blank(src[i]))
		{
			while (src[i] && is_blank(src[i]))
				i++;
		}
		if (src[i] == '|')
			append_token(l, new_token("|", PIPE));
		else if (src[i] == '>')
		{
			if (src[i + 1] == '>')
			{
				append_token(l, new_token(">>", REDIR_OUT));
				i++;
			}
			else
				append_token(l, new_token(">", REDIR_OUT));
		}
		else if (src[i] == '<')
		{
			if (src[i + 1] == '<')
			{
				append_token(l, new_token("<<", REDIR_IN));
				i++;
			}
			else
				append_token(l, new_token("<", REDIR_IN));
		}
		else if (src[i] == ';')
			append_token(l, new_token(";", END));
		else if (src[i] == '"' || src[i] == '\'')
		{
			char c = src[i];
			int s_i = ++i;
			while (src[i] && src[i] != c)
				i++;
			if (!src[i])
			{
				// syntax error
				destroy_token_list(l);
				return (NULL);
			}
			if (c == '\'')
				append_token(l, new_token(range_strdup(src, s_i, i - 1), ARGS));
			else if (c == '"')
				append_token(l, new_token(translate_env(src, s_i, i - 1), ARGS));
		}
		else
		{
			int s_i;
			t_token_type tp;
			s_i = i;
			if (is_cmd)
				tp = CMD;
			else
				tp = ARGS;
			while (src[i] && !is_seperator(src[i]))
				i++;
			append_token(l, new_token(range_strdup(src, s_i, i - 1), tp));
			i--;
		}
		handle_cmd_flag(src[i], &is_cmd);
		i++;
	}
	return (l);
}

int	main(int argc, char **argv)
{
	printf("arg: %s\n", argv[1]);
	t_token_list	*l = tokenize(argv[1]);
	t_token	*iter;

	iter = l->head;
	while (iter)
	{
		printf("str: %s\t\t\ttype: ", iter->str);
		if (iter->type == CMD)
			printf("cmd\n");
		else if(iter->type == ARGS)
			printf("args\n");
		else if(iter->type == PIPE)
			printf("pipe\n");
		else if(iter->type == REDIR_IN)
			printf("redir in\n");
		else if(iter->type == REDIR_OUT)
			printf("redir out\n");
		else if(iter->type == END)
			printf("end\n");
		iter = iter->next;
	}
	destroy_token_list(l);
}
