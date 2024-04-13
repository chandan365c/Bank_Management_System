#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
//#include<Bank_Man.h>

int num_users=0;
char user_usernames[10][15]; //maximum users are 10 and max length of username is 15
char user_passwords[10][15];
float user_balances[10];
enum defined_acc_types{Salary, FD, Savings, RD};
char account_type[10];
int user_arr_index=-1;

void CreateAcc()
{
    int acc_type_prompt;
    printf("Enter username: ");
    scanf("%s", user_usernames[num_users]);
    printf("Set a strong password: ");
    scanf("%s", user_passwords[num_users]);
    printf("\n");
    user_balances[num_users] = 0;
    printf("What type of account would you like to create?\n");
    printf("    1. Salary Account\n");
    printf("    2. Fixed Deposits Account\n");
    printf("    3. Savings Account\n");
    printf("    4. Recurring Deposits Account\n");
    printf("\n");
    printf("Select your type of account: ");
    scanf("%d", &acc_type_prompt);
    switch(acc_type_prompt)
    {
        case 1:
        {
            account_type[num_users] = (enum defined_acc_types)acc_type_prompt ;
            printf("\n");
            sleep(1);
            printf("Salary account created...\n");
            sleep(1.5);
            printf("Please Login to your account to view balance or perform transactions\n");
            printf("\n");
            printf("Redirecting to Home page. . . .");
            printf("\n");
            sleep(2);
            printf("\n");
            break;
        }
        case 2:
        {
            account_type[num_users] = (enum defined_acc_types)acc_type_prompt ;
            printf("\n");
            sleep(1);
            printf("Fixed Deposits account created...\n");
            sleep(1.5);
            printf("Please Login to your account to view balance or perform transactions\n");
            printf("\n");
            printf("Redirecting to Home page. . . .");
            printf("\n");
            sleep(2);
            printf("\n");
            break;
        }
        case 3:
        {
            account_type[num_users] = (enum defined_acc_types)acc_type_prompt ;
            printf("\n");
            sleep(1);
            printf("Savings account created...\n");
            sleep(1.5);
            printf("Please Login to your account to view balance or perform transactions\n");
            printf("\n");
            printf("Redirecting to Home page. . . .");
            printf("\n");
            sleep(2);
            printf("\n");
            break;
        }
        case 4:
        {
            account_type[num_users] = (enum defined_acc_types)acc_type_prompt ;
            printf("\n");
            sleep(1);
            printf("Recurring Deposits account created...\n");
            sleep(1.5);
            printf("Please Login to your account to view balance or perform transactions\n");
            printf("\n");
            printf("Redirecting to Home page. . . .");
            printf("\n");
            sleep(2);
            printf("\n");
            break;
        }
    }
    num_users++;
}

bool Login()
{
    //Verify login credentials
    //Need to check whether user exists. If not, redirect to main page
    char username[15], password[15];
    printf("Welcome back! Please login with your details!\n");
    printf("\n");
    printf("Enter username: ");
    scanf("%s", username);
    for(int i=0; i<num_users; i++)
    {
        if(user_usernames[i]==username[i])
        {        
            //printf("\n");
            printf("Enter password: ");
            scanf("%s", password);

            if(user_passwords[i]==password[i])
            {
                printf("\n");
                printf("Logged in successfully!\n");
                printf("\n");
                printf("Welcome %s!",user_usernames[i]);
                printf("\n");
                user_arr_index=i;
                return true;    //User is authentic
            }
            else
            {
                return false;   //Password is wrong
            }
        }
        //return false;
    }
}

void check_balance(int user_index)
{
    printf("\n");
    printf("Fetching balance. . .\n");
    printf("\n");
    sleep(1);
    printf("Current available balance is %.2f\n", user_balances[user_index]);
    printf("\n");
}

int Deposit(int user_index, float amount)
{
    user_balances[user_index] = user_balances[user_index] + amount;
    printf("%.2f deposited into your account!\n", amount);
}

int Withdraw(int user_index, float amount)
{
    if (user_balances[user_index]>= amount) 
    {
        user_balances[user_index] = user_balances[user_index]- amount;
        printf("%.2f withdrawn successfully!\n", amount);
    } 
    else 
    {
        printf("Insufficient balance! Please check your balance and try again\n");
    }
}


int main()
{
    int choice, action;

    do  //Looping until user enters 3 to exit
    {
        printf("Welcome to Vijay Malya Bank! Please choose your option...\n");
        printf("1. Create Account\n");
        printf("2. Log into existing account\n");
        printf("3. Exit\n");
        printf("\n");

        prompt_choice:                              //Label to prompt user to enter their choice
            printf("Please enter your choice: ");
            scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            {
                if(num_users<10)
                {
                    CreateAcc();
                }
                else
                {
                    printf("\n");
                    printf("Sorry! The maximum number of accounts have been reached, try again later!\n");
                    printf("\n");
                    printf("Redirecting. . .");
                    printf("\n");
                    sleep(1);
                    printf("\n");
                    break;
                }
                break;
            }
            case 2:
            {
                if(Login())
                {
                    int user_action;
                    float amount;
                    do
                    {
                        printf("How would you like to bank with us today?\n");
                        printf("1. Make a deposit\n");
                        printf("2. Withdraw money\n");
                        printf("3. Check available balance\n");
                        printf("4. Logout");
                        printf("\n");

                        prompt_action:                              //Label to prompt user to choose action
                            printf("Please enter your choice: ");
                            scanf("%d", &user_action);

                        switch(user_action) {
                            case 1:
                                printf("Enter the amount to deposit: ");
                                scanf("%f", &amount);
                                Deposit(user_arr_index, amount);
                                break;

                            case 2:
                                printf("Enter the amount to withdraw: ");
                                scanf("%f", &amount);
                                Withdraw(user_arr_index, amount);
                                break;

                            case 3:
                                check_balance(user_arr_index);
                                break;

                            case 4:
                                printf("Logging out. . . \n");
                                printf("\n");
                                sleep(1);
                                printf("\n");
                                printf("Logged out successfully!\n");
                                printf("\n");
                                break;

                            default:
                                printf("\n");
                                printf("Invalid choice! Please choose the appropriate action from the above list\n");
                                sleep(1);
                                printf("\n");
                                goto prompt_action;

                        }
                    } while (user_action!=4);
                    
                }
                else
                {
                    printf("\n");
                    printf("Login failed! Check the username and password!");
                    printf("\n");
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
                printf("Invalid choice! Please choose the appropriate choice from the above list\n");
                sleep(1);
                printf("\n");
                goto prompt_choice;

            }
        }
    } while(choice!=3);

    return 0;
}