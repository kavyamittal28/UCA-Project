#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

void login()
{
    printf("Enter your username: ");
    char username[20];
    scanf("%s", username);
    printf("Enter your password: ");
    char password[20];
    scanf("%s", password);
    printf("--------------------------------------------------\n");
    printf("          Welcome Back To Casino Hunter!\n");
    printf("--------------------------------------------------\n");
    gameWalletChoice();
}

void newAccount()
{
    printf("Set your username: ");
    char username[20];
    scanf("%s", username);
    printf("Set your password: ");
    char password1[20];
    scanf("%s", password1);
    printf("Confirm your password: ");
    char password2[20];
    scanf("%s", password2);

    // printf("%s", password1);
    // printf("%s", password2);

    if (strcmp(password1, password2) == 0)
    {
        printf("--------------------------------------------------\n");
        printf("             Welcome To Casino Hunter!\n");
        printf("--------------------------------------------------\n");
        gameWalletChoice();
    }

    else
    {
        printf("\nYour password doesn't match. Try Again!!\n");
        newAccount();
    }
}

void authentication()
{
    printf("1 - Login        ");
    printf("2 - Create an account \n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1)
    {
        login();
    }

    else if (choice == 2)
    {
        newAccount();
    }
    else
    {
        printf("INVALID INPUT!!! \n Please Read Instructions Carefully");
    }
}

void Welcome()
{
    printf("--------------------------------------------------\n");
    printf("--------------------------------------------------\n");
    printf("             Welcome To Casino Hunter!\n");
    printf("--------------------------------------------------\n");
    printf("--------------------------------------------------\n");
    printf("\n\n");
    authentication();
};

int main()
{
    Welcome();
    return 0;
}
