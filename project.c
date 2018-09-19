
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Function Prototypes*/


/*Structures*/
/*Node Structure in Order to implment a linkedlist*/
struct node {
    struct node* nextp;
};
typedef struct node node_t;




int main() {
    node_t* linkedListp;
    node_t* index_pointer;
    linkedListp = (node_t*) malloc(sizeof (node_t));
    free(linkedListp);
    linkedListp = NULL;
    return 0;
}

