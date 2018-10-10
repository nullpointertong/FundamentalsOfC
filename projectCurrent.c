#include "projectCurrentHeader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void) {
    
    node_t linkList;
    linkList = malloc( sizeof (node_t)); /*initialise the linkList*/
    int *numUsers=0;
    numUsers = malloc( sizeof (int)*1);  /*initialise numUsers*/
    node_t p;
    p=malloc( sizeof (node_t)*1);        /*initialise p pointer*/
    int debugFlag = 0;
    /*initialise debugFlag as 0, can be accessed in userMenu*/
    
    
    if(readFile(linkList, p, numUsers)==0)
        /*checks to see if there is a database file, loads data if it exists*/
    {
        printf("Error: Data was unable to load.\n Contact Administrator\n");
        /*if database does not exists*/
    }
    
    
    p= userMenu(linkList, p, &debugFlag, numUsers);
    /*go to userMenu, go to login or newUser and get p(points to user)*/
    
    
    char input = 'a';
    while (input != '0') {
        /*main menu for user, will repeat until 1 or 0 is added*/
        
        input = accountMenu();
        
        switch (input) {
            case ('1'):
            {
                p=userMenu(linkList, p ,&debugFlag, numUsers);
                break;
            }/*goes back to userMenu and gets p for a different user*/
            case ('2'):
                while (addNewAccount(linkList, p, debugFlag) == 0);
                break;
             /*repeats addNewAccount until valid input*/
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
                /**/
                    if(writeFileV3(linkList, numUsers)==0)
                        printf("write failure");
                        /*if cannot make file*/
                exit(0);  /*end*/
            }
            default:
            {
                printf("Please enter an option 1-6 or quit with 0\n");
                /*repeats if an invalid input*/
                if (debugFlag == 1)
                    printf("\n\nDEBUG: input =%c\n", input); /*debug*/
            }
            
        }
    }
    
    return 0; /*end*/
    
}
/* Used to create a new user from the accountMenu*/
node_t userMenu(node_t linkList, node_t p, int *debugFlag, int *numUsers) {
    char input;
    
    
    while ((input != '1') && (input != '2')) { /*will repeat unless*/
        printf("1. Login\n"                    /*1 or 2 is input*/
               "2. Create User Account\n"
               "3. Exit\n");
        
        printf("Option: ");
        scanf(" %c", &input); /*collects user input*/
        
        
        switch (input) {
            case ('1') : { /*go to login*/
                p=login(linkList, p,  *debugFlag);
                if (*debugFlag == 1) /*debug*/
                    printf("\nDEBUG: \np->user.username= %s"
                           " \np->user.password_1= %s \n",
                           p->user.username, p->user.password_1);
                break;
            }
            
            
            case ('2') : { /*go to newUser, then create newAccount*/
                p = newUser(linkList, numUsers, p, *debugFlag);
                while (addNewAccount(linkList, p, *debugFlag) == 0);
                break;
            }
            case ('3'):
                exit(0); /*end*/
                
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
            default: /*repeats until 1 or 2 is entered*/
                printf("Please enter a valid option\n");
                if (*debugFlag == 1)
                    printf("\nDEBUG: input_s =%c\n", input);
        }
    }
    
    return p; /*returns p, points to user node, to main*/
}

node_t login(node_t linkList,node_t p, int debugFlag) {
    char userlogin[15]; /*initialise temp*/
    char userpass[15];  /*initialise temp*/
    int found=0; /*used as a flag*/
    
    p=NULL;      /*assigns p to nothing, so that it can be reassigned*/
    
                 /*gets username and password*/
    printf("Username: ");
    scanf("%s", userlogin);
    
    printf("Password: ");
    scanf("%s", userpass);
    
    if (debugFlag == 1) /*debug*/
        printf("\nDEBUG: \nuserlogin =%s\nuserpass= %s \n",userlogin, userpass);
        
    
        
    for (p = linkList->nextp; p!=NULL; p = p->nextp) {
                               /*traverse linkedlist*/
        
        if (debugFlag == 1) /*debug*/
            printf("\nDEBUG: \n"
                   "current p->user.username =%s\n"
                   "current p->user.password =%s\n", p->user.username,
                   p->user.password_1);
        
            if (strcmp(p->user.username, userlogin) == 0) {
                              /*compare usernames to information*/
                
            
            if (strcmp(p->user.password_1, userpass) == 0) {
                              /*compare passwords to password entered*/
                printf("Welcome, %s",p->user.username);
                found = 1;
                
                break; /*ends for loop where p points to user
                        * if username and password are correct*/
                
            } else printf("Wrong Password");
                       /*if password wrong*/
            
        }
    }
    if(found==0)
    {
        printf("Sorry this username doesn't exist in the system\n");
        login(linkList, p, debugFlag);
        /*username and password wrong*/
    }
    if (debugFlag == 1) /*debug*/
        printf("\nDEBUG: \np->user.username= %s \np->user.password_1= %s \n", p->user.username, p->user.password_1);
    
    return p; /*p will point to user*/
}


node_t newNode(node_t linkList, node_t p)
{

    p=NULL; /*assigns p to nothing, so that it can be reassigned*/

       p = linkList;
            /*p used to traverse the linklist*/
    while (p->nextp != NULL) {
        p = p->nextp;

    }       /*will stop when p=the last node before NULL*/
    

    node_t newUse = NULL;
    

    newUse = malloc(sizeof(node_t)*1000);
            /*initialise the new node*/
    newUse->nextp = NULL;
            /*set the next node to NULL*/
    p->nextp = newUse;
    p = p->nextp;

    return p; /*return p pointing to the new node*/

}


node_t newUser(node_t linkList, int *numUsers, node_t p, int debugFlag) {
    
    ++(*numUsers); /*increments numUsers*/
    
   p=newNode(linkList,p);
                    /*returns p pointing to the new node*/
    sprintf(p->user.userID, "%d", *numUsers);
                    /*sets userID to the number of uses*/
                    
                    
    printf("Enter Your Username> \n");
    scanf("%s", p->user.username);
    printf("Enter Your Password> \n"); /*gets user and password*/
    scanf("%s", p->user.password_1);
    
    printf("Welcome to Richard and Co Bank!!\n");
    if (debugFlag == 1) /*debug*/
        printf("\nDEBUG: \n"
               "p->user.username= %s\n"
               "p->user.password= %s\n", p->user.username,
               p->user.password_1);
    
    p->user.numAccounts = 0;        /*sets number of accounts to 0*/
    
   
    
    if (debugFlag == 1) /*debug*/
        printf("\nDEBUG: \n"
               "p->user.username= %s\n"
               "p->user.password= %s\n", p->user.username, p->user.password_1);
    
    return p; /*returns p pointing the new User*/
}


char accountMenu() {
    char input;
    char garbage;
    garbage = getchar();
    if (garbage != '\0');
        /*clears input*/
    
    
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
     
   */ printf("\n1. User Menu\n"
           "2. Add Account\n"
           "3. List Accounts\n"
           "4. Transfer Between Accounts\n"
           "5. Withdraw Money\n"
           "6. Deposit Money\n"
           "0. exit\n"); /*prints options*/
    
    printf("Option: ");
    scanf("%c", &input); /*gets user option*/
    
    return input; /*returns user option*/
}

int addNewAccount(node_t linkList, node_t p, int debugFlag) {
    
    char garbage;
    garbage = getchar();
    if (garbage);
        /*clears input*/
    char action; /*initialises user input*/
    
    
    printf("Do you wannt to add a new account, "
           "please enter 'y' or 'n' for next processing\n");
    scanf("%c", &action);
                 /*gets user input*/
    
    if (debugFlag == 1) /*debug*/
        printf("\nDEBUG: action= %c\n", action);
    
    if (action == 'y' || action == 'Y')  /*if y is inputted*/
        {
            if (debugFlag == 1) /*debug*/
                printf("\nDEBUG: p->user.numAccounts= %d\n", p->user.numAccounts);
    
            if (p->user.numAccounts >= 5)
            {
            /*if more than 5 accounts*/
            printf("Sorry, the quota for accounts of user is full\n");
            return 1;
            
            }
            else
            {
                char newAccountID[10]; /*iniitalised string,
                                        * temp for accountID */
                int currentNum = p->user.numAccounts;
            
                sprintf(newAccountID, "%s%d", p->user.username, currentNum);
                                        /*creates newAccountID=
                                         * username+numaccounts*/
            
                 if (debugFlag == 1) /*debug*/
                 printf("\nDEBUG: newAccountID= %s\n", newAccountID);
                 
                 strcpy(p->user.account[currentNum].accountID, newAccountID);
                                        /*copies newAccountID to linklist*/
    
                 p->user.account[currentNum].accountValue = 0;
                 p->user.account[currentNum].availableFlag = 1;
                                        /*sets accountValue and availableFlag*/
                 
                 printf("Your new account has been added successfully\n");
                 printf("Account ID is %s and value is $%.2lf\n",
                   p->user.account[currentNum].accountID,
                   p->user.account[currentNum].accountValue);
            
                 p->user.numAccounts = p->user.numAccounts + 1;
                                        /*increments number of accounts*/
            if (debugFlag == 1) /*debug*/
                printf("\nDEBUG: \n"
                       "p->user.numAccounts= %d\n"
                       "p->user.account[currentNum].availableFlag= %d\n",
                       p->user.numAccounts,
                       p->user.account[currentNum].availableFlag);
            return 1; /*addAccount successful*/
            
               }
    } else if (action == 'n' || action == 'N') {/*if user inputs 'n'*/
        return 1 /*takes user back to menu*/;
    } else if (action != 'n' || action != 'N') {/*if user inputs anything else*/
        printf("Please enter valid input\n");
    }            /*will return 0, function will be called again*/
    
    return 0;
}

/*Transfer money from one account into another account*/
void TransferMoney(node_t p, node_t linkList, int debugFlag) {
    
    char accountID1[10]; /*init, accountID1, temp*/
    char accountID2[10]; /*init, accountID2, temp*/
    double amount;       /*init, amount of money transfered, temp*/
    
    char garbage;
    garbage = getchar();
    if (garbage);
        /*clears input*/
    
    printf("What account would you like to transfer from? ");
    scanf("%s", accountID1);
    
    printf("Destination account: ");
    scanf("%s", accountID2);
    
    printf("Amount: ");
    scanf(" %lf", &amount);
    /*get 2 accountsID to be transferred from and amount transferred*/
    
    int j;
    int once = 0;
    for (j = 0; j < 6; j++) {
        
        if ((strcmp(p->user.account[j].accountID, accountID1)) == 0)
                  /*cycles through accounts until linkList accountID matches
                   * accountID1*/
        {
            if (p->user.account[j].accountValue >= amount)
            { /*makes sure there is enough money in the account*/
                
                p->user.account[j].accountValue =
                        p->user.account[j].accountValue - amount;
                   /*amount subtracted from account1*/
                
                if (debugFlag == 1) /*debug*/
                    printf("\nDEBUG: \n"
                           "Amount= %.2lf\n"
                           "p->user.account[j].accountValue= %.2lf\n",
                           amount,
                           p->user.account[j].accountValue);
                
            }
            else
            {
                printf("Insufficient Funds\n"); /*if not enough money */
                once = 1;                       /*in account, ends function*/
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
                if ((strcmp(p->user.account[k].accountID,
                        accountID2)) == 0 && once == 0)
                {        /*cycles through until accountID matches accountID*/
                    p->user.account[k].accountValue =
                            p->user.account[k].accountValue + amount;
                         /*amount added added to account 2*/
                    
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
        } else if (((strcmp(p->user.account[j].accountID, accountID2) ||
        (strcmp(p->user.account[j].accountID, accountID1))) != 0 && once == 0))
                        /*if accountID's do not match up
                         * and no successful transfer or lack of funds*/
        {
            printf("Transfer unsuccessful, "
                   "please check you have the right account\n");
            
            once = 1;
                    
                       /*function end*/
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



void listAccounts(node_t p)
{
    int j;
    for (j = 0; j < 6; j++) /*cycles and prints through each account*/
    {
        if (p->user.account[j].availableFlag == 1) /*will not print
                                                    * if availableflag=0*/
        {
            printf("%d Account: %s Value: $%.2lf \n", j + 1,
                   p->user.account[j].accountID,
                   p->user.account[j].accountValue);
        }
    }
}

void withdrawMoney(node_t p, node_t linkList, int debugFlag) {
    
    char accountID1[15]; /*init, accountID1, temp*/
    double amount;       /*init, amount to be subtracted, temp*/
    int found = 0;       /*init, used as flag*/
    
    
    char garbage;
    garbage = getchar();
    if (garbage);
            /*clears input*/
    
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
    for (j = 0; j < 6; j++)
    {
        if ((strcmp(p->user.account[j].accountID,
                    accountID1)) == -10) { /*search for account
                                            *-10= ASCII for \n */
            
            if (debugFlag == 1) /*debug*/
                printf("\nDEBUG: current p->user.account[j].accountID= %s\n",
                       p->user.account[j].accountID);
                
            if (p->user.account[j].accountValue < amount)
            {
                printf("Insufficient Funds\n"); /*if not enough money in
                                                 * account, ends function */
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
        if (j == 5 && found == 0)  /*if cycled through function
                                    * and no successful withdraw*/
        {
            printf("Sorry the account your trying to"
                   " withdraw from doesn't exist\n");
            
        }
        
    }
}

int depositMoney(node_t p, node_t linkList, int debugFlag) {
    
    char accountID1[15]; /*init, accountID1, temp*/
    double amount;       /*init, amount to be subtracted, temp*/
    int found = 0;       /*init, used as flag*/
    
    
    
    
    char garbage;
    garbage = getchar();
    if (garbage);
            /*clean input*/
    
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
    for (j = 0; j < 6; j++)  /*cycle through accounts*/
    {
        
        if (debugFlag == 1) /*debug*/
            printf("\nDEBUG: current p->user.account[j].accountID= %s\n",
                   p->user.account[j].accountID);
            
       
        if (((strcmp(p->user.account[j].accountID,
                     accountID1)) == -10) && found == 0) /*search for account
                                                          *-10= ASCII for \n */
        {
            
            if (debugFlag == 1) /*debug*/
                printf("\nDEBUG: p->user.account[j].accountValue= %lf\n",
                       p->user.account[j].accountValue);
            
            p->user.account[j].accountValue
                    = p->user.account[j].accountValue + amount;
                                                    /*add amount to account*/
            printf("deposit successfull\n");
            found = 1;
            
            
        } else
        if (j == 5 && found == 0)                 /*if accountID isnt matched*/
        {
            printf("Sorry the account your trying to"
                   " deposit to doesn't exist\n");
            return 0;
        }
    }
    
    if (debugFlag == 1) /*debug*/
        printf("\nDEBUG: p->user.account[j].accountValue= %lf\n",
               p->user.account[j].accountValue);
    return 0; /*end program*/
}

int writeFileV3(node_t linkList, int* numUsers)
{
	char * key = "dwawd1dwa12#$";
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
                encrypt(linkList->user.userID,key),
                linkList->user.numAccounts);
        for(j=0;j<linkList->user.numAccounts;++j)
        {
            fprintf(fp, "%s %lf %d ",
                  encrypt(linkList->user.account[j].accountID,key),
                    linkList->user.account[j].accountValue,
                    linkList->user.account[j].availableFlag);
        }
    
        }
    
    
    fclose(fp);
    return 1;
}

int readFile(node_t linkList, node_t p, int* numUsers)
{
	char * key = "dwawd1dwa12#$";
    FILE* fp;
    int i, j;
    fp=fopen("Database.txt", "r");
    
    if(fp==NULL)
    {
        return 0;
    }
    printf("maybe");
    fscanf(fp, "%d ", numUsers);
    
    for(i=0; i<*numUsers; ++i)
    {
        p=newNode(linkList, p);
    
        fscanf(fp, "%s %s %s %d ",
                encrypt(p->user.username,key),
                encrypt(p->user.password_1,key),
                encrypt(p->user.userID,key),
                &p->user.numAccounts);
        printf("no");
        for(j=0; j<p->user.numAccounts;++j)
        {
            fscanf(fp, "%s %lf %d ",
                    encrypt(p->user.account[j].accountID,key),
                    &p->user.account[j].accountValue,
                    &p->user.account[j].availableFlag);
        }
    }
    return 1;
}

void insert_hashmap(int *employeeId, map_t hashmap[], int *new_key) {
    /*Please Note Hashmap is implmented in the form h(K) = KmodN where
    N is number of elements in array and K is key*/
    if (hashmap[*new_key].key == 0 && hashmap[*new_key].value == 0) {
        hashmap[*new_key].value = *employeeId;
        hashmap[*new_key].key = *new_key;
    } else if (hashmap[*new_key].key != 0 && hashmap[*new_key].value != 0) {
        /*Linear Collision */
        
        (*new_key)++;
        return insert_hashmap(employeeId, hashmap, new_key);
    }
}

void display_hashmap(int *employeeId, map_t hashmap[], int * new_key) {
    int i;
    printf("Value Key\n");
    for (i = 0; i < 10; i++) {
        printf("%d %d\n", hashmap[i].value, hashmap[i].key);
    }
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
            encryped[i] = 0;
        }
    }
    return encryped;
}
