#include <stdio.h>
#include <stdlib.h> // Let use malloc and free
#define MESSAGE_LENGTH 10 // Define length of the message
#define PRIORITY_RANGE 100 // Define priority range
#define CAPACITY 10 // Define capacity of the list

struct list
{
	char  message[MESSAGE_LENGTH]; // message field
	int priority; // priority of the message
	struct list *ptr; // pointer on the next list element
};
void message_gen(char chs[]) // generate message
{
	int i; 
	for( i = 0 ; i < MESSAGE_LENGTH - 1 ; i++ ) {
		chs[i] = 65 + rand() % 26;      
	}
	chs[MESSAGE_LENGTH - 1] = '\0';
}
int priority_gen(void) // generate priority of the message
{
	return rand() % PRIORITY_RANGE;
}
struct list *create_element(void) // Form node of the list
{
	struct list *lst;
	// memory allocation at the root of the list
	lst = (struct list*)malloc(sizeof(struct list));  
	lst->priority = priority_gen();  
	message_gen(lst->message);
	lst->ptr = NULL; // This is the last node of the list
	printf("\n");
	printf("New element Priority: %d, Message: %s \n", lst->priority, lst->message);
	return(lst);
}
void listprint(struct list *lst) // Print the list
{
	struct list *p;
	p = lst;
	printf("Now we have the list\n");
	do {
		// Print prioity and message of p element
		printf("Priority: %d, Message: %s \n", p->priority, p->message); 
		p = p->ptr; // to the next element
	} while (p != NULL);
	printf( "\n" );
}
/*
The function add element to the not full list 
 */
struct list *justr_add_element(struct list *lst,  struct list *temp)
{
	struct list *temp1, *p;
	temp1 = lst;
	
	int b = 1; // If b = 0 then new element is added to the list
	
	// Add new element to the begining of the list
	if ( temp->priority >= lst->priority ) {
		temp->ptr = lst;
		temp1 = temp;
		b = 0;
	}
	
	// Add element to the end of the list with one element
	if ( ( lst->ptr == NULL ) && ( temp->priority < lst->priority ) ) {
		lst->ptr = temp; // previos node points on the creaing node
		temp->ptr = NULL; // creating node points on the next element
		b = 0;
	}
	
	if ( b ) {		
		p = lst; // save pointer to the next node	
		lst = lst->ptr;
		do {
			if ( temp->priority >= lst->priority ) {
				p->ptr = temp; // previos node points on the creaing node
				temp->ptr = lst; // creating node points on the next element
				b = 0;
			}
			else {
				p = p->ptr;
				lst = lst->ptr;
			}		
		} while ( (lst != NULL) && b );
	}
	
	if ( b ) {
		p->ptr = temp; // previos node points on the creaing node
		temp->ptr = NULL; // creating node points on the next element
	}
	
	return(temp1);
}

/*
The function add element to the full list 
 */
struct list *delete_add_element(struct list *lst, struct list *temp) 
{
	struct list *temp1, *p;
	temp1 = lst;
	
	for (int i = 0; i < CAPACITY-2 ; i++) {
		temp1 = temp1->ptr;
	}
	p = temp1->ptr;
	if (temp->priority > p->priority ) {
		temp1->ptr = NULL; 
		free(p); // Free the memory of the deleting node
		lst = justr_add_element(lst, temp);
	}
	else free(temp);
	
	return(lst);
}

void delete_list(struct list *lst)
{
	struct list *p;
	p = lst;
	
	for (int i = 0; i < CAPACITY-2 ; i++) { 
		lst = lst->ptr;
		free(p);
		p = lst;
	}
	free(lst);
}




