/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 00:58:21 by bpole             #+#    #+#             */
/*   Updated: 2019/12/19 00:58:28 by bpole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		match_name(char **str, t_lem *lem)
{
	t_rooms		*rooms;
	t_rooms		*src;
	t_rooms		*dst;

	src = NULL;
	dst = NULL;
	rooms = lem->rooms;
	while (rooms)
	{
		if (ft_strcmp(str[0], rooms->name) == 0)
			src = rooms;
		else if (ft_strcmp(str[1], rooms->name) == 0)
			dst = rooms;
		if (src && dst)
			break ;
		rooms = rooms->next;
	}
	if (!src || !dst)
		ft_error("ERROR - links name dosn't consist in rooms");
	ft_connect_push_back(&src->connect, ft_connect_new(dst));
	ft_connect_push_back(&dst->connect, ft_connect_new(src));
}

static char		**valid_links(t_lem *lem)
{
	char		**str;
	int			i;

	i = 0;
	if ((str = ft_strsplit(lem->line, '-')) == NULL)
		return (NULL);
	while (str[i] != NULL)
		i++;
	if (i != 2)
		ft_error("ERROR in link");
	match_name(str, lem);
	return (str);
}

static t_links	*creat_links(char **str)
{
	t_links		*new;

	if ((new = (t_links *)malloc(sizeof(t_links))) == NULL)
		ft_error("ERROR of malloc");
	new->begin = ft_strjoin("", str[0]);
	new->finish = ft_strjoin("", str[1]);
	new->next = NULL;
	return (new);
}

void			add_links(t_lem *lem)
{
	char		**str;
	t_links		*cpy;

	cpy = lem->links;
	if ((str = valid_links(lem)) == NULL)
		ft_error("Error in links");
	if (lem->links == NULL)
		lem->links = creat_links(str);
	else
	{
		while (cpy->next != NULL)
			cpy = cpy->next;
		cpy->next = creat_links(str);
	}
	ft_free_char_arr(&str);
}
