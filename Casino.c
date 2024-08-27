#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>



void game()
{
    printf("Choose the game you want to play\n");
    printf("1 - Guess The Number\n");
    printf("2 - Rock Paper Scissors\n");
    printf("3 - Flip the Coin\n");
    printf("4 - Exit\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1)        gusseTheNumber_rule();
    if (choice == 2)        sps_rule();
    if (choice == 3)        coin_rule();
    if (choice == 4)        gameWalletChoice();
}

void gameWalletChoice()
{
    int choice;
    printf("1 - Game        ");
    printf("2 - Wallet        ");
    printf("3 - Logout \n");
    scanf("%d", &choice);
    if (choice == 1)
    {
        game();
    }
    else if (choice == 2)
    {
        wallet();
    }
    else if (choice == 3)
    {
        printf("\n\n\n");
        authentication();
    }
}


void login()
{
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);
    if(strcmp(username, user[0]) == 0 && strcmp(password, user[0]) == 0){
        adminPannel();
    }
    else{
        if (newUser(username, pointer + 1) == 0) {
        if (checkPass(username, password, pointer + 1)) {
            printf("--------------------------------------------------\n");
            printf("          Welcome Back To Casino Hunter!\n");
            printf("--------------------------------------------------\n");
            gameWalletChoice();
            } 
            else {
            printf("!! Incorrect Password !!\n");
            authentication();
            }
        } 
        else 
        {
        printf("User does not exist. Please create a new account.\n");
        authentication();
        }
    }
    
}

int newUser(const char *target, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(target, user[i]) == 0) {
            return 0; 
        }
    }
    return 1;
}

void newAccount() {
    char newUsername[20], newPassword[20], password2[20];
    printf("Set your username: ");
    scanf("%s", newUsername);
    printf("Set your password: ");
    scanf("%s", newPassword);
    printf("Confirm your password: ");
    scanf("%s", password2);

    if (strcmp(newPassword, password2) == 0) {
        if (newUser(newUsername, pointer + 1)) {
            pointer++;
            strcpy(user[pointer], newUsername);
            strcpy(passkey[pointer], newPassword);
            printf("--------------------------------------------------\n");
            printf("             Welcome To Casino Hunter!\n");
            printf("--------------------------------------------------\n");
            gameWalletChoice();
        } else {
            printf("Username already exists.\n");
            newAccount();  
        }
    } else {
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
