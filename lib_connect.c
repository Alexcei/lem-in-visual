#include "lem_visual.h"

t_connect		*ft_connect_new(t_rooms *rooms)
{
	t_connect	*res;

	if (!(res = (t_connect*)ft_memalloc(sizeof(t_connect))))
		return (NULL);
	res->rooms = rooms;
	res->next = NULL;
	return (res);
}

void  			ft_connect_push_back(t_connect **begin_list, t_connect *new)
{
	t_connect  *last;

	if (!*begin_list)
	{
		*begin_list = new;
		return ;
	}
	last = *begin_list;
	while (last->next)
		last = last->next;
	last->next = new;
}

void			ft_connect_add(t_connect **alst, t_connect *new)
{
	if (alst && new)
	{
		if (*alst)
		{
			new->next = *alst;
			*alst = new;
		}
		else
			*alst = new;
	}
}

void 		ft_connect_clear(t_connect **begin_list)
{
	t_connect *temp;

	while (*begin_list)
	{
		temp = *begin_list;
		*begin_list = (*begin_list)->next;
		free(temp);
	}
	*begin_list = NULL;
}

void	ft_connect_remove_if(t_connect **begin_list, int bfs, int (*cmp)())
{
	t_connect  *privios;
	t_connect  *current;

	current = *begin_list;
	privios = NULL;
	while (current)
	{
		if (!cmp(current->rooms, bfs))
		{
			if (current == *begin_list)
			{
				*begin_list = current->next;
				free(current);
				current = *begin_list;
			}
			else
			{
				privios->next = current->next;
				free(current);
				current = privios;
			}
		}
		else
		{
			privios = current;
			current = current->next;
		}
	}
}

void	ft_connect_remove_if1(t_connect **begin_list, int bfs, int (*cmp)())
{
	t_connect	*remove;
	t_connect	*current;

	current = *begin_list;
	while (current && current->next)
	{
		if ((*cmp)(current->rooms, bfs) == 0)
		{
			remove = current->next;
			current->next = current->next->next;
			free(remove);
		}
		current = current->next;
	}
	current = *begin_list;
	if (current && (*cmp)(current->rooms, bfs) == 0)
	{
		*begin_list = current->next;
		free(current);
	}
}