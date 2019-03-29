#include <time.h>
#include "functions.h"

int main (void)
{
	int check_quit;
	
	/* Intializes random number generator */
	srand(time(NULL));
	struct list * message_list = NULL;
	
	/* Generate first element of the list */
	message_list = create_element();
	listprint(message_list);
	
	/* Add new elements when list is not full */
	for ( int i = 0 ; i < CAPACITY - 1 ; i++ )
	{
		message_list = justr_add_element(message_list, create_element());
		listprint(message_list);
	}
	
	/* Add new elements when list is full */
	do {
		printf("We have a list with %d elements\n", CAPACITY);
		printf("Enter 1 if you whant add new element to the list and continue\n");
		printf("Enter 0 if you whant quit the program after adding new element\n");
		scanf("%d",&check_quit);
		message_list = delete_add_element(message_list, create_element());
		listprint(message_list);
	} while ( check_quit );	
	delete_list(message_list);// Delete 10 elements of the list
	return 0;
}






