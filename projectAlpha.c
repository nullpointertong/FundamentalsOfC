#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct account {
    char accountNum[10];
    int accountValue;
};
typedef struct account account_t;

struct user {
    char username[15];
    char password[15];
    char userID[6];
    account_t account[5];
};
typedef struct user user_t;

struct node {
    struct node* nextp;
    user_t user;
};
typedef struct node *node_t; /* PS: made the first value a pointer*/




/*Prototypes*****************************/
node_t readFile();
int writeFile(node_t linkList);
node_t newUser(node_t linkList, int numUsers);
void accountMenu(node_t linkList);

void addNewAccount(node_t linklist, char userID[]); /*Added userID*/
void PayUser(node_t linkList, int amount);
void TransferMoney(char accountNum1[],char accountNum2[],int amount);
void WhitdrawMoney(char accountNum[],int amount);
void DepositMoney(char accountNum[],int amount);
/***************************************************/

node_t newUser(node_t linkList, int numUsers)
{
    ++numUsers;
    node_t newUse, p; /*PS: now these are both pointers
                       *defines 2 new nodes*/
    
    newUse=(node_t)malloc(sizeof(node_t));
    p=(node_t)malloc(sizeof(node_t));
                      /*dynamically sets their size*/
    newUse->nextp=NULL;
                      /*sets the next node so that NULL will be the next link*/
    p=linkList;
                      /*p used to traverse the linklist*/
    while(p->nextp!=NULL)
    {
        p= p->nextp;
    }                 /*will stop when p=the last node before NULL*/
    
    p->nextp=newUse; /*changes the last node (previous NULL) to another node
                      * which points to NULL*/
    
   int count;
    for(count=0; count<5; ++count)
    {
        p->nextp->user.userID[count]='0';
    }
    
    p->nextp->user.userID[5]= numUsers;
                            /*will set the User ID to the number of users in
                             * the system (including itself)*/
                            
    printf("Enter Your Username> \n");
    scanf("%s", p->nextp->user.username);
    printf("Enter Your Password> \n");
    scanf("%s", p->nextp->user.password);
    printf("Welcome to Richard and Co Bank!!\n");
    
    addNewAccount(linkList, p->nextp->user.userID);
    
   return linkList;
    
}