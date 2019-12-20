/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtorwold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:43:35 by wtorwold          #+#    #+#             */
/*   Updated: 2019/12/20 17:06:54 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		check_comment_links(char *line)
{
	int			res;

	res = ft_hash(line);
	if (res == -1)
		return (-1);
	else if (res == 1 || res == 2)
	{
		ft_error("ERROR - start or end includes in links");
		return (-3);
	}
	else
		return (0);
}

static void		check_duplicate_links(t_links *links)
{
	t_links		*cpy;
	t_links		*temp;
	int			i;
	int			l;

	cpy = links;
	while (cpy)
	{
		i = 0;
		l = 0;
		temp = links;
		while (temp)
		{
			if (ft_strcmp(cpy->begin, temp->begin) == 0 &&
			ft_strcmp(cpy->finish, temp->finish) == 0)
				i++;
			if (ft_strcmp(cpy->begin, temp->finish) == 0 &&
			ft_strcmp(cpy->finish, temp->begin) == 0)
				l++;
			temp = temp->next;
		}
		if (i > 1 || l > 0)
			ft_error("Error - Dublicate link's line");
		cpy = cpy->next;
	}
}

void			parse_links(t_lem *lem)
{
	if (check_comment_links(lem->line) == -1)
		lem->line = NULL;
	else
		add_links(lem);
	while (ft_read_file(lem) > 0)
	{
		if (ft_hash(lem->line) == -1)
		{
			lem->line = NULL;
			continue ;
		}
		add_links(lem);
	}
	if (!lem->v)
		check_duplicate_links(lem->links);
}
