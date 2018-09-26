typedef struct map map_t;

struct node {
    struct node* nextp;
    user_t user;
    
};
typedef struct node node_t;

struct user {
    char username[15];
    char password[15];
    account_t account[5];
};
typedef struct user user_t;


struct account {
	int accountNum;
	int accountValue;
};
typedef struct account account_t;
