#include "projectCurrentHeader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 256
#define DATABASE "Database.txt"
#define DATABASETEMP "Database.tmp"

int main(void) {

    node_t linkList;
    linkList = malloc( sizeof (node_t)*1); /*initialise the linkList*/
    /*printf("enter shite >");
    
    scanf("%s", linkList->user.password);
    
    printf("%s", linkList->user.password);*/
    int *numUsers=0;
    numUsers = malloc( sizeof (int)*1); /*initialise numUsers*/
    node_t p;
    p=malloc( sizeof (node_t)*1);
    int debugFlag = 0;
    int *encryptFlag;
    encryptFlag = malloc(sizeof(int)*1);
    *encryptFlag = 2;
    int *compressFlag;
    compressFlag = malloc(sizeof(int)*1);
    
    FILE *fp = fopen(DATABASE, "r");    
    if (fp == NULL){
       printf("Database file empty: No such login exists");
       miniMenu(linkList, p ,&debugFlag, numUsers, compressFlag, encryptFlag);
    }
    
    
    if(readFile(linkList, p, numUsers, encryptFlag)==0)
    {
        printf("Error: Data was unable to load\n");
        userMenu(linkList, p, &debugFlag, numUsers, compressFlag, encryptFlag);
        
    }else{
    p= userMenu(linkList, p, &debugFlag, numUsers, compressFlag, encryptFlag); /*go to start menu and get user option*/
    }
    
    /*will loop until a valid input is added*/
    char input = 'a';
    while (input != '0') {
        
        input = accountMenu();
        
        switch (input) {
            /*waiting till each function is finished to connect them.*/
            case ('1'):
            {
            if(*numUsers == 0){
                printf("Database file empty: No such login exists");
                }else{
                p=userMenu(linkList, p ,&debugFlag, numUsers, compressFlag, encryptFlag);
                }
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
                
                    if(writeFileV3(linkList, numUsers, encryptFlag)==0)
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
/* Used to create a new user from the accountMenu*/
node_t userMenu(node_t linkList, node_t p, int *debugFlag, int *numUsers, int *compressFlag, int *encryptFlag) {
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
                printf("%d", *numUsers);
                if(*numUsers == 0){
                printf("Database file empty!");
                }else{
                p=login(linkList, p,  *debugFlag, compressFlag, encryptFlag);
                if (*debugFlag == 1) /*debug*/
                    printf("\nDEBUG: \np->user.username= %s \np->user.password_1= %s \n", p->user.username, p->user.password_1);
                    }
                
                break;
            }
            case ('2') : {
                p = newUser(linkList, numUsers, p, *debugFlag, encryptFlag);
                while (addNewAccount(linkList, p, *debugFlag) == 0);
                break;
            }
            case ('3'):{
             FILE *fpTemp = fopen(DATABASE, "r");    
                if (fpTemp == NULL)
                {
                }
                else if(*compressFlag == 0)
                {
                doCompress();
                *compressFlag = 1;
                fclose(fpTemp);
                }
                exit(0);
                }
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
char startMenu() {
    char input;
    
    
    printf("1. Login\n"
           "2. Create User Account\n");
    
    printf("Option: ");
    scanf(" %c", &input);
    
    
    switch(input){
        case('1') : {
        FILE *fp = fopen(DATABASE, "r");    
        if (fp == NULL){
       printf("Database file empty: No such login exists");
       input = '2';
       return input;
    }else
            return input;
            break;
        }
        case('2') : {
            return input;
            break;
        }
            printf("Please enter a valid option\n");
    }
    return input;
}

/* switch (input) {
     case('1') : {
         login(linkList);
         break;
     }
     case('2') : {    fetch = <refspec>
         newUser(linkList, numUsers);
         break;
     }
     default : printf("Please enter a valid option");
 }
}
 */
node_t login(node_t linkList,node_t p, int debugFlag, int *compressFlag, int *encryptFlag) {
    char userlogin[15];
    char userpass[15];
    int found=0;
    char * key = "@#$%*&()@#$%*&()";
    p=NULL;
    
    FILE *fp = fopen(DATABASE, "r");    
    if (fp == NULL){
       printf("Database file empty: No such login exists");
    }
    if(*compressFlag == 1){
     doDecompress();
     (*compressFlag = 0);
        fclose(fp);
    }
    
    
    printf("user:::%s",encrypt(linkList->nextp->user.username,key));
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
                *encryptFlag = 1;
                
                break;
                /* go to accountmenu and pass userID*/
            } else printf("Wrong Password");
            
        }
    }
    if(found==0)
    {
        printf("Sorry this username doesn't exist in the system\n");
        login(linkList, p, debugFlag, compressFlag, encryptFlag);
    }
    if (debugFlag == 1) /*debug*/
        printf("\nDEBUG: \np->user.username= %s \np->user.password_1= %s \n", p->user.username, p->user.password_1);
    
    return p;
}





node_t newNode(node_t linkList, node_t p)
{

p=NULL;


/*sets the next node so that NULL will be the next link*/
p = linkList;
/*p used to traverse the linklist*/
while (p->nextp != NULL) {
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


node_t newUser(node_t linkList, int *numUsers, node_t p, int debugFlag, int *encryptFlag) {
    
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
    *encryptFlag = 2;
    p->user.numAccounts = 0;
    
   
    
    if (debugFlag == 1) /*debug*/
        printf("\nDEBUG: \n"
               "p->user.username= %s\n"
               "p->user.password= %s\n", p->user.username, p->user.password_1);
    
    return p;
}

/* Used as a submenu for functions like Transfer between accounts,
 * Deposit and withdraw. It is an easy and straight forward way to have
 * A submenu */
char miniMenu(node_t linkList, node_t p ,int &debugFlag,int numUsers, int compressFlag,int encryptFlag) {
    char garbage;
    garbage = getchar();
    if (garbage);
    
    
    char input = '\0';
    printf("1. Create Account\n"
           "2. Exit\n");
    
    printf("Option: ");
    scanf("%c", &input);
    switch(input){
    
        case('1') : {
        
       printf("Database file empty: No such login exists");
       input = '2';
       return input;
       break;
    }
        }
        case('2') : {
            return input;
            break;
        }
            printf("Please enter a valid option\n");
    }
    return input;
    
}

char accountMenu() {
    char input;
    char garbage;
    garbage = getchar();
    if (garbage != '\0');
    
    
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
    printf("\n1. User Menu\n"
           "2. Add Account\n"
           "3. List Accounts\n"
           "4. Transfer Between Accounts\n" /* new user*/
           "5. Withdraw Money\n"
           "6. Deposit Money\n"
           "0. exit\n");
    
    printf("Option: ");
    scanf("%c", &input);
    /* switch (input) {
         waiting till each function is finished to connect them.
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
         default: printf("Please enter an option 1-7 or quit with 0\n");*/
    /*
int i;
map_t hashmap[10];
for(i = 0 ;i<10 ; i++){
hashmap[i].value = 0;
hashmap[i].key = 0;
}
Replace .value with information you want*/
    return input;
}

int addNewAccount(node_t linkList, node_t p, int debugFlag) {
    /*char* currentID = userID;
    printf("Your user ID is %s", currentID);
     */
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
                    for (j = 0; j < 6; j++) {
                        if (strcmp(p->nextp->user.account[j].accountID, accountID1) == 0) /*locate account of user p*/ {
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

void withdrawMoney(node_t p, node_t linkList, int debugFlag) {
    
    char accountID1[15];
    double amount;
    int found = 0;
    
    /*node_t i;
    i = malloc(sizeof (node_t));
    for (i = linkList; i != NULL; i = i->nextp) {
        if (strcmp(i->user.userID, userid) == 0) {*/
    
    /* Mini Withdraw Menu, like in the Deposti function*/
    
    /* if(miniMenu("Withdraw Money", p, linkList) == '1')
     {*/
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

int depositMoney(node_t p, node_t linkList, int debugFlag) {
    
    char accountID1[15];
    double amount;
    int found = 0; /* used to match when searching accounts*/
    
    
    /*  if((miniMenu("Deposit Money", p, linkList) == '1'))
      {
           clean stdin to prevent overflow*/
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

int writeFileV3(node_t linkList, int* numUsers, int *encryptFlag)
{
    char *key = "@#$%*&()@#$%*&()";
    int j;
    
    FILE* fp;
    fp = fopen("Database.txt", "w+");
    if(fp==NULL)
        return 0;
    fprintf(fp, "%d ", *numUsers);
    
    /*Dyanmic Key Generation was considered however
    was left out due to the ram and storage restrictions
    */ 
    
    for(linkList=linkList->nextp; linkList!=NULL;linkList=linkList->nextp)
    {
    if(*encryptFlag == 2){
            /*encryptFlag = 1;*/
        fprintf(fp, "%d %s %s %s %d ", *encryptFlag,
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
        else{fprintf(fp, "%d %s %s %s %d ", *encryptFlag,
                linkList->user.username,
                linkList->user.password_1,
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
    }
    
    fclose(fp);
    return 1;
}

int readFile(node_t linkList, node_t p, int* numUsers, int *encryptFlag)
{

    FILE* fp;
    int i, j;
    fp=fopen("Database.txt", "r+");
    
    if(fp==NULL)
    {
       printf("Database file empty: No such login exists");
       return 0;
    }
    
    fscanf(fp, "%d ", numUsers);
    
    for(i=0; i<*numUsers; ++i)
    {
        p=newNode(linkList, p);
    
        fscanf(fp, "%d %s %s %s %d ", encryptFlag,
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

/* Encrypts using XOR bitwise Operation */
char * encrypt(char * encryptMessage, char * key)
{
    int messageLength = strlen(encryptMessage);
    int keyLength = strlen(key);
    char * encryped = malloc(messageLength + 1);
    int i;
    for(i = 0 ; i<=messageLength; i++)
    {
        if(&encryped[i] != NULL){
            encryped[i] = encryptMessage[i] ^ key[i % keyLength];
        }
        else{
            encryped[i] = '\0';
        }
    }
    return encryped;
}

/*get a string then encoding with Run_Length_Encoding, return a string*/
char *encoding(char str[])
{
    int count;
    int strLength = strlen(str);
    char *new = (char *)malloc(sizeof(char)*(strLength*2 + 1)); 
    char finalCount[MAX];

    int i;
    int j=0;
    for(i=0; i<strLength; i++)
    {
        new[j++] = str[i];/* init the first occureences of a char*/
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
            new[j] = finalCount[k]; /*coping each encoded char to new string */
        }

    }

    return new;
}

/*get a string then decoding with Run_Length_Encoding, return a string*/
char *decoding(char str[])
{
   char temp[MAX];
   char* final = malloc(MAX);
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
         strcat(final, temp);
        }
        else
        {
         strcpy(final, temp);
         initdone =1;
        }
       
    }

    final[strlen(final)+1] = '\0';
    
    return final;
}

/*Compress  database*/
void doCompress()
{
    char temp[100];
    FILE *fp = fopen(DATABASE, "r");
    FILE *fpWrite = fopen(DATABASETEMP, "w");
    char *finished= malloc(sizeof(char)*10);
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

/*Decompress  database*/
void doDecompress()
{
    char temp[100];
    FILE *fp = fopen(DATABASE, "r");
    FILE *fpWrite = fopen(DATABASETEMP, "w");
    char *finished=malloc(sizeof(char)*10);
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
