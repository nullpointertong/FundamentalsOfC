
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Structures*/
/*Node Structure in Order to implment a linkedlist*/
struct map {
	int key;
	int value;
};
typedef struct map map_t;

struct node {
    struct node* nextp;
};
typedef struct node node_t;

/*Function Prototypes*/
void insert_hashmap(int *employeeId,map_t hashmap[],int * new_key);
void display_hashmap(int *employeeId,map_t hashmap[],int * new_key);


int main() {
	/* Assuming 10 is the maximum amount this hashmap can store
	*/
	int i;
	int employeeId;
	map_t hashmap[10];
	for(i = 0 ;i<10 ; i++){
    hashmap[i].value = 0;
    hashmap[i].key = 0;
    }
    printf("Enter Employee Id");
    scanf("%d", &employeeId);
    int new_key = employeeId % 10;    
    insert_hashmap(&employeeId, hashmap, &new_key);
    display_hashmap(&employeeId, hashmap, &new_key);
/*
    node_t* linkedListp;
    node_t* index_pointer;
    linkedListp = (node_t*) malloc(sizeof (node_t));
    free(linkedListp);
    linkedListp = NULL;

*/
    return 0;
}


void insert_hashmap(int *employeeId,map_t hashmap[], int *new_key)
{
	/*Please Note Hashmap is implmented in the form h(K) = KmodN where 
	N is number of elements in array and K is key*/
	if(hashmap[*new_key].key == 0 && hashmap[*new_key].value == 0){
	hashmap[*new_key].value = *employeeId; 
    hashmap[*new_key].key = *new_key;
    }
    else if(hashmap[*new_key].key != 0 && hashmap[*new_key].value != 0){
    /*Linear Collision */

    	(*new_key)++;  
    	return insert_hashmap(employeeId,hashmap,new_key);
    }
}

void display_hashmap(int *employeeId,map_t hashmap[],int * new_key)
{
	int i;
	printf("Value Key\n");
	for(i = 0 ; i<10 ; i++){
		printf("%d %d\n",hashmap[i].key, hashmap[i].value);
	}
}

    


