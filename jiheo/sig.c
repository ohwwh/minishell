/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheo <jiheo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:00:11 by jiheo             #+#    #+#             */
/*   Updated: 2022/07/08 15:38:48 by jiheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"

void    c_handler(int sig)
{
	// Ctrl C가 입력될 경우 이 함수가 실행된다.
	// Ctrl C는 입력을 초기화하거나 현재 실행중인 자식 프로세스들을 종료한다.
	// 즉 tree 구조를 순회하면서 프로세스를 종료해야한다.
	char    c;

	signal(sig, SIG_IGN);
	printf("did you hit Ctrl-C?\nDo you really want to quit? [y/n]");
	c = getchar();
	if (c == 'y' || c == 'Y')
		exit(0);
	else
		signal(SIGINT, c_handler);
	getchar();
}

void	d_handler(int sig)
{
	// Ctrl D는 signal이 아닌 input으로 제어해야한다
	// 만약 ctrl D가 입력으로 들어올 경우 프로그램을 종료한다
	// 그 외에는 signal로 처리한다
}

void	bs_handler(int sig)
{
	char    c;

	signal(sig, SIG_IGN);
	printf("did you hit Ctrl-\\?\nDo you really want to quit? [y/n]");
	c = getchar();
	if (c == 'y' || c == 'Y')
		exit(0);
	else
		signal(SIGQUIT, c_handler);
	getchar();
}

int main(void)
{
	signal(SIGINT, c_handler);
	signal(SIGQUIT, bs_handler);
	while (1)
		pause();
	printf("hi\n");
	return (0);
}
