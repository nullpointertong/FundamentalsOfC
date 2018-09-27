#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct account {
    char accountNum[10];
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
void accountMenu(node_t linkList);

void addNewAccount(node_t linklist, char userID[]); /*Added userID*/
void PayUser(node_t linkList, int amount);
void TransferMoney(char accountNum1[],char accountNum2[],int amount);
void WhitdrawMoney(char accountNum[],int amount);
void DepositMoney(char accountNum[],int amount);
/***************************************************/

int main(void)
{
    return 0;
}
node_t newUser(node_t linkList, int *numUsers)
{
    ++*numUsers;
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
    
   
    
    sprintf(p->nextp->user.userID,"05%d", *numUsers);
                            /*will set the User ID to the number of users in
                             * the system (including itself) with the leasing
                             * digits being zeros*/
                            
    printf("Enter Your Username> \n");
    scanf("%s", p->nextp->user.username);
    printf("Enter Your Password> \n");
    scanf("%s", p->nextp->user.password);
    printf("Welcome to Richard and Co Bank!!\n");
    
    addNewAccount(linkList, p->nextp->user.userID);
    
    free(p);
    p=NULL; /*frees the storage space*/
    
   return linkList;
    
}

int writeFile(node_t linkList, int numUsers)
{
    FILE*fp;
    
    fp=fopen("Database.txt", "w");
    
    if(fp==NULL) /*if file fails to open function ends*/
    {
        return 0;
    }
    
    if(numUsers==0) /*if there is no data to write function ends*/
    {
        return 0;
    }

    fprintf(fp, "%d ", numUsers); /*prints number of uses, used when reading
                                   * the file*/
    
    node_t p;
    p=(node_t)malloc(sizeof(node_t));
                                 /*sets data size for pointer*/
    int count;                   /*used to count through user accounts*/
    
    for(p=linkList; p!=NULL; p=p->nextp)
          /*prints each value for each user until the next */
    {
        fprintf(fp, "%s %s %s %d ", p->user.userID, p->user.username,
                                 p->user.userID, p->user.numAccounts);
          /*numAccounts used to determine how many accounts to print*/
          
        for(count=0; count<p->user.numAccounts; ++count)
        {
            fprintf(fp, "%s %lf ", p->user.account[count].accountNum,
                                   p->user.account[count].accountValue);
            /*prints account num and value for each account he user has*/
        }
    }
    
    fclose(fp);
    
    free(p);
    p=NULL; /*frees the storage space*/
    
    return 1; /*writing to file was successful*/
}
