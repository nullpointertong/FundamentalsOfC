#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
void insert_hashmap(int *employeeId,map_t hashmap[],int * new_key);
void display_hashmap(int *employeeId,map_t hashmap[],int * new_key);
/***************************************************/


int main(void) {

    node_t linkList = NULL;
    linkList = malloc(sizeof (node_t));
    startMenu(linkList);
    return 0;
}

void startMenu(node_t linkList)
{
    char input;
    int init = 0;
    int *numUsers = &init; 
     
    printf("1. Login\n"
           "2. Create Account\n");
            
    printf("Option: ");
    scanf("%c", &input);
    
    switch (input) {
        case('1') : {
                        login(linkList);
                        break;
                    }
        case('2') : {   
                        newUser(linkList, numUsers);
                        break;
                    }
        default : printf("Please enter a valid option");
    }
}

void login(node_t linkList) {
    char userlogin[15];
    char userpass[15];

    /* ask for username and password*/
    printf("Username: ");
    scanf("%s", userlogin);

    printf("Password: ");
    scanf("%s", userpass);

    /* use a pointer to traverse the linkedlist*/
    node_t p;
    p = malloc(sizeof (node_t));

    /*traverse linkedlist*/
    for (p = linkList; p != NULL; p = p->nextp) {
        /*compare usernames to information*/
        if (strcmp(p->nextp->user.username, userlogin) == 0) {
            /* compare passwords to password entered*/
            if (strcmp(p->nextp->user.password, userpass) == 0) {
                printf("Welcome, %s", p->nextp->user.username);
                /* go to accountmenu and pass userID*/
                accountMenu(p, linkList);
            } else printf("Wrong Password");
        } else {
            printf("Sorry this username doesn't exist in the system\n");
            login(linkList);
        }
    }
}

void newUser(node_t linkList, int *numUsers) {
    ++(*numUsers);
    node_t newUse, p; /*PS: now these are both pointers
                       *defines 2 new nodes*/

    newUse = malloc(sizeof (node_t));
    p = malloc(sizeof (node_t));
    /*dynamically sets their size*/
    newUse->nextp = NULL;
    /*sets the next node so that NULL will be the next link*/
    p = linkList;
    /*p used to traverse the linklist*/
    if(p->nextp != NULL) {
        p = p->nextp;
    } /*will stop when p=the last node before NULL*/

    /*changes the last node (previous NULL) to another node
                      * which points to NULL*/

    sprintf(p->user.userID, "%d", *numUsers);
    printf("DEBUG USERID IS %s",p->user.userID);
    /*will set the User ID to the number of users in
     * the system (including itself) with the leasing
     * digits being zeros*/

    printf("Enter Your Username> \n");
    scanf("%s", p->user.username);
    printf("Enter Your Password> \n");
    scanf("%s", p->user.password);
    printf("Welcome to Richard and Co Bank!!\n");

    addNewAccount(linkList, p);
}



/* Used as a submenu for functions like Transfer between accounts,
 * Deposit and withdraw. It is an easy and straight forward way to have
 * A submenu */
char miniMenu(char name[], node_t p, node_t linkList)
{
    char garbage;
    garbage = getchar();
    if(garbage);
    
    char input;
    printf("1. %s\n", name);
      printf("2. list Accounts\n"
            "3. Return to Menu\n");
            
    printf("Option: ");
    scanf("%c", &input);
    
    if(input == '2') {listAccounts(p);
                      miniMenu(name, p, linkList);}
    if(input == '3') { accountMenu(p, linkList);};
    return input;
    
}


void accountMenu(node_t p, node_t linkList) {
    char input;
    char garbage;
    garbage = getchar();
    if(garbage != '\0');


    /*Please add number of users here*/

    /* printf("*********************************************************\n"
            "                              $$\n"
            "                          $$$$$$$$$\n"
            "                       $$$$$$$$$$$$$$\n"
            "                      $$$$$$$$$$$$$$$$$\n"
            "                      $$$$$   $$    $$$$$\n"
            "                      $$$$    $$     $$$$$$\n"
            "                      $$$$    $$      $$$$$$\n"
            "                        $$$$\n"
            "                          $$$$$\n"
            "                               $$$$\n"
            "                              $$ $$$$$$$\n"
            "                              $$     $$$$$$\n"
            "                              $$     $$$$$\n"
            "                              $$      $$$$\n"
            "                              $$     $$$$\n"
            "                              $$   $$$$$\n"
            "                       $$$$$$$$$$$$$$$$$$\n"
            "                        $$$$$$$$$$$$$$\n"
            "                              $$\n");
     */
    printf("\n1. Add Account\n"
            "2. Delete Account\n"
            "3. Transfer Between Accounts\n"
            "4. List Accounts\n"
            "5. Pay Others\n"
            "6. Withdraw Money\n"
            "7. Deposit Money\n"
            "0. exit\n");

    printf("Option: ");
    scanf("%c", &input);
    switch (input) {
            /*waiting till each function is finished to connect them.*/
        case('1'): {addNewAccount(linkList, p);
                    break;}
        case('2'): printf("DeleteAccount"); 
                    break;
        case('3'): TransferMoney(p, linkList);
                    break;
        case('4'): {listAccounts(p);
                    accountMenu(p, linkList);
                    break;}
        case('5'): PayUser(p, linkList);
                    break;
        case('6'): withdrawMoney(p, linkList);
                    break;
        case('7'): depositMoney(p, linkList);
                    break;
        case('0'): exit(0);
        default: printf("Please enter an option 1-7 or quit with 0\n");
        /*
    int i;
    map_t hashmap[10];
    for(i = 0 ;i<10 ; i++){
    hashmap[i].value = 0;
    hashmap[i].key = 0;
    }
Replace .value with information you want*/
    }
}

void addNewAccount(node_t linkList, node_t p) {
    /*char* currentID = userID;
    printf("Your user ID is %s", currentID);
    */
    char garbage;
    garbage = getchar();
    if(garbage != '\0');
    char action;
    
  
    printf("Do you wannt to add a new account, please enter 'y' or 'n' for next processing\n");
    scanf("%c", &action);
    
    if (action == 'y' || action == 'Y')
    {
        
      
        if (p->user.numAccounts >= 5) 
        {
             /*if more than 5 accounts*/
            printf("Sorry, the quota for accounts of user is full\n");
                    
        } else {
                    /* This function is broken*/
                    int currentNum = p->user.numAccounts;
                    char* newAccountID = p->user.userID + currentNum;  /*create new account ID*/
                    strcpy(p->user.account[currentNum].accountID, newAccountID);
                    p->user.account[currentNum].accountValue = 0;
                    printf("Your new account has been added successfully\n");
                    printf("Account ID is %s and value is $%.2lf\n",
                           p->user.account[currentNum].accountID,
                           p->user.account[currentNum].accountValue);
                }
    } else if (action == 'n' || action == 'N') 
    {
        accountMenu(p, linkList);
    } 
    else if (action != 'n' || action != 'N')
    {
        printf("Please neter valid input\n");
    }
}



void TransferMoney(node_t p, node_t linkList) {
    /*Transfer money from one account into another account*/
    char accountID1[10];
    char accountID2[10];
    double amount;
        if(miniMenu("Transfer", p, linkList) == '1')
        {
            char garbage;
            garbage = getchar();
            if(garbage);
       /* if (strcmp(p->nextp->user.userID, userid) == 0) {*/
            printf("What account would you like to transfer from?");
            scanf("%s", accountID1);

            printf("Destination account: ");
            scanf("%s", accountID2);

            printf("Amount: ");
            scanf("%lf", &amount);
                /*get 2 accountsID to be transferred from*/

            int j;
            for (j = 0; j < 6; j++) {
                if ((strcmp(p->user.account[j].accountID, accountID1))==0) {  /*doesnt it produce 0 if is equal?-changed**/
                    p->user.account[j].accountValue = p->nextp->user.account[j].accountValue - amount; /*amount subtracted from account*/
                    int k;
                    for (k = 0; k < 6; k++) {
                        if ((strcmp(p->user.account[j].accountID, accountID2))== 0) {  /*shouldnt this be accountID2-changed**/
                            p->user.account[k].accountValue = p->nextp->user.account[k].accountValue + amount; /*amount added added to account 2*/
                            printf("Money successfully Transferred\n");
                            accountMenu(p, linkList);
                        } else {
                            printf("Transfer unsuccessful, please check you have the right account\n");
                            p->user.account[j].accountValue = p->nextp->user.account[j].accountValue + amount; /*shouldnt this be plus not minus-changed* */
                            TransferMoney(p, linkList);
                        }
                    }

                } else {
                    printf("Sorry the account your trying to"
                            " transfer from doesn't exist\n");

                    TransferMoney(p, linkList);
                }
            }
        }
    
}

node_t PayUser(node_t p, node_t linkList) {
    char id[15];
    double amount;
    char accountID1[10];
    char accountID2[10];

    printf("What is the userid of the user you want to pay ?\n");
    scanf("%s", id);

    printf("How much do you want to pay ?\n");
    scanf("%lf", &amount);

    printf("What is the account number you want to pay ?\n");
    scanf("%s", accountID2);

    printf("With which account do you want to pay?\n");
    scanf("%s", accountID1);
    /*gets info for transfer, */

    node_t i;
    i = malloc(sizeof (node_t)); /*sets pointer for the unknown node*/
    for (i = linkList; i != NULL; i = i->nextp) {
        if (strcmp(i->nextp->user.userID, id) == 0) { /*finds unknown node using userID*/
            int j;
            for (j = 0; j < 6; j++) {
                if (strcmp(i->user.account[j].accountID, accountID2) == 0) { /*locate account for user i*/
                    i->user.account[j].accountValue = i->nextp->user.account[j].accountValue + amount; /*pay user i*/
                    /* minus the original account!!*/
                    for(j = 0; j < 6; j++)
                    {
                        if (strcmp(p->nextp->user.account[j].accountID, accountID1) == 0) /*locate account of user p*/
                        {
                            p->nextp->user.account[j].accountValue = p->nextp->user.account[j].accountValue - amount; /*deduct cash for user p*/
                        }
                        
                    }
                    printf("Mr/Miss %s has been paid \n", id);
                } else {
                    printf("No account found with that account number \n");
                }
            }
        } else {
            printf("No user find with that id \n");
        }

    }
    free(i);
    return p;
}

void listAccounts(node_t p)
{   
    int j;
    for (j = 0; j < 6; j++) 
    {
        printf("%d Account: %s Value: $%.2lf \n", j+1, 
        p->nextp->user.account[j].accountID, 
        p->nextp->user.account[j].accountValue);
    }
    
}
    
void withdrawMoney(node_t p, node_t linkList) {
    
    char accountID1[15];
    double amount;
    int found = 0;
    
    /*node_t i;
    i = malloc(sizeof (node_t));
    for (i = linkList; i != NULL; i = i->nextp) {
        if (strcmp(i->user.userID, userid) == 0) {*/
        
    /* Mini Withdraw Menu, like in the Deposti function*/
   
    if(miniMenu("Withdraw Money", p, linkList) == '1')
    {
            char garbage;
            garbage = getchar();
            if(garbage);
            
            printf("What account would you like to withdraw from? ");
            fgets(accountID1, 10, stdin);

            printf("Amount: ");
            scanf("%lf", &amount); /*get info for withdraw*/


            int j;
            for (j = 0; j < 6; j++) {
            /* I can't get rid of the \n so strcmp reads for comparison plus \n*/
                if ((strcmp(p->nextp->user.account[j].accountID, 
                accountID1)) == -10) { /*search for account */
                    if (p->nextp->user.account[j].accountValue < amount)
                    {
                        printf("Insufficient Funds\n");
                        
                        withdrawMoney(p, linkList);
                    }
                    p->user.account[j].accountValue = 
                    p->user.account[j].accountValue - amount; 
                    /*deduct value from account*/
                    printf("withdraw successfull\n");
                    found = 1;
                    withdrawMoney(p, linkList);


                } 
                if(j == 5 && found == 0)
                {
                    printf("Sorry the account your trying to"
                            " withdraw from doesn't exist\n");

                    withdrawMoney(p, linkList);
                }

        }
    }
        
}


void depositMoney(node_t p, node_t linkList) {
    
    char accountID1[15];
    double amount;
    int found = 0; /* used to match when searching accounts*/
    
    
    if((miniMenu("Deposit Money", p, linkList) == '1'))
    {
            /* clean stdin to prevent overflow*/
        char garbage;
        garbage = getchar();
        if(garbage);
            
        printf("What account would you like to Deposit to? ");
        fgets(accountID1, 10, stdin);
        printf("Amount: ");
        scanf("%lf", &amount); /*get info for deposit*/
            

        int j;
            for (j = 0; j < 6; j++) 
            {
                /* I can't get rid of the \n so strcmp reads for comparison plus \n*/
                if (((strcmp(p->nextp->user.account[j].accountID, 
                    accountID1)) == -10) && found == 0) 
                    {
                    
                    p->nextp->user.account[j].accountValue 
                    = p->nextp->user.account[j].accountValue + amount; 
                    /*add amount to account*/
                    printf("deposit successfull\n");
                    found = 1;
                    
                    depositMoney(p, linkList);

                    }else
                        if(j == 5 && found == 0)
                        {
                            printf("Sorry the account your trying to"
                            " deposit to doesn't exist\n");
                
                            depositMoney(p, linkList);
                        } 
            }
    }
}


int writeFile(node_t linkList, int numUsers) {
    FILE*fp;

    fp = fopen("Database.txt", "w");

    if (fp == NULL) /*if file fails to open function ends*/ {
        return 0;
    }

    if (numUsers == 0) /*if there is no data to write function ends*/ {
        return 0;
    }

    fprintf(fp, "%d ", numUsers); /*prints number of uses, used when reading
                                   * the file*/
    node_t p;
    p = malloc(sizeof (node_t));
    /*sets data size for pointer*/
    int count; /*used to count through user accounts*/
    for (p = linkList; p != NULL; p = p->nextp)
        /*prints each value for each user until the next */ {
        fprintf(fp, "%s %s %s %d ", p->user.userID, p->user.username,
                p->user.userID, p->user.numAccounts);
        /*numAccounts used to determine how many accounts to print*/

        for (count = 0; count < p->user.numAccounts; ++count) {
            fprintf(fp, "%s %lf ", p->user.account[count].accountID,
                    p->user.account[count].accountValue);
            /*prints account num and value for each account he user has*/
        }
    }
    fclose(fp);
    free(p);
    p = NULL; /*frees the storage space*/
    return 1; /*writing to file was successful*/
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
        printf("%d %d\n",hashmap[i].value, hashmap[i].key);
    }
}




