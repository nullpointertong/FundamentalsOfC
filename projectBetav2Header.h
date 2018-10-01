#ifndef PROJECTHEADER_H
#define PROJECTHEADER_H

/*********Structures********************/
/*Node Structure in Order to implment a linkedlist*/
struct account {
    char accountID[10];
    double accountValue;
};
typedef struct account account_t;

struct user {
    char username[15];
    char password[15];
    char userID[6];
    /*made 6 for \0*/
    account_t account[6];
    int numAccounts;
    /*added, useful when writing to file*/
};
typedef struct user user_t;

struct node {
    struct node* nextp;
    user_t user;
};
typedef struct node *node_t;
/* The First value a pointer*/

struct map {
    int key;
    int value;
};
typedef struct map map_t;
/****************************************/

/**************Prototypes*************************/
void login(node_t linkList);
void accountMenu(node_t p, node_t linkList);
void addNewAccount(node_t linkList, node_t p); /*Added userID*/
void TransferMoney(node_t p, node_t linkList);
node_t PayUser(node_t p, node_t linkList);
void withdrawMoney(node_t p, node_t linkList);
void depositMoney(node_t p, node_t linkList);
void newUser(node_t linkList, int *numUsers);
int writeFile(node_t linkList, int numUsers);
node_t readFile();
void deleteAccount(node_t p);
void startMenu(node_t linkList);
void listAccounts(node_t p);
char miniMenu(char name[], node_t p, node_t linkList);
/***************************************************/

#endif
