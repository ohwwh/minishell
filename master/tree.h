/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:41:15 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/15 11:57:31 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "libohw/includes/libft.h"


t_tree	*new_tree(void);
t_node	*new_node(t_node_type nt, char **data);
t_meta	*new_meta(char *s, int f, int t);

char	**lst_to_arr(t_list *l);
void	destroy_strings(char **strs);
void	destroy_nodes(t_node *n);
void	destroy_tree(t_tree *t);
void	destroy_lst(t_list *lst);

int		find_c(char *src, int from, char c);

char	*extract(char *s, int *p_from);
char	*extract_rd(char *s, int *p_from);

char	*cut_value(char *str, char *envp[]);
char	*get_value(char *envp[], char *key);
char	*translate(char *s, char *envp[]);

t_tree	*parse(char *s, char *envp[]);

void	print_meta(t_meta *m);
void	print_info(t_node *n);

bool	is_blank(char c);
bool	is_sep(char c);
void	ignore_space(char *s, int *i);
void	ignore_until_c(char *s, int *i, char c);

char	*join_and_rm_all(char *s1, char *s2);

#endif // TREE_H