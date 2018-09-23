
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
void insert_hashmap(int *sampleData,map_t hashmap[],int * new_key);

int main() {
	/* Assuming 10 is the maximum amount this hashmap can store
	*/
	int i;
	int sampleData = 10;
	map_t hashmap[10];
	for(i = 0 ;i<10 ; i++){
    hashmap[i].value = 0;
    hashmap[i].key = 0;
    }
    int new_key = sampleData % 10;    
    insert_hashmap(&sampleData, hashmap, &new_key);
/*
    node_t* linkedListp;
    node_t* index_pointer;
    linkedListp = (node_t*) malloc(sizeof (node_t));
    free(linkedListp);
    linkedListp = NULL;

*/
    return 0;
}


void insert_hashmap(int *sampleData,map_t hashmap[], int *new_key)
{
	/*Please Note Hashmap is implmented in the form h(K) = KmodN where 
	N is number of elements in array and K is key*/
	if(hashmap[*new_key].key == 0 && hashmap[*new_key].value == 0){
	hashmap[*new_key].value = *sampleData; 
    hashmap[*new_key].key = *new_key;
    }
    else if(hashmap[*new_key].key != 0 && hashmap[*new_key].value != 0){
    	(*new_key)++;  
    	return insert_hashmap(sampleData,hashmap,new_key);
    }
    
}


