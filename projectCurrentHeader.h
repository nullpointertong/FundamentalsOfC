#ifndef PROJECT_HEADER_OMEGA_H
/*********Structures********************/
/*Node Structure in Order to implment a linkedlist*/
struct account {
    char accountID[10];
    double accountValue;
    int availableFlag;
};
typedef struct account account_t;

struct user {
    char username[10];
    char password_1[10];
    char userID[6];
    /*made 6 for \0*/
    account_t account[6];
    int numAccounts;
    
    /*added, useful when writing to file*/
    int suFlag;
    /*Checks if user has su i.e(admin) rights
    to add or modify details*/
};
typedef struct user user_t;

struct node {
    struct node* nextp;
    user_t user;
};
typedef struct node* node_t;

/* The First value a pointer*/

struct map {
    int key;
    int value;
};
typedef struct map map_t;
/****************************************/

/**************Prototypes*************************/
node_t login(node_t linkList, node_t p, int debugFlag);
char accountMenu();
int addNewAccount(node_t linkList, node_t p, int debugFlag);
void TransferMoney(node_t p, node_t linkList, int debugFlag);
void withdrawMoney(node_t p, node_t linkList, int debugFlag);
int depositMoney(node_t p, node_t linkList, int debugFlag);
node_t newNode(node_t linkList, node_t p);
node_t newUser(node_t linkList, int *numUsers, node_t p, int debugFlag);
int writeFile(node_t p, int* numUsers);
node_t userMenu(node_t linkList, node_t p, int *debugFlag, int *numUsers);
void listAccounts(node_t p);

void insert_hashmap(int *employeeId, map_t hashmap[], int * new_key);
void display_hashmap(int *employeeId, map_t hashmap[], int * new_key);
int writeFileV3(node_t linkList, int* numUsers);
int readFile(node_t linkList, node_t p, int* numUsers);
char * encrypt(char * encryptMessage, int messageLength, char * key, int keyLength);
/***************************************************/
#endif
