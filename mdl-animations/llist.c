
//llist.c
//define singly linked list for struct vary_node
//shaumik ashraf

#include"misc_headers.h"
#include"

void add(llist l, char* nam, double val) {

	struct vary_node* n;

	n = (struct vary_node*)malloc(sizeof(struct vary_node));

	strcpy(n->name, nam);
	n->value = val;
	n->next = NULL;

	while( l->next!=NULL ) {
		l = l->next;
	}

}
