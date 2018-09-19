
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
void insert_hashmap(int *sampleData,map_t hashmap[]);

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
    insert_hashmap(&sampleData, hashmap);
/*
    node_t* linkedListp;
    node_t* index_pointer;
    linkedListp = (node_t*) malloc(sizeof (node_t));
    free(linkedListp);
    linkedListp = NULL;

*/
    return 0;
}


void insert_hashmap(int *sampleData,map_t hashmap[])
{
	/*Please Note Hashmap is implmented in the form h(K) = KmodN where 
	N is number of elements in array and K is key*/
	if(hashmap[*sampleData % 10].key == 0 && hashmap[*sampleData % 10].value == 0){
	hashmap[*sampleData % 10].value = *sampleData; 
    hashmap[*sampleData % 10].key = *sampleData % 10;
    }
    /*else   insert collision handling mech here */

}

