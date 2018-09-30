#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "projectHeader.h"

int main(void) {
    node_t linkList;
    linkList = malloc(sizeof (node_t));
    login(linkList);
    return 0;
}

node_t login(node_t linkList) {
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
    return p;
}

void accountMenu(node_t p, node_t linkList) {
    char input;
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
    printf("1. Add Account\n"
            "2. Delete Account\n"
            "3. Transfer Between Accounts\n"
            "4. Pay Others\n"
            "5. Withdraw Money\n"
            "6. Deposit Money\n"
            "0. exit\n");

    printf("Option: ");
    scanf("%c", &input);
    switch (input) {
            /*waiting till each function is finished to connect them.*/
        case('1'): addNewAccount(p);
        case('2'): printf("DeleteAccount"); /*deleteAccount(accountID[]);*/
        case('3'): TransferMoney(p, linkList);
        case('4'): printf("Payuser"); /*PayUser(node_t linkList, int amount);*/
        case('5'): printf("Withdraw money"); /*WithdrawMoney(char accountID[],int amount);*/
        case('6'): printf("DepositMoney"); /*DepositMoney(char accountID[],int amount);*/
        case('0'): exit(0);
        default: printf("Please enter an option 1-6 or quit with 0\n");
    }
}

node_t addNewAccount(node_t p) {
    /*char* currentID = userID;
    printf("Your user ID is %s", currentID);
    */
    char action;
    printf("Do you wannt to add a new account, please enter 'y' or 'n' for next processing\n");
    scanf("%c", &action);
    while (action != 'y' || action != 'n' || action != 'Y' || action != 'N') {
        printf("Invalid Input, Please try again\n");   /*confirm if user wants to make a new account*/
        scanf("%c", &action);
    }


    if (action == 'y' || action == 'Y') {
       /* node_t p;
        p = malloc(sizeof (node_t));*/

      /*  for (p = linkList; p != NULL; p = p-> nextp) {
            if (strcmp(p->user.userID, userID) == 0) {
                if (p->user.numAccounts >= 5) {
                    printf("Sorry, the quota for accounts of user is full\n");
                    break;
                } else {
                    int currentNum = p->user.numAccounts;
                    char* newAccountID = userID + currentNum;
                    strcpy(p->user.account[currentNum + 1].accountID, newAccountID);
                    p->user.account[currentNum + 1].accountValue = 0;
                    printf("Your new account has been added successfully\n");
                    printf("Account ID is %s and value is %lf",
                            p->user.account[currentNum + 1].accountID,
                            p->user.account[currentNum + 1].accountValue);*/
      
                if (p->nextp->user.numAccounts >= 5) { /*if more than 5 accounts*/
                    printf("Sorry, the quota for accounts of user is full\n");
                    
                } else {
                    int currentNum = p->nextp->user.numAccounts;
                    char* newAccountID = p->nextp->user.userID + currentNum;  /*create new account ID*/
                    strcpy(p->nextp->user.account[currentNum + 1].accountID, newAccountID);
                    p->nextp->user.account[currentNum + 1].accountValue = 0;
                    printf("Your new account has been added successfully\n");
                    printf("Account ID is %s and value is %lf",
                           p->nextp->user.account[currentNum + 1].accountID,
                           p->nextp->user.account[currentNum + 1].accountValue);
                }
            } else if (action == 'n' || action == 'N') {
                /* call accountMenu(linklist) */
            }
        
    return p;
}



void TransferMoney(node_t p, node_t linkList) {
    /*Transfer money from one account into another account*/
    char accountID1[10];
    char accountID2[10];
    double amount;
    
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
                if ((strcmp(p->nextp->user.account[j].accountID, accountID1))==0) {  /*doesnt it produce 0 if is equal?-changed**/
                    p->nextp->user.account[j].accountValue = p->nextp->user.account[j].accountValue - amount; /*amount subtracted from account*/
                    int k;
                    for (k = 0; k < 6; k++) {
                        if (strcmp(p->nextp->user.account[j].accountID, accountID2)) {  /*shouldnt this be accountID2-changed**/
                            p->nextp->user.account[k].accountValue = p->nextp->user.account[k].accountValue + amount; /*amount added added to account 2*/
                            printf("Money successfully Transferred\n");
                            accountMenu(p, linkList);
                        } else {
                            printf("Transfer unsuccessful, please check you have the right account\n");
                            p->nextp->user.account[j].accountValue = p->nextp->user.account[j].accountValue + amount; /*shouldnt this be plus not minus-changed* */
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
                if (strcmp(i->nextp->user.account[j].accountID, accountID2) == 0) { /*locate account for user i*/
                    i->nextp->user.account[j].accountValue = i->nextp->user.account[j].accountValue + amount; /*pay user i*/
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

node_t withdrawMoney(node_t p) {

    char accountID1[10];
    double amount;

    /*node_t i;
    i = malloc(sizeof (node_t));
    for (i = linkList; i != NULL; i = i->nextp) {
        if (strcmp(i->user.userID, userid) == 0) {*/
            printf("What account would you like to withdraw from?");
            scanf("%s", accountID1);

            printf("Amount: ");
            scanf("%lf", &amount); /*get info for withdraw*/


            int j;
            for (j = 0; j < 6; j++) {
                if (strcmp(p->nextp->user.account[j].accountID, accountID1)) { /*search for account */
                    if (p->nextp->user.account[j].accountValue < amount) {
                        printf("Insufficient Funds");
                        withdrawMoney(p);
                    }
                    p->nextp->user.account[j].accountValue = p->nextp->user.account[j].accountValue - amount; /*deduct value from account*/
                    printf("withdraw successfull");


                } else {
                    printf("Sorry the account your trying to"
                            " withdraw from doesn't exist\n");

                    withdrawMoney(p);
                }

            }
    return p;
}


node_t depositMoney(node_t p) {

    char accountID1[10];
    double amount;

  /*  node_t i;
    i = malloc(sizeof (node_t));
    for (i = linkList; i != NULL; i = i->nextp) {
        if (strcmp(i->user.userID, userid) == 0) {*/
            printf("What account would you like to Deposit from?");
            scanf("%s", accountID1);

            printf("Amount: ");
            scanf("%lf", &amount); /*get info for deposit*/
            

            int j;
            for (j = 0; j < 6; j++) {
                if (strcmp(p->nextp->user.account[j].accountID, accountID1)) { /*find account */

                    p->nextp->user.account[j].accountValue = p->nextp->user.account[j].accountValue + amount; /*add amount to account*/
                    printf("deposit successfull");


                } else {
                    printf("Sorry the account your trying to"
                            " deposit to doesn't exist\n");

                    depositMoney(p);
                }

            }
    return p;
}


node_t newUser(node_t linkList, int *numUsers) {
    ++*numUsers;
    node_t newUse, p; /*PS: now these are both pointers
                       *defines 2 new nodes*/

    newUse = malloc(sizeof (node_t));
    p = malloc(sizeof (node_t));
    /*dynamically sets their size*/
    newUse->nextp = NULL;
    /*sets the next node so that NULL will be the next link*/
    p = linkList;
    /*p used to traverse the linklist*/
    while (p->nextp != NULL) {
        p = p->nextp;
    } /*will stop when p=the last node before NULL*/

    p->nextp = newUse; /*changes the last node (previous NULL) to another node
                      * which points to NULL*/



    sprintf(p->nextp->user.userID, "05%d", *numUsers);
    /*will set the User ID to the number of users in
     * the system (including itself) with the leasing
     * digits being zeros*/

    printf("Enter Your Username> \n");
    scanf("%s", p->nextp->user.username);
    printf("Enter Your Password> \n");
    scanf("%s", p->nextp->user.password);
    printf("Welcome to Richard and Co Bank!!\n");

    addNewAccount(p);

    return p;

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






