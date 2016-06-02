
//llist.h
//create a singly linked list for struct vary_node as defined in misc_headers.h
//shaumik ashraf

typedef struct vary_node* llist;

void add(llist l, char* nam, double val);
char** get_names(llist l);
double get_value(llist l, char* nam);

