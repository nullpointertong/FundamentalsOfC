#include "projectheaderOmega.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int main(void) {
    
    node_t linkList ;
    linkList = malloc(sizeof (node_t));
    /*load init from database*/
    int *numUsers;
    numUsers=malloc(sizeof(int)*1);
   char input_s= startMenu();
   node_t p;
   p= (node_t)(malloc(sizeof (node_t)*1));
    switch (input_s)
    {
        case('1') : {
           login(linkList, p);
            break;
        }
        case('2') : {
            newUser(linkList, numUsers, p);
           /* sprintf(p->user.userID, "%d", *numUsers);
            printf("DEBUG USERID IS %s\n",p->user.userID);
            will set the User ID to the number of users in
             the system (including itself) with the leasing
              digits being zeros
    
            printf("Enter Your Username> \n");
            scanf("%s", p->user.username);
            printf("Enter Your Password> \n");
            scanf("%s", p->user.password);
            printf("Welcome to Richard and Co Bank!!\n");*/
            p->user.numAccounts = 0;
            addNewAccount(linkList, p);
            printf("\n yeeeet %s", p->user.userID);
            break;
        }
        default : printf("Please enter a valid option");
    }
    
    char input='a';
    while(input!='0') {
    
    
        input = accountMenu();
    
        switch (input) {
            /*waiting till each function is finished to connect them.*/
            case ('1'): {
                while (addNewAccount(linkList, p)==0);
                break;
            }
            case ('2'):
                printf("DeleteAccount");
                break;
                
            case ('3'):
                TransferMoney(p, linkList);
                break;
                
            case ('4'): {
                listAccounts(p);
                break;
            }
            case ('5'):
                PayUser(p, linkList);
                break;
            case ('6'):
                withdrawMoney(p, linkList);
                break;
            case ('7'):
                depositMoney(p, linkList);
                break;
            case ('0'):
                exit(0);
            default:
                printf("Please enter an option 1-7 or quit with 0\n");
        
        }
    }
    /*while input='0'
     main
     login(linkList);
     check file is exist?
     if no, do create user
     if yes, show 'Login', 'Create User' Menu*/
    
    
    return 0;
}

char startMenu() {
    char input;
    
    
    printf("1. Login\n"
           "2. Create Account\n");
    
    printf("Option: ");
    scanf("%c", &input);
    
    return input;
}
   /* switch (input) {
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
*/
void login(node_t linkList, node_t p) {
       char userlogin[15];
       char userpass[15];
    
    
    
       /* ask for username and password*/
       printf("Username: ");
       scanf("%s", userlogin);
    
       printf("Password: ");
       scanf("%s", userpass);
    
       /* use a pointer to traverse the linkedlist*/
       
       /*traverse linkedlist*/
       for (p = linkList; p != NULL; p = p->nextp) {
           /*compare usernames to information*/
           if (strcmp(p->user.username, userlogin) == 0) {
               /* compare passwords to password entered*/
               if (strcmp(p->user.password, userpass) == 0) {
                   printf("Welcome, %s", p->user.username);
                   /* go to accountmenu and pass userID*/
                   accountMenu(p, linkList);
               } else printf("Wrong Password");
           } else {
               printf("Sorry this username doesn't exist in the system\n");
               login(linkList, p);
           }
       }
}

void newUser(node_t linkList, int *numUsers, node_t p) {
    ++(*numUsers);
    /*node_t newUse; PS: now these are both pointers
                       defines 2 new nodes
    
    newUse = malloc(sizeof (node_t));*/
   
    /*dynamically sets their size*/
   /* newUse->nextp = NULL;*/
    /*sets the next node so that NULL will be the next link*/
   /* p = linkList;*/
    /*p used to traverse the linklist*/
    if(p->nextp != NULL) {
        p = p->nextp;
        
    } /*will stop when p=the last node before NULL*/
    
    /*changes the last node (previous NULL) to another node
                      * which points to NULL*/
    
    sprintf(p->user.userID, "%d", *numUsers);
    printf("DEBUG USERID IS %s\n",p->user.userID);
    /*will set the User ID to the number of users in
     * the system (including itself) with the leasing
     * digits being zeros*/
    
    printf("Enter Your Username> \n");
    scanf("%s", p->user.username);
    printf("Enter Your Password> \n");
    scanf("%s", p->user.password);
    printf("Welcome to Richard and Co Bank!!\n");
    p->user.numAccounts = 0;
    
    
    
}



/* Used as a submenu for functions like Transfer between accounts,
 * Deposit and withdraw. It is an easy and straight forward way to have
 * A submenu */
char miniMenu(char name[], node_t p, node_t linkList)
{
    char garbage;
    garbage = getchar();
    if(garbage);
    
    
    char input = '\0';
    printf("1. %s\n", name);
    printf("2. list Accounts\n"
           "3. Return to Menu\n");
    
    printf("Option: ");
    scanf("%c", &input);
    if(input == '1')
    {
        return input;
    }
    if(input == '2')
    {
        listAccounts(p);
        miniMenu(name, p, linkList);
        
    }
    else if(input == '3')
    {
        accountMenu(p, linkList);
    }
    else
    {
        printf("%c", input);
    }
    return input;
    
}


char accountMenu()
{
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



int addNewAccount(node_t linkList, node_t p) {
    /*char* currentID = userID;
    printf("Your user ID is %s", currentID);
    */
    char garbage;
    garbage = getchar();
    if(garbage);
    
    char action;
    
    
    printf("Do you wannt to add a new account,please enter 'y' or 'n' for next processing\n");
    scanf("%c", &action);
    
    if (action == 'y' || action == 'Y')
    {
        
        
        if (p->user.numAccounts >= 5)
        {
            /*if more than 5 accounts*/
            printf("Sorry, the quota for accounts of user is full\n");
            
        } else {
            /* This function is broken*/
            char newAccountID[10];
            int currentNum = p->user.numAccounts;
            /*strcat(newAccountID, strcat(p->user.userID, currentNum));
            create new account ID*/
            sprintf(newAccountID, "%s%d", p->user.username, currentNum);
            strcpy(p->user.account[currentNum].accountID, newAccountID);
            p->user.account[currentNum].accountValue = 0;
            p->user.account[currentNum].availableFlag = 1;
            printf("Your new account has been added successfully\n");
            printf("Account ID is %s and value is $%.2lf\n",
                   p->user.account[currentNum].accountID,
                   p->user.account[currentNum].accountValue);
            p->user.numAccounts = p->user.numAccounts + 1;
            
            printf("\nyeee%d", p->user.account->availableFlag);
            return 1;
            
        }
    } else if (action == 'n' || action == 'N')
    {
        return 0;
    }
    else if (action != 'n' || action != 'N')
    {
        printf("Please enter valid input\n");
    }
    
    return 0;
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
                p->user.account[j].accountValue = p->user.account[j].accountValue - amount; /*amount subtracted from account*/
                int k;
                for (k = 0; k < 6; k++) {
                    if ((strcmp(p->user.account[j].accountID, accountID2))== 0) {  /*shouldnt this be accountID2-changed**/
                        p->user.account[k].accountValue = p->user.account[k].accountValue + amount; /*amount added added to account 2*/
                        printf("Money successfully Transferred\n");
                        accountMenu(p, linkList);
                    } else {
                        printf("Transfer unsuccessful, please check you have the right account\n");
                        p->user.account[j].accountValue = p->user.account[j].accountValue + amount; /*shouldnt this be plus not minus-changed* */
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
        if(p->user.account[j].availableFlag == 1)
        {
            printf("%d Account: %s Value: $%.2lf \n", j+1,
                   p->user.account[j].accountID,
                   p->user.account[j].accountValue);
        }
    }
}

int withdrawMoney(node_t p, node_t linkList) {
    
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
        if(garbage);
        
        printf("What account would you like to withdraw from? ");
        fgets(accountID1, 10, stdin);
        
        printf("Amount: ");
        scanf("%lf", &amount); /*get info for withdraw*/
        
        
        int j;
        for (j = 0; j < 6; j++) {
            /* I can't get rid of the \n so strcmp reads for comparison plus \n*/
            if ((strcmp(p->user.account[j].accountID,
                        accountID1)) == -10) { /*search for account */
                if (p->nextp->user.account[j].accountValue < amount)
                {
                    printf("Insufficient Funds\n");
                    
                    return 0;
                }
                p->user.account[j].accountValue =
                        p->user.account[j].accountValue - amount;
                /*deduct value from account*/
                printf("withdraw successfull\n");
                found = 1;
                return 0;
                
                
            }
            if(j == 5 && found == 0)
            {
                printf("Sorry the account your trying to"
                       " withdraw from doesn't exist\n");
                
                return 0;
            }
            
        }
    return 0;
}




int depositMoney(node_t p, node_t linkList) {
    
    char accountID1[15];
    double amount;
    int found = 0; /* used to match when searching accounts*/
    
    
  /*  if((miniMenu("Deposit Money", p, linkList) == '1'))
    {
         clean stdin to prevent overflow*/
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
            if (((strcmp(p->user.account[j].accountID,
                         accountID1)) == -10) && found == 0)
            {
                
                p->user.account[j].accountValue
                        = p->user.account[j].accountValue + amount;
                /*add amount to account*/
                printf("deposit successfull\n");
                found = 1;
                
                /* depositMoney(p, linkList);*/
                /* miniMenu("Deposit Money", p, linkList);*/
                
            }else
            if(j == 5 && found == 0)
            {
                printf("Sorry the account your trying to"
                       " deposit to doesn't exist\n");
                
                return 0;
            }
        }
    return 0;
}




int writeFile(node_t linkList, int* numUsers) {
    FILE*fp;
    
    fp = fopen("Database.txt", "w");
    
    if (fp == NULL) /*if file fails to open function ends*/ {
        return 0;
    }
    
    if (numUsers == 0) /*if there is no data to write function ends*/ {
        return 0;
    }
    
    fprintf(fp, "%d ", *numUsers); /*prints number of uses, used when reading
                                   * the file*/
    node_t p;
    p = malloc(sizeof (node_t));
    /*sets data size for pointer*/
    int count; /*used to count through user accounts*/
    for (p = linkList; p != NULL; p = p->nextp)
        /*prints each value for each user until the next */ {
        fprintf(fp, "%s %s %s %d ", p->user.userID, p->user.username,
                p->user.password, p->user.numAccounts);
        /*numAccounts used to determine how many accounts to print*/
        
        for (count = 0; count < p->user.numAccounts; ) {
            fprintf(fp, "%s %lf %d", p->user.account[count].accountID,
                    p->user.account[count].accountValue, p->user.account[count].availableFlag);
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




