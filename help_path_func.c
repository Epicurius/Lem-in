
#include "lem_in.h"

void	free_path(t_path *path_l)
{
	t_path *curr;

	curr = path_l;
	while (curr != NULL)
	{
		path_l = path_l->next;
		if (curr->div != NULL)
			free(curr->div); //memdel
		free(curr->path);
		free(curr);
		curr = path_l;
	}
}

void	add_path_to_list(t_path *paths, t_path *new)
{
	t_path *curr;

	if (paths && new)
	{
		curr = paths;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new;
	}
}

t_path	*re_link(t_path *path_l)
{
	t_path *tmp;

	path_l->next->path_nb = path_l->path_nb;
	path_l->next->div = path_l->div;
	path_l->next->llen = path_l->llen;
	tmp = path_l;
	path_l = path_l->next;
	free(tmp);
	return (path_l);
}
/*
int	longest_path(t_lem_in *lem, t_path *paths)
{
	int		i;
	int		ll = 0;
	t_path	*path;

	i = 0;
	path = paths;
	lem->max_paths = paths->path_nb;
	while (i < lem->max_paths)
	{
		if (path->len > ll)
			ll = path->len;
		++i;
		path = path->next;
	}
	return (ll);
}*/

void	set_path(t_path **path_l, int i, t_lem_in *lem)
{
	t_path *tmp;

	if ((*path_l)->path == NULL && (*path_l)->next->path != NULL)
		*path_l = re_link(*path_l);
	(*path_l)->path_nb = i;
	//printf("paths_nb: %d\n", path_nb);
	//(*path_l)->llen = longest_path(lem, *path_l);
	ant_algo(lem, *path_l);
	//if (!((*path_l)->div = divide_ants(lem, *path_l)))
	//	error_msg("Cant find a single path. (set_path)");
}
