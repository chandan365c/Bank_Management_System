#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    int choice, verify;
    float amount, balance=0;
    printf("Welcome to Vijay Malya bank!!\n");
    printf("\n");
    printf("Please answer the following question to verify you are not a robot\n");
    printf("\n");
    printf("What is 10+5?\n");
    printf("Ans = ");
    scanf("%d", &verify);
    if(verify==15)
    {
        sleep(1);
        printf("\n");
        printf("VERIFICATION COMPLETE\n");
        printf("\n");
        sleep(0.5);
        printf("Welcome to Vijay Malya bank!!\n");
        sleep(1);

        do
        {
            printf("Please select what would you like to do\n");
            printf("1. Deposit\n");
            printf("2. Withdrawl\n");
            printf("3. Check Balance\n");
            printf("4. Exit");
            printf("\n");
            prompt_choice:
                printf("Please enter your choice: ");
                scanf("%d", &choice);
            printf("\n");
            switch(choice)
            {
                case 1:
                {
                    prompt_1:
                        printf("Enter the amount to deposit: ");
                        scanf("%f", &amount);
                    if(amount<=0)
                    {
                        printf("Invalid Amount! Please enter a higher value!\n");
                        goto prompt_1;
                    }
                    else
                    {
                        balance = balance + amount;
                        sleep(0.5);
                        printf("Deposited successfully!\n");
                        printf("\n");
                        sleep(1);
                    }
                    break;
                }
                case 2:
                {
                   prompt_2:
                        printf("Enter the amount to Withdraw: ");
                        scanf("%f", &amount);
                    if(amount > balance)
                    {
                        printf("Insufficient balance! Please check your balance and try again!\n");
                        goto prompt_2;
                    }
                    else
                    {
                        balance = balance - amount;
                        sleep(0.5);
                        printf("Withdrawl successful!\n");
                        printf("\n");
                        sleep(1);
                    }
                    break; 
                }
                case 3:
                {
                    printf("Fetching balance. . . .\n");
                    printf("\n");
                    sleep(1);
                    printf("Balance fetched successfully");
                    printf("\n");
                    printf("Available balance = %.2f\n",balance);
                    printf("\n");
                    sleep(1);
                    break;
                }
                case 4:
                {
                    printf("Exiting. . .");
                    printf("\n");
                    sleep(1);
                    printf("Thank you for banking with us!\n");
                    printf("\n");
                    break;
                }
                default:
                {
                    printf("Invalid choice! Please choose a valid option!\n");
                    printf("\n");
                    goto prompt_choice;
                }
            }

        } while (choice!=4);
        
    }
    else
    {
        printf("\n");
        printf("OOPS! INCORRECT ANSWER!\n");
        printf("\n");
        printf("VERIFICATION FAILED!\n");
        printf("\n");
        printf("Exiting. . .");
        printf("\n");
        sleep(1);
        exit(0);
    }
    return 0;
}