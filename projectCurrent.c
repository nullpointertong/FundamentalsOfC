/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Leader: Richard Tong
 * Group Members: JiaJian
 * Student ID: 13238528
 * Date of submission: 7/09/2018
 *
*******************************************************************************/

/*******************************************************************************
 * List header files:
*******************************************************************************/
#include "projectCurrentHeader.h"
#include <stdio.h> /*fopen,fclose,fgets,fprintf,printf,sprintf,fscanf,scanf */
#include <stdlib.h> /*malloc,exit */
#include <string.h> /*strcmp,strcat,strlen,strcpy*/

/*******************************************************************************
 * List preprocessing directives:
*******************************************************************************/
#define MAX 256
#define DATABASE "Database.txt"
#define DATABASETEMP "Database.tmp"

/*******************************************************************************
 * Main:
 * This function starts by printing the menu for the users to navigate through
 * the program. It also initializes the linked list, the data type that is used
 * to hold user information.
 * Inputs:
 * NONE
 * Outputs:
 * node_t linkedList : head for the linkedlist p
 * node_t p : linked list used to hold user info throughout the program.
*******************************************************************************/
int main(void) {

    node_t linkList;
    linkList = malloc( sizeof (node_t)); /*initialise the linkList*/
    int *numUsers=0;
    numUsers = malloc( sizeof (int)*1); /*initialise numUsers*/
    node_t p;
    p=malloc( sizeof (node_t)*1);
    int debugFlag = 0;
    
    FILE *fp;
    fp = fopen(DATABASE, "rb");    
    if (fp == NULL){
    
    }
    else{
        doDecompress();
        fclose(fp);
    }
    fclose(fp);
    
    
    
    if(readFile(linkList, p, numUsers)==0)
    {
        printf("Error: Data was unable to load\n");
    }
    
    p= userMenu(linkList, p, &debugFlag, numUsers); /*go to start menu and get user option*/
    
    /*will loop until a valid input is added*/
    char input = 'a';
    while (input != '0') {
        
        input = accountMenu();
        
        switch (input) {
            /*waiting till each function is finished to connect them.*/
            case ('1'):
            {
                p=userMenu(linkList, p ,&debugFlag, numUsers);
                break;
            }
            case ('2'):
                while (addNewAccount(linkList, p, debugFlag) == 0);
                break;
            
            case ('3'):
            {
                listAccounts(p);
                break;
            }
            case ('4'):
                TransferMoney(p, linkList, debugFlag);
                break;
            case ('5'):
                withdrawMoney(p, linkList, debugFlag);
                break;
            case ('6'):
                depositMoney(p, linkList, debugFlag);
                break;
            case ('0'):
            {
                
                    if(writeFileV3(linkList, numUsers)==0)
                        printf("write failure");
                
                exit(0);
            }
            default:
            {
                printf("Please enter an option 1-6 or quit with 0\n");
                if (debugFlag == 1)
                    printf("\n\nDEBUG: input =%c\n", input); /*debug*/
            }
            
        }
    }
    
    return 0; 
}

/*******************************************************************************
 * This function, called by the main displays an option for the user to create 
 * a user account or to login with existing details.
 * inputs:
 * - node_t linkedList : head of our linkedlist used to store user info.
 * - node_t p : The actual linkedlist used to store info.
 * - int *debugFlag : a pointer used to indicate whether the program is in
 *   debug mode or not.
 * - int *numUsers : a pointer used to store the number of users created.
 * outputs:
 * - node_t p : updates p if a new user is created.
 * - p->user.username : username of the user.
 * - p->user.password_1 : password of the user.
 * - int *debugFlag : used to signify to go into debug mode or not.
*******************************************************************************/
node_t userMenu(node_t linkList, node_t p, int *debugFlag, int *numUsers) {
    char input;
    
    
    while ((input != '1') && (input != '2')) {
        printf("1. Login\n"
               "2. Create User Account\n"
               "3. Exit\n");
        
        printf("Option: ");
        scanf(" %c", &input);
        
        
        switch (input) {
            case ('1') : {
                printf("user:::%s",linkList->nextp->user.username);
                p=login(linkList, p,  *debugFlag);
                if (*debugFlag == 1) /*debug*/
                    printf("\nDEBUG: \np->user.username= %s \np->user.password_1= %s \n", p->user.username, p->user.password_1);
                break;
            }
            case ('2') : {
                p = newUser(linkList, numUsers, p, *debugFlag);
                while (addNewAccount(linkList, p, *debugFlag) == 0);
                break;
            }
            case ('3'):
                exit(0);
            case ('d'): /*toggles debug mode on or off*/
            case ('D'): {
                if (*debugFlag == 0) {
                    *debugFlag = 1; /*on*/
                    printf("\nDEBUG mode: on\n");
                } else if (*debugFlag == 1) {
                    *debugFlag = 0; /*off*/
                    printf("\nDEBUG mode: off\n");
                }
            }
            default:
                printf("Please enter a valid option\n");
                if (*debugFlag == 1)
                    printf("\nDEBUG: input_s =%c\n", input);
        }
    }
    
    return p;
}

/*******************************************************************************
 * This function lets the user login to the program. In so doing p now contains
 * the users information.
 * inputs:
 * - node_t linkedList : head of our linkedlist used to store user info.
 * - node_t p : The actual linkedlist used to store info.
 * - int debugFlag : a pointer used to indicate whether the program is in
 *   debug mode or not.
 * outputs:
 * - node_t p : updates p with the information of that user. 
*******************************************************************************/
node_t login(node_t linkList, node_t p, int debugFlag) {
    char userlogin[15];
    char userpass[15];
    int found=0;
    char * key = "@#$%*&()@#$%*&()";
    p=NULL;
    
    printf("user:::%s",linkList->nextp->user.username);
    /* ask for username and password*/
    printf("Username: ");
    scanf("%s", userlogin);
    
    printf("Password: ");
    scanf("%s", userpass);
    
    if (debugFlag == 1) /*debug*/
        printf("\nDEBUG: \nuserlogin =%s\nuserpass= %s \n", userlogin, userpass);
    
    /* use a pointer to traverse the linkedlist*/
    
    /*traverse linkedlist*/
    for (p = linkList->nextp; p!=NULL; p = p->nextp) {
        /*compare usernames to information*/
        if (debugFlag == 1) /*debug*/
            printf("\nDEBUG: \n"
                   "current p->user.username =%s\n"
                   "current p->user.password =%s\n", p->user.username,
                   p->user.password_1);
        if (strcmp(encrypt(p->user.username,key), userlogin) == 0) {
            /* compare passwords to password entered*/
            if (strcmp(encrypt(p->user.password_1,key), userpass) == 0) {
                printf("Welcome, %s",p->user.username);
                found = 1;
                
                break;
                /* go to accountmenu and pass userID*/
            } else printf("Wrong Password");
            
        }
    }
    if(found==0)
    {
        printf("Sorry this username doesn't exist in the system\n");
        login(linkList, p, debugFlag);
    }
    if (debugFlag == 1) /*debug*/
        printf("\nDEBUG: \np->user.username= %s \np->user.password_1= %s \n", p->user.username, p->user.password_1);
    
    return p;
}



/*******************************************************************************
 * This function is used to dynamically expand the linkList to hold more data.
 * inputs:
 * - node_t linkedList : head of our linkedlist used to store user info.
 * - node_t p : The actual linkedlist used to store info.
 * outputs:
 * - node_t p : Adds an other node to the linkedlist p.
*******************************************************************************/
node_t newNode(node_t linkList, node_t p)
{

    p=NULL;


    /*sets the next node so that NULL will be the next link*/
    p = linkList;
    /*p used to traverse the linklist*/
        while (p->nextp != NULL) 
            {
            p = p->nextp;
            } /*will stop when p=the last node before NULL*/

    /*changes the last node (previous NULL) to another node
    * which points to NULL*/

    node_t newUse = NULL;
    newUse = malloc(sizeof(node_t)*1000);
    newUse->nextp = NULL;
    p->nextp = newUse;
    p = p->nextp;
    return p;
}

/*******************************************************************************
 * This function lets the user create a new user. In so doing this function,
 * creates a new node in p and updates p with the username and password for
 * the new user.
 * inputs:
 * - node_t linkedList : head of our linkedlist used to store user info.
 * - node_t p : The actual linkedlist used to store info.
 * - int debugFlag : a pointer used to indicate whether the program is in
 *   debug mode or not.
 * - int *numUsers : this variable is used to keep track of the number of users.
 * outputs:
 * - node_t p : updates p with the username and password of a new user.
 * - int *newUsers : add one to newUsers to indicate a newUser was added.
*******************************************************************************/
node_t newUser(node_t linkList, int *numUsers, node_t p, int debugFlag) {
    
    ++(*numUsers);
    
   p=newNode(linkList,p);
    /*dynamically sets their size*/
    sprintf(p->user.userID, "%d", *numUsers);
    
    /*will set the User ID to the number of users in
     * the system (including itself) with the leasing
     * digits being zeros*/
    
    printf("Enter Your Username> \n");
    scanf("%s", p->user.username);
    printf("Enter Your Password> \n");
    scanf("%s", p->user.password_1);
    printf("Welcome to Richard and Co Bank!!\n");
    if (debugFlag == 1) /*debug*/
        printf("\nDEBUG: \n"
               "p->user.username= %s\n"
               "p->user.password= %s\n", p->user.username,
               p->user.password_1);
    
    p->user.numAccounts = 0;
    
   
    
    if (debugFlag == 1) /*debug*/
        printf("\nDEBUG: \n"
               "p->user.username= %s\n"
               "p->user.password= %s\n", p->user.username, p->user.password_1);
    
    return p;
}

/*******************************************************************************
 * This function prints the menu the user sees once they login. It shows to the
 * main function how to navigate to the rest of the programs functions.
 * inputs:
 * - NONE
 * outputs:
 * - NONE
*******************************************************************************/

char accountMenu() {
    char input;
    char garbage;
    garbage = getchar();
    if (garbage != '\0');
    
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
    printf("\n1. User Menu\n"
           "2. Add Account\n"
           "3. List Accounts\n"
           "4. Transfer Between Accounts\n" /* new user*/
           "5. Withdraw Money\n"
           "6. Deposit Money\n"
           "0. exit\n");
    
    printf("Option: ");
    scanf("%c", &input);
   
    return input;
}
/*******************************************************************************
 * This function lets the user add a new bank account. A user can have a max
 * of 5 bank accounts.
 * inputs:
 * - node_t linkedList : head of our linkedlist used to store user info.
 * - node_t p : The actual linkedlist used to store info.
 * - int debugFlag : a pointer used to indicate whether the program is in
 *   debug mode or not.
 * outputs:
 * - node_t p : updates p with a new bank account.
 * - p->user.numAccounts : adds one if a new account is made
 * - p->user.account[currentNum].accountID : Initializes the new Account ID
 * - p->user.account[currentNum].accountValue : Initializes the amount of money
 *   int the users new account.
 * - p->user.account[currentNum].availableFlag : Sets a flag so the account can
     be accessed.
*******************************************************************************/
int addNewAccount(node_t linkList, node_t p, int debugFlag) {
    
    char garbage;
    garbage = getchar();
    if (garbage);
    
    char action;
    
    printf("Do you wannt to add a new account,please enter 'y' or 'n' for next processing\n");
    scanf("%c", &action);
    
    if (debugFlag == 1) /*debug*/
        printf("\nDEBUG: action= %c\n", action);
    
    if (action == 'y' || action == 'Y') {
        if (debugFlag == 1) /*debug*/
            printf("\nDEBUG: p->user.numAccounts= %d\n", p->user.numAccounts);
        
        if (p->user.numAccounts >= 5) {
            /*if more than 5 accounts*/
            printf("Sorry, the quota for accounts of user is full\n");
            return 1;
            
        } else {
            
            char newAccountID[10];
            int currentNum = p->user.numAccounts;
            
            sprintf(newAccountID, "%d%d", p->user.numAccounts, currentNum);
            /*creates newAccountID= username+numaccounts*/
            if (debugFlag == 1) /*debug*/
                printf("\nDEBUG: newAccountID= %s\n", newAccountID);
            strcpy(p->user.account[currentNum].accountID, newAccountID);
            /*copies newAccountID to linklist*/
            p->user.account[currentNum].accountValue = 0;
            p->user.account[currentNum].availableFlag = 1;
            printf("Your new account has been added successfully\n");
            printf("Account ID is %s and value is $%.2lf\n",
                   p->user.account[currentNum].accountID,
                   p->user.account[currentNum].accountValue);
            p->user.numAccounts = p->user.numAccounts + 1;
            
            if (debugFlag == 1) /*debug*/
                printf("\nDEBUG: \n"
                       "p->user.numAccounts= %d\n"
                       "p->user.account[currentNum].availableFlag= %d\n",
                       p->user.numAccounts,
                       p->user.account[currentNum].availableFlag);
            return 1;
            
        }
    } else if (action == 'n' || action == 'N') {
        return 1;
    } else if (action != 'n' || action != 'N') {
        printf("Please enter valid input\n");
    }
    return 0;
}

/*******************************************************************************
 * This function lets the user Transfer funds between bank accounts.
 * inputs:
 * - node_t linkedList : head of our linkedlist used to store user info.
 * - node_t p : The actual linkedlist used to store info.
 * - int debugFlag : a pointer used to indicate whether the program is in
 *   debug mode or not.
 * outputs:
 * - node_t p : Updates p with the new information of the funds of the his/her 
 *   bank account.
 * - p->user.account[j].accountValue : Decreases the account money was 
 *   transfered from.
 * - p->user.account[k].accountValue : Increases the account money was 
 *   transfered to.
*******************************************************************************/
void TransferMoney(node_t p, node_t linkList, int debugFlag) {
    /*Transfer money from one account into another account*/
    char accountID1[10];
    char accountID2[10];
    double amount;
    char garbage;
    garbage = getchar();
    if (garbage);
    /* if (strcmp(p->nextp->user.userID, userid) == 0) {*/
    printf("What account would you like to transfer from? ");
    scanf("%s", accountID1);
    
    printf("Destination account: ");
    scanf("%s", accountID2);
    
    printf("Amount: ");
    scanf(" %lf", &amount);
    /*get 2 accountsID to be transferred from*/
    
    int j;
    int once = 0;
    for (j = 0; j < 6; j++) {
        
        if ((strcmp(p->user.account[j].accountID, accountID1)) == 0) {
            if (p->user.account[j].accountValue >= amount) { /*doesnt it produce 0 if is equal?-changed**/
                p->user.account[j].accountValue = p->user.account[j].accountValue - amount; /*amount subtracted from account*/
                
                if (debugFlag == 1) /*debug*/
                    printf("\nDEBUG: \n"
                           "Amount= %.2lf\n"
                           "p->user.account[j].accountValue= %.2lf\n",
                           amount,
                           p->user.account[j].accountValue);
                
            } else {
                printf("Insufficient Funds\n");
                once = 1;
                if (debugFlag == 1) /*debug*/
                    printf("\nDEBUG: \n"
                           "Amount= %.2lf\n"
                           "p->user.account[j].accountValue= %.2lf\n",
                           amount,
                           p->user.account[j].accountValue);
                return;
            }
            int k;
            for (k = 0; k < 6; k++) {
                if ((strcmp(p->user.account[k].accountID, accountID2)) == 0 && once == 0) { /*shouldnt this be accountID2-changed**/
                    p->user.account[k].accountValue = p->user.account[k].accountValue + amount; /*amount added added to account 2*/
                    printf("Money successfully Transferred\n");
                    once = 1;
                    if (debugFlag == 1) /*debug*/
                        printf("\nDEBUG: \n"
                               "p->user.account[k].accountID= %s\n"
                               "p->user.account[k].accountValue= %.2lf\n",
                               p->user.account[k].accountID,
                               p->user.account[k].accountValue);                                                           
                }                
            }
        } else if (((strcmp(p->user.account[j].accountID, accountID2) || (strcmp(p->user.account[j].accountID, accountID1))) != 0 && once == 0)) {
            printf("Transfer unsuccessful, please check you have the right account\n");
            
            once = 1;
            if (debugFlag == 1) {
                /*debug*/
                printf("\nDEBUG: \n"
                       "p->user.account[j].accountID = %s\n"
                       "Input ACCOUNTID = %s\n"
                       "Input ACCOUNTID2 = %s\n",
                       p->user.account[j].accountID, accountID1,
                       accountID2);
                listAccounts(p);
            }
        }
    }
    
}

/*******************************************************************************
 * This function lets the user view his/her bank account ID and funds.
 * inputs:
 * - node_t p : The actual linkedlist used to store info.
 * outputs:
 * NONE
*******************************************************************************/
void listAccounts(node_t p) {
    int j;
    for (j = 0; j < 6; j++) {
        if (p->user.account[j].availableFlag == 1) {
            printf("%d Account: %s Value: $%.2lf \n", j + 1,
                   p->user.account[j].accountID,
                   p->user.account[j].accountValue);
        }
    }
}
/*******************************************************************************
 * This function lets the user Withdraw funds of his/her bank accounts.
 * inputs:
 * - node_t linkedList : head of our linkedlist used to store user info.
 * - node_t p : The actual linkedlist used to store info.
 * - int debugFlag : a pointer used to indicate whether the program is in
 *   debug mode or not.
 * outputs:
 * - node_t p : Updates p with the new information of the funds of the his/her 
 *   bank account.
 * - p->user.account[j].accountValue : Decreases the amount of money withdrawn
     from the account.
*******************************************************************************/
void withdrawMoney(node_t p, node_t linkList, int debugFlag) {
    
    char accountID1[15];
    double amount;
    int found = 0;
    
    char garbage;
    garbage = getchar();
    if (garbage);
    
    printf("What account would you like to withdraw from? ");
    fgets(accountID1, 10, stdin);
    
    printf("Amount: ");
    scanf("%lf", &amount); /*get info for withdraw*/
    
    if (debugFlag == 1) { /*debug*/
        printf("\nDEBUG: \n"
               "accountID1= %s\n"
               "amount= %lf\n", accountID1, amount);
    }
    
    int j;
    for (j = 0; j < 6; j++) {
        /* I can't get rid of the \n so strcmp reads for comparison plus \n*/
        if ((strcmp(p->user.account[j].accountID,
                    accountID1)) == -10) { /*search for account */
            if (debugFlag == 1) /*debug*/
                printf("\nDEBUG: current p->user.account[j].accountID= %s\n",
                       p->user.account[j].accountID);
            if (p->user.account[j].accountValue < amount) {
                printf("Insufficient Funds\n");
                if (debugFlag == 1) /*debug*/
                    printf("\nDEBUG: p->user.account[j].accountValue= %lf\n",
                           p->user.account[j].accountValue);
                return;
            }
            p->user.account[j].accountValue =
                    p->user.account[j].accountValue - amount;
            /*deduct value from account*/
            printf("withdraw successfull\n");
            found = 1;
            if (debugFlag == 1) /*debug*/
                printf("\nDEBUG: p->user.account[j].accountValue= %lf\n",
                       p->user.account[j].accountValue);
            
            
        }
        if (j == 5 && found == 0) {
            printf("Sorry the account your trying to"
                   " withdraw from doesn't exist\n");            
        }        
    }
}
/*******************************************************************************
 * This function lets the user Desposit funds to his/her bank accounts.
 * inputs:
 * - node_t linkedList : head of our linkedlist used to store user info.
 * - node_t p : The actual linkedlist used to store info.
 * - int debugFlag : a pointer used to indicate whether the program is in
 *   debug mode or not.
 * outputs:
 * - node_t p : Updates p with the new information of the funds of the his/her 
 *   bank account.
 * - p->user.account[j].accountValue : Increases the amount of money in the 
     account funds were transfered to.
*******************************************************************************/
int depositMoney(node_t p, node_t linkList, int debugFlag) {
    
    char accountID1[15];
    double amount;
    int found = 0; /* used to match when searching accounts*/
    
    
          /* clean stdin to prevent overflow*/
    char garbage;
    garbage = getchar();
    if (garbage);
    
    printf("What account would you like to Deposit to? ");
    fgets(accountID1, 10, stdin);
    printf("Amount: ");
    scanf("%lf", &amount); /*get info for deposit*/
    
    if (debugFlag == 1) { /*debug*/
        printf("\nDEBUG: \n"
               "accountID1= %s\n"
               "amount= %lf\n", accountID1, amount);
    }
    
    int j;
    for (j = 0; j < 6; j++) {
        if (debugFlag == 1) /*debug*/
            printf("\nDEBUG: current p->user.account[j].accountID= %s\n",
                   p->user.account[j].accountID);
        /* I can't get rid of the \n so strcmp reads for comparison plus \n*/
        if (((strcmp(p->user.account[j].accountID,
                     accountID1)) == -10) && found == 0) {
            
            if (debugFlag == 1) /*debug*/
                printf("\nDEBUG: p->user.account[j].accountValue= %lf\n",
                       p->user.account[j].accountValue);
            
            p->user.account[j].accountValue
                    = p->user.account[j].accountValue + amount;
            /*add amount to account*/
            printf("deposit successfull\n");
            found = 1;
            /* depositMoney(p, linkList);*/
            /* miniMenu("Deposit Money", p, linkList);*/
            
        } else
        if (j == 5 && found == 0) {
            printf("Sorry the account your trying to"
                   " deposit to doesn't exist\n");
            return 0;
        }
    }
    
    if (debugFlag == 1) /*debug*/
        printf("\nDEBUG: p->user.account[j].accountValue= %lf\n",
               p->user.account[j].accountValue);
    return 0;
}
/*******************************************************************************
 * This function writes the contents of p to a file so the information p can be
 * stored in a databse so that the user can re-access his/her account when they
 * login next time.
 * inputs:
 * - node_t linkedList : head of our linkedlist used to store user info.
 * - int *numUsers : a pointer user to store the amount of users made.
 * outputs:
 * - NONE
*******************************************************************************/
int writeFileV3(node_t linkList, int* numUsers)
{
    char * key = "@#$%*&()@#$%*&()";
    int j;
    FILE* fp;
    fp = fopen("Database.txt", "w");
    if(fp==NULL)
        return 0;
    fprintf(fp, "%d ", *numUsers);
    /*Dyanmic Key Generation was considered however
    was left out due to the ram and storage restrictions
    */ 
    
    for(linkList=linkList->nextp; linkList!=NULL;linkList=linkList->nextp)
    {
        fprintf(fp, "%s %s %s %d ",
                encrypt(linkList->user.username,key),
                encrypt(linkList->user.password_1,key),
                linkList->user.userID,
                linkList->user.numAccounts);
        for(j=0;j<linkList->user.numAccounts;++j)
        {
            fprintf(fp, "%s %lf %d ",
                  linkList->user.account[j].accountID,
                    linkList->user.account[j].accountValue,
                    linkList->user.account[j].availableFlag);
        }
    } 
    fclose(fp);
    return 1;
}
/*******************************************************************************
 * This function reads p from the database file.
 * inputs:
 * - node_t linkedList : head of our linkedlist used to store user info.
 * - node_t p : The actual linkedlist used to store info.
 * - int debugFlag : a pointer used to indicate whether the program is in
 *   debug mode or not.
 * outputs:
 * - node_t p : p is initialized with the data from the file.
 * 
*******************************************************************************/
int readFile(node_t linkList, node_t p, int* numUsers)
{
    FILE* fp;
    int i, j;
    fp=fopen("Database.txt", "r");
    
    if(fp==NULL)
    {
        return 0;
    }
    
    fscanf(fp, "%d ", numUsers);
    
    for(i=0; i<*numUsers; ++i)
    {
        p=newNode(linkList, p);
    
        fscanf(fp, "%s %s %s %d ",
                p->user.username,
                p->user.password_1,
                p->user.userID,
                &p->user.numAccounts);
        printf("no");
        for(j=0; j<p->user.numAccounts;++j)
        {
            fscanf(fp, "%s %lf %d ",
                    p->user.account[j].accountID,
                    &p->user.account[j].accountValue,
                    &p->user.account[j].availableFlag);
        }
    }
    return 1;
}


/*******************************************************************************
 * This function encrypts the data collected from the user using the XOR bitwise
 * operation.
 * inputs:
 * - char * encryptMessage : The message to encrypt.
 * - char * key : The key used to do the encryption.
 * outputs:
 * - char * encrypted : Return the encrypted string back to the function that
 *   called it.
*******************************************************************************/
char * encrypt(char * encryptMessage, char * key)
{
    int messageLength = strlen(encryptMessage);
    int keyLength = strlen(key);
    char * encrypted = malloc(messageLength + 1);
    int i;
    for(i = 0 ; i<=messageLength; i++)
    {
        if(&encrypted[i] != NULL){
            encrypted[i] = encryptMessage[i] ^ key[i % keyLength];
        }
        else{
            encrypted[i] = '\0';
        }
    }
    return encrypted;
}

/*******************************************************************************
 * This function does the encoding for the Run_Length_Encoding compression that
 * we are using.
 * inputs:
 * - char str[] : String passed to the function to encode.
 * outputs:
 * - char *encodedString : Returns the encoded string back to the function that
 *   called it. This string is used to compress the databse file.
 * 
*******************************************************************************/
char *encoding(char str[])
{
    int count;
    int strLength = strlen(str);
    char *encodedString = (char *)malloc(sizeof(char)*(strLength*2 + 1)); 
    char finalCount[MAX];

    int i;
    int j=0;
    for(i=0; i<strLength; i++)
    {
        encodedString[j++] = str[i];/* init the first occureences of a char*/
        count =1;/*init the count for each occureence*/

        /*if second char is equal to the previous char*/
        while(str[i] == str[i+1] && i+1<strLength)
        {
            count++;
            i++;
        }

        sprintf(finalCount, "%d", count);

        int k;
        for(k=0;*(finalCount+k); k++, j++)
        {
            encodedString[j] = finalCount[k]; /*coping each encoded char to new string */
        }
    }
    return encodedString;
}

/*******************************************************************************
 * This function does the decoding for the Run_Length_Encoding compression that
 * we are using.
 * inputs:
 * - char str[] : String passed to the function to encode.
 * outputs:
 * - char *decodedString : Returns the encoded string back to the function that
 *   called it. This string is used to compress the databse file.
 * 
*******************************************************************************/
char *decoding(char str[])
{
   char temp[MAX];
   char* decodedString = malloc(MAX);
   char* tempCurrentChar =malloc(sizeof(char)*1);
   int initdone = 0;
   
   /*get char first, then get its count*/
   int i;
   for(i=0; i<strlen(str); i=i+2)
   {
        int time = str[i+1] - '0';
        
        sprintf(tempCurrentChar, "%c", str[i]);
        strcpy(temp, tempCurrentChar);

        int j; 
        for(j = 1; j < time; j++)
        {
            char tempChar[2];
            tempChar[0] = str[i];
            tempChar[1] = '\0';
            strcat(temp, tempChar);
        }
        
        /*if use strcat straightly, 
        it somehow get the garbage memory then insert to final string,
        so strcpy is necessary for this situation*/
        if(initdone == 1)
        {
         strcat(decodedString, temp);
        }
        else
        {
         strcpy(decodedString, temp);
         initdone =1;
        }
       
    }

    decodedString[strlen(decodedString)+1] = '\0';
    
    return decodedString;
}

/*******************************************************************************
 * This function uses Run_Length_Encoding to compress the database.
 * inputs:
 * NONE
 * outputs:
 * NONE
 * 
*******************************************************************************/
void doCompress()
{
    char temp[100];
    FILE *fp = fopen(DATABASE, "rb");
    FILE *fpWrite = fopen(DATABASETEMP, "wb");
    char *finished= malloc(sizeof(char)*1);
    char space[2];
    space[0] = ' ';
    space[1] = '\0';
    
    if(fp != NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp, "%s ", temp);
            finished = encoding(temp); /*getting a string from encoding function*/
            fputs(finished, fpWrite);
            fputs(space, fpWrite);/*space is needed here for meeting the databse*/
            
        }

    fclose(fp);	
    fclose(fpWrite);

    remove(DATABASE);
    rename(DATABASETEMP, DATABASE);

    }
    else
    {
        printf("Cannot find database, please have a check");
    }
}


/*******************************************************************************
 * This function uses Run_Length_Encoding to decompress the database.
 * inputs:
 * NONE
 * outputs:
 * NONE
 * 
*******************************************************************************/
void doDecompress()
{
    char temp[100];
    FILE *fp = fopen(DATABASE, "rb");
    FILE *fpWrite = fopen(DATABASETEMP, "wb");
    char *finished=malloc(sizeof(char)*1);
    char space[2];
    space[0] = ' ';
    space[1] = '\0';

    if(fp!=NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp, "%s ", temp);
            finished = decoding(temp); /*getting a string from decoding function*/
            fputs(finished, fpWrite);
            fputs(space, fpWrite); /*space is needed here for meeting the databse*/
        }
    fclose(fp);
    fclose(fpWrite);

    remove(DATABASE);
    rename(DATABASETEMP, DATABASE);
    }
    else
    {
        printf("Cannot find database, please have a check");
    }
}
