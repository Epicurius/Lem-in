
#include "./lem_in.h"
#include "./error_msg.h"

int main(void)
{
	t_lem_in *lem;

	lem = (t_lem_in *)malloc(sizeof(* lem));
	lem->moves = MAX_INT;
	lem->end = NULL;
	lem->start = NULL;
	lem->room_nb = 2;
	lem->min_moves = NULL;
	read_input(lem);
	room_link_list(lem);
	if (lem->min_moves != NULL)
		fprintf(stderr, "%s\n", lem->min_moves);
	//print_table(lem);
	algo(lem);
	return (0);
}
