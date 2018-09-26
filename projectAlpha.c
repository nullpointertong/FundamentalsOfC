struct node {
    struct node* nextp;
    user_t user;
    
};
typedef struct node node_t;

struct user {
    char username[15];
    char password[15];
    char userID[5];
    account_t account[5];
};
typedef struct user user_t;


struct account {
	char accountNum[10];
	int accountValue;
};
typedef struct account account_t;

/*Prototypes*****************************/
node_t readFile(); 
int writeFile(node_t linkList);
int newUser(node_t linkList, int numUsers);  
void accountMenu(node_t linkList);

void addNewAccount(node_t linklist);
void PayUser(node_t linkList, int amount);
void TransferMoney(char accountNum1[],char accountNum2[],int amount);
void WhitdrawMoney(char accountNum[],int amount);
void DepositMoney(char accountNum[],int amount); 

user_t* i;
for (*i = Linkedlist.user; i != NULL; ++i)
{
	/* if(node == somecondition)
 	node.user.Accountname*/
	if(i.user.accountID=accountID)
	{
	do some shit
		return i*;
	}
}
