#ifndef PROJECTHEADER_H
#define PROJECTHEADER_H
	
struct account {
    char accountID[10];
    double accountValue;
};
typedef struct account account_t;

struct user {
    char username[15];
    char password[15];
    char userID[6];   /*made 6 for \0*/
    account_t account[6];
    int numAccounts;  /*added, useful when writing to file*/
};
typedef struct user user_t;

struct node {
    struct node* nextp;
    user_t user;
};
typedef struct node *node_t; /* PS: made the first value a pointer*/

/*Prototypes*****************************/
node_t readFile();
int writeFile(node_t linkList, int numUsers);
node_t newUser(node_t linkList, int *numUsers);
void accountMenu(node_t linkList, char userID[]);

void addNewAccount(node_t linklist, char userID[]); /*Added userID*/
void PayUser(node_t linkList, char userID[]);
void TransferMoney(node_t linkList, char userid[]);
void withdrawMoney(node_t linkList, char userid[]);
void depositMoney(node_t linkList, char userid[]);
void deleteAccount(char accountID[]);
void login(node_t linkList);
/***************************************************/

#endif