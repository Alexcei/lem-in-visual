#include "lem_visual.h"

t_rooms			*ft_rooms_new(t_connect *connect)
{
	t_rooms	*res;

	if (!(res = (t_rooms*)ft_memalloc(sizeof(t_rooms))))
		return (NULL);
	res->connect = connect;
	res->next = NULL;
	return (res);
}

void			ft_rooms_push_back(t_rooms **begin_list, t_rooms *new)
{
	t_rooms		*last;

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

void			ft_rooms_add(t_rooms **alst, t_rooms *new)
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