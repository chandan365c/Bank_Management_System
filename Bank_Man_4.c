#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<string.h>

struct accounts
{
    char user_usernames[15];    //max length of username is 15
    char user_passwords[15];
    float user_balances;
    enum defined_acc_types{Salary=1, FD, Savings, RD};  //enum to assign a number to the type of account
    int account_type;
    struct accounts *next;
};

struct accounts *head=NULL;

void save_to_file()
{
    FILE *fp = fopen("Bank_Man_Data.txt", "w");
    if (fp!=NULL)
    {
        struct accounts *current = head;
        while (current != NULL)
        {
            fwrite(current, sizeof(struct accounts), 1, fp);
            current = current->next;
        }
        fclose(fp);
    }
}

void CreateAcc()
{
    struct accounts *new_account=(struct accounts*) malloc(sizeof(struct accounts));
    if(new_account == NULL)
    {
        printf("\n");
        printf("Memory allocation failed\n");
        printf("\n");
        return;
    }
    
    printf("Enter username: ");
    scanf("%s", new_account->user_usernames);
    printf("Set a strong password: ");
    scanf("%s", new_account->user_passwords);
    printf("\n");
    new_account->user_balances = 0;     //assign new user balance as 0

    printf("What type of account would you like to create?\n");
    printf("    1. Salary Account\n");
    printf("    2. Fixed Deposits Account\n");
    printf("    3. Savings Account\n");
    printf("    4. Recurring Deposits Account\n");
    printf("\n");
    printf("Select your type of account: ");
    scanf("%d", &new_account->account_type);
    new_account -> next = head;
    head = new_account;
    save_to_file();    //save the created account to file
    printf("\n");
    printf("Account created successfully!\n");
    printf("\n");
    sleep(1);
    printf("Please Login to your account to perform further actions.\n");
    printf("\n");
    sleep(1);
}

struct accounts *find_acc(const char *username)     //function to traverse through the linked list and see if user exists or not
{
    struct accounts *current = head;        //assign current node as head node in the starting 
    while (current!= NULL) 
    {
        if (strcmp(current->user_usernames, username) == 0)     //comparing the data in the current node and the user entered data
        {
            return current;
        }
        current = current->next;            //moving to the next node
    }
    return NULL; // Account not found
}

bool Login(char username[15])
{
    char password[15];

    struct accounts *user_accounts = find_acc(username);    //checking if user exists or not
    if (user_accounts == NULL)      //case:- user does not exist 
    {
        printf("\n");
        printf("Account not found!! Please check the entered username!\n");
        printf("\n");
        return false;
    }

    //If user exists
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(user_accounts->user_passwords, password) == 0)   //compare and match passwords
    {
        printf("\n");
        printf("Logged in successfully!\n");
        return true;
    } 
    else 
    {
        printf("\n");
        printf("Incorrect password!\n");
        return false;
    }
}

void check_balance(struct accounts *account)
{
    printf("\n");
    printf("Fetching balance. . .\n");
    printf("\n");
    sleep(1);
    printf("Current available balance is %.2f\n", account->user_balances);
    printf("\n");
}

int Deposit(struct accounts *account)
{
    float amount;
    deposit:
        printf("Enter the amount to deposit: ");
        scanf("%f", &amount);
    if(amount<=0)
    {
        sleep(0.5);
        printf("\n");
        printf("Please enter a valid amount!\n");
        printf("\n");
        goto deposit;
    }
    else
    {
        account-> user_balances = account->user_balances + amount;
        printf("\n");
        printf("%.2f deposited into your account!\n", amount);
        printf("\n");
    }
}

int Withdraw(struct accounts *account)
{
    float amount;
    withdrawl:
       printf("Enter the amount to withdraw: ");
       scanf("%f", &amount);

    if(amount<=0)
    {
        sleep(0.5);
        printf("\n");
        printf("Please enter a valid amount!\n");
        printf("\n");
        goto withdrawl;
    }

    if (account->user_balances >= amount) 
    {
        account -> user_balances = account -> user_balances - amount;
        printf("\n");
        printf("%.2f withdrawn successfully!\n", amount);
        printf("\n");
        sleep(0.5);
    } 
    else 
    {
        printf("\n");
        printf("Insufficient balance! Please check your balance and try again\n");
        printf("\n");
        sleep(0.5);
    }
}


void Acc_Details(struct accounts *account)
{
    printf("\n");
    printf("Fetching account details. . . \n");
    printf("\n");
    sleep(1);
    printf("\n");
    printf("Username:- %s\n", account -> user_usernames);

    switch(account->account_type)       //convert account type enums to strings 
    {
        case Salary:
            printf("Account Type: Salary\n");
            break;
        case FD:
            printf("Account Type: Fixed Deposit\n");
            break;
        case Savings:
            printf("Account Type: Savings\n");
            break;
        case RD:
            printf("Account Type: Recurring Deposit\n");
            break;
        default:
            printf("Account Type: Unknown\n");
    }
    printf("Account Balance: %.2f\n", account -> user_balances);
    printf("\n");
    sleep(0.5);
}

void read_file_content()
{
    FILE *fp = fopen("Bank_Man_Data.txt", "r");
    if (fp != NULL)
    {
        struct accounts temp;
        while (fread(&temp, sizeof(struct accounts), 1, fp))
        {
            struct accounts *new_account=(struct accounts*) malloc(sizeof(struct accounts));
            if (new_account != NULL)
            {
                strcpy(new_account->user_usernames, temp.user_usernames);
                strcpy(new_account->user_passwords, temp.user_passwords);
                new_account->user_balances = temp.user_balances;
                new_account->account_type = temp.account_type;
                new_account->next = head;
                head = new_account;
            }
        }
        fclose(fp);
    }
    else
    {
        printf("\n");
        printf("Error opening file/ File not found!\n");
        printf("\n");
    }
}

int main()
{
    read_file_content();

    int choice, action;
    int attempts=0;

    do  //Looping until user enters 3 to exit
    {
        printf("Welcome to ABCD Bank! Please choose your option...\n");
        printf("    1. Create Account\n");
        printf("    2. Login to existing account\n");
        printf("    3. Exit\n");
        printf("\n");

        prompt_choice:                              //Label to prompt user to enter their choice
            printf("Please enter your choice [1-3]: ");
            scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            {
                CreateAcc();
                break;
            }
            case 2:
            {
                struct accounts *current = NULL;
                char username[15];
                printf("\n");
                printf("Welcome back! Please login with your credentials!\n");
                printf("\n");
                printf("Enter username: ");
                scanf("%s", username);
                current = find_acc(username);   

                if(Login(username))
                {
                    int user_action;
                    do
                    {
                        printf("How would you like to bank with us today?\n");
                        printf("    1. Make a deposit\n");
                        printf("    2. Withdraw money\n");
                        printf("    3. Check available balance\n");
                        printf("    4. Get account details\n");
                        printf("    5. Logout");
                        printf("\n");

                        prompt_action:                              //Label to prompt user to choose action
                            printf("Please enter your choice: ");
                            scanf("%d", &user_action);

                        switch(user_action) 
                        {
                            case 1:     //Deposits
                            {
                                Deposit(current);
                                break;
                            }

                            case 2:     //Withdrawl
                            {
                                Withdraw(current);
                                break;
                            }

                            case 3:     //check balance
                            {
                                check_balance(current);
                                break;
                            }
                            
                            case 4:     //fetch details
                            {
                                Acc_Details(current);
                                break;
                            }

                            case 5:     //Logout
                            {
                                save_to_file();
                                printf("Logging out. . . \n");
                                printf("\n");
                                sleep(1);
                                printf("\n");
                                printf("Logged out successfully!\n");
                                printf("\n");
                                break;
                            }

                            default:
                            {
                                printf("\n");
                                printf("Invalid choice! Please choose the appropriate action from the above list\n");
                                sleep(1);
                                printf("\n");
                                goto prompt_action;
                            }

                        }
                    } while (user_action!=5); 
                }
                else
                {
                    printf("\n");
                    printf("Login failed!! Redirecting to homepage. . .\n");
                    printf("\n");
                    sleep(1);
                    attempts++;
                    if(attempts==3)
                    {
                        printf("\n");
                        printf("Maximux login attempts exceeded!! Please try again later!\n");
                        printf("\n");
                        sleep(1);
                        printf("Exiting. . . ");
                        printf("\n");
                        exit(0);
                    }
                }
                break;
            }
            case 3:
            {
                printf("\n");
                printf("Exiting....\n");
                sleep(1.5);
                printf("\n");
                printf("Thank you for banking with us!\n");
                break;
            }
            default:
            {
                printf("\n");
                printf("Invalid choice! Please choose the appropriate choice (1 to 3) from the above list\n");
                sleep(1);
                printf("\n");
                goto prompt_choice;

            }
        }
    } while(choice!=3);

    struct accounts *current = head;        
    while (current != NULL) 
    {
        struct accounts *temp = current;    //assign temp pointer to head node
        current = current->next;        //move current pointer to next node
        free(temp);         //free the previous node
        temp = NULL;        //making temp as null to avoid dangling pointer
    }

    return 0;
}
