#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


void deposit();
void withdraw();
void wallet();
void coin();
void sps();
void gusseTheNumber();
void game();
void gameWalletChoice();
void login();
void newAccount();
void authentication();
void Welcome();
void showData();
void insights();
void adminPannel();
int getUserIndex(const char *target, int size);





char password[20];
char username[20];
char user[500][15]={"admin"};
char passkey[500][15]={"admin"};
int wallet_balance[500]= {0};
int pointer = 0;
int size = sizeof(user) / sizeof(user[0]);
int totalDeposit = 0;
int totalWithdrawal = 0;
int coinProfit = 0;
int coinLoss = 0;
int spsProfit = 0;
int spsLoss = 0;
int gusseTheNumberProfit = 0;
int gusseTheNumberLoss = 0;
void clearScreen() {printf("\e[1;1H\e[2J");};
int checkPass(const char *user_name, const char *pass, int size);











int getUserInput() {
    int choice;
    while (scanf("%d", &choice) != 1) {
        printf("Invalid input. Please enter a number.\n");
        while (getchar() != '\n'); // Clear the buffer
    }
    return choice;
}

void GameP_L(){
    int choice;
    printf("1 - Gusse The Number        ");
    printf("2 - Stone Paper Scissors        ");
    printf("3 - Flip The Coin        ");
    printf("4 - Go Back \n");  
    choice = getUserInput();
    if (choice == 1) {
        printf("\nTotal Wining is - $%d",gusseTheNumberProfit);
        printf("\nTotal Lossing is - $%d\n\n",gusseTheNumberLoss);
        if(gusseTheNumberProfit==gusseTheNumberLoss) printf("Deposite And Withrawal amount is same");
        else if(gusseTheNumberProfit>gusseTheNumberLoss) printf("Net Profit is - $%d", gusseTheNumberProfit - gusseTheNumberLoss);
        else if(gusseTheNumberProfit<gusseTheNumberLoss) printf("Net Loss is - $%d", gusseTheNumberLoss - gusseTheNumberProfit);
        printf("\n\n");
        GameP_L();
    }
    else if (choice == 2) {
        printf("\nTotal Wining is - %d",spsProfit);
        printf("\nTotal Lossing is - %d\n\n",spsLoss);
        if(spsProfit==spsLoss) printf("Deposite And Withrawal amount is same");
        else if(spsProfit>spsLoss) printf("Net Profit is - %d", spsProfit - spsLoss);
        else if(spsProfit<spsLoss) printf("Net Loss is - %d", spsLoss - spsProfit);
        printf("\n\n");
        GameP_L();
    } 
    else if (choice == 3) {
        printf("\nTotal Wining is - %d",coinProfit);
        printf("\nTotal Lossing is - %d\n\n",coinLoss);
        if(coinProfit==coinLoss) printf("Deposite And Withrawal amount is same");
        else if(coinProfit>coinLoss) printf("Net Profit is - %d", coinProfit - coinLoss);
        else if(coinProfit<coinLoss) printf("Net Loss is - %d", coinLoss - coinProfit);
        printf("\n\n");
        GameP_L();
    }
    else if (choice == 4)
    {
        adminPannel();
    }
    
}

void insights(){
    printf("\nTotal Deposite is - $%d", totalDeposit);
    printf("\nTotal Withrawal is - $%d\n\n", totalWithdrawal);
    if(totalDeposit==totalWithdrawal) printf("Deposite And Withrawal amount is same");
    else if(totalDeposit>totalWithdrawal) printf("Net Profit is - $%d", totalDeposit - totalWithdrawal);
    else if(totalDeposit<totalWithdrawal) printf("Net Loss is - $%d", totalWithdrawal - totalDeposit);
    printf("\n\n");
    adminPannel();
}

void updateBalance(){
    char selectedUsername[20];
    printf("Enter username: ");
    scanf("%s", selectedUsername);
    printf("Enter wallet balance - ");
    scanf("%d", &wallet_balance[getUserIndex(selectedUsername, pointer + 1)]);
    printf("Wallet Balance Updated Sucessfully");
    showData();
}
 
void showData(){
    int choice ;
    for (int i = 0; i < size; i++) {
        if(strcmp("", user[i]) == 0) continue;
        printf("%s   %s   %d\n", user[i], passkey[i], wallet_balance[i]);
    }
    printf("\n \n");
    printf("1 - Update Wallet Balance             2- Go Back");
    choice = getUserInput();

    if (choice == 1)
    {
        updateBalance();
    }

    if (choice == 2)
    {
        adminPannel();
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

int getUserIndex(const char *target, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(target, user[i]) == 0) {
            return i; 
        }
    }
    return -1;
}

void deposit() {
    printf("Enter amount you want to deposit: ");
    int balance;
    scanf("%d", &balance);
    printf("Deposite sucessfull !!!\n");
    totalDeposit += balance;
    wallet_balance[getUserIndex(username, pointer + 1)] += balance;
    printf("Your Total Balance is $%d\n", wallet_balance[getUserIndex(username, pointer + 1)]);
    gameWalletChoice();
}

void withdraw()
{
    while (1) {
        printf("Enter amount you want to withdraw: ");
        int balance;
        scanf("%d", &balance);
        if (balance > wallet_balance[getUserIndex(username, pointer + 1)])
        {
            printf("Your enter amount is larger than your balance.\n");
            break;
        }
        else if(balance == 0) {
            printf("You can't withdraw $0.\n");
        }
        else
        {
            char pass[20];
            printf("Enter your password: ");
            scanf("%s", pass);
            if (checkPass(username, pass, pointer + 1)){
            printf("Withdrawal successful !!!\n");
            wallet_balance[getUserIndex(username, pointer + 1)] -= balance;
            totalWithdrawal += balance;
            printf("Your Total Balance is $%d \n", wallet_balance[getUserIndex(username, pointer + 1)]);
            break; }
            else{
                printf("\nIncorrect password.\n");
            }
        }
    }
    gameWalletChoice();
}

void wallet()
{
    printf("Your Wallet Balance is - $%d \n", wallet_balance[getUserIndex(username, pointer + 1)]);
    int choice;
    printf("1 - Deposit       ");
    printf("2 - Withrawal       ");
    printf("3 - Go Back \n");
    choice = getUserInput();

    if (choice == 1)deposit();
    if (choice == 2)withdraw();
    if (choice == 3)gameWalletChoice();
    

}

void coin_rule(){
     printf("********************* Rules ************************\n");
    printf("----------------------------------------------------\n");
    printf("1. You have to guess between Head and Tail\n");
    printf("2. If you guess correct number you win the bet and get Double of your bet Amount.\n");
    printf("3. If you guess wrong you loss your betting Amount.\n\n");
    coin();
}

void coin(){
    int choice;
    do {
        printf("Your Wallet Balance is - $%d\n", wallet_balance[getUserIndex(username, pointer + 1)]);
        printf("Choose Between Head and Tail \n1 - Head\n2 - Tail\n");
        int number;
        scanf("%d", &number);
        printf("Enter The Amount You Want To Bet - ");
        int betAmount;
        scanf("%d", &betAmount);

        if (betAmount > wallet_balance[getUserIndex(username, pointer + 1)])
        {
            printf("You don't have enough balance to bet.\n");
            printf("1 - Deposit         ");
            printf("2 - Restart \n");
            choice = getUserInput();
            if (choice == 1)
                deposit();
        }
        else
        {
            int randomnumber = 1 + rand() % 2;
            if (number == randomnumber)
            {
                wallet_balance[getUserIndex(username, pointer + 1)] += betAmount ;
                coinProfit += betAmount;
                printf("\nYou Win The Bet And Get $%d\nAvailable balance is $%d\n", betAmount * 2, wallet_balance[getUserIndex(username, pointer + 1)]);
            }
            else
            {
                wallet_balance[getUserIndex(username, pointer + 1)] -= betAmount;
                coinLoss += betAmount; 
                printf("\nYou Lose The Bet \nAvailable balance is $%d\n", wallet_balance[getUserIndex(username, pointer + 1)]);
            }
        }

        printf("1 - Play Again\n");
        printf("2 - Exit\n");
        choice = getUserInput();
    } while (choice == 1);
    game();
}

void sps_rule(){
    printf("********************* Rules ************************\n");
    printf("----------------------------------------------------\n");
    printf("1. You have to choose from Stone , Paper and Scissors\n");
    printf("2. If you win the bet and get Double of your bet Amount.\n");
    printf("3. If you lose , you loss your betting Amount.\n\n");
    sps();
}

void sps(){
    printf("Your Wallet Balance is - $%d\n", wallet_balance[getUserIndex(username, pointer + 1)]);
    printf("Choose One from the three menioned below:\n1 - Stone\n2 - Paper\n3 - Scissors\n");
    int number;
    scanf("%d", &number);
    printf("Enter The Amount You Want To Bet - ");
    int betAmount;
    scanf("%d", &betAmount);
    if (betAmount > wallet_balance[getUserIndex(username, pointer + 1)])
    {
        printf("You don't have enough balance to bet.\n");
        printf("1 - Deposit         ");
        printf("2 - Restart \n");
        int choice;
        choice = getUserInput();
        if (choice == 1)
            deposit();
        else
            sps();
    }
    else
    {
        int randomnumber;
        randomnumber = 1 + rand() % 3;
        if (randomnumber == 1){
            if (number == 1){
                printf("Its a Draw\n");
            }
            if (number == 2){
                if(randomnumber==1) printf("Your Computer has choosen Stone");
                if(randomnumber==2) printf("Your Computer has choosen Paper");
                if(randomnumber==3) printf("Your Computer has choosen Scissors");
                wallet_balance[getUserIndex(username, pointer + 1)] -= betAmount;
                spsProfit += betAmount;
                printf("\nYou Loss The Bet \nAvailable balance is $%d\n", wallet_balance[getUserIndex(username, pointer + 1)]);
            }
            if (number == 3){
                wallet_balance[getUserIndex(username, pointer + 1)] += betAmount ;
                spsLoss += betAmount;
                printf("\nYou Win The Bet And Get $%d\nAvailable balance is $%d\n", betAmount * 2, wallet_balance[getUserIndex(username, pointer + 1)]);
            }
        }
        else if (randomnumber == 2){
            if (number == 2){
                printf("Its a Draw\n");
            }
            if (number == 1){
                if(randomnumber==1) printf("Your Computer has choosen Stone");
                if(randomnumber==2) printf("Your Computer has choosen Paper");
                if(randomnumber==3) printf("Your Computer has choosen Scissors");
                wallet_balance[getUserIndex(username, pointer + 1)] -= betAmount;
                spsProfit += betAmount;
                printf("\nYou Loss The Bet \nAvailable balance is $%d\n", wallet_balance[getUserIndex(username, pointer + 1)]);
            }
            if (number == 3){
                wallet_balance[getUserIndex(username, pointer + 1)] += betAmount ;
                spsLoss += betAmount;
                printf("\nYou Win The Bet And Get $%d\nAvailable balance is $%d\n", betAmount * 2, wallet_balance[getUserIndex(username, pointer + 1)]);
            }
        }
        else if (randomnumber == 3){
            if (number == 3){
                printf("Its a Draw\n");
            }
            if (number == 2){
                if(randomnumber==1) printf("Your Computer has choosen Stone");
                if(randomnumber==2) printf("Your Computer has choosen Paper");
                if(randomnumber==3) printf("Your Computer has choosen Scissors");
                wallet_balance[getUserIndex(username, pointer + 1)] -= betAmount;
                spsProfit += betAmount;
                printf("\nYou Loss The Bet \nAvailable balance is $%d\n", wallet_balance[getUserIndex(username, pointer + 1)]);
            }
            if (number == 1){
                wallet_balance[getUserIndex(username, pointer + 1)] += betAmount ;
                spsLoss += betAmount;
                printf("\nYou Win The Bet And Get $%d\nAvailable balance is $%d\n", betAmount * 2, wallet_balance[getUserIndex(username, pointer + 1)]);
            }
        }
    }
    printf("1 - Play Again\n");
    printf("2 - Exit\n");
    int choice;
    choice = getUserInput();
    if (choice == 1)
        sps();
    else
        game();
}

void gusseTheNumber_rule(){
    printf("********************* Rules ************************\n");
    printf("----------------------------------------------------\n");
    printf("1. You have to guess a number between 1 to 10\n");
    printf("2. If you guess correct number you win the bet and get 10 times of your bet Amount.\n");
    printf("3. If you guess wrong you loss your betting Amount.\n\n");
    gusseTheNumber();
}

void gusseTheNumber()
{
    
    printf("Your Wallet Balance is - $%d\n", wallet_balance[getUserIndex(username, pointer + 1)]);
    printf("Choose The Number between 1 to 10 - ");
    int number;
    scanf("%d", &number);
    printf("Enter The Amount You Want To Bet - ");
    int betAmount;
    scanf("%d", &betAmount);
    if (betAmount > wallet_balance[getUserIndex(username, pointer + 1)])
    {
        printf("You don't have enough balance to bet.\n");
        printf("1 - Deposit         ");
        printf("2 - Restart \n");
        int choice;
        choice = getUserInput();
        if (choice == 1)
            deposit();
        else
            gusseTheNumber();
    }
    else
    {
        int randomnumber;
        randomnumber = rand() % 10 +1;
        if (number == randomnumber)
        {
            wallet_balance[getUserIndex(username, pointer + 1)] += betAmount * 9;
            gusseTheNumberLoss += betAmount*9;
            printf("\nYou Win The Bet And Get $%d\nAvailable balance is $%d\n", betAmount * 10, wallet_balance[getUserIndex(username, pointer + 1)]);
        }
        else
        {
            printf("Correct Number is %d",randomnumber);
            wallet_balance[getUserIndex(username, pointer + 1)] -= betAmount;
            gusseTheNumberProfit += betAmount;
            printf("\nYou Loss The Bet \nAvailable balance is $%d\n", wallet_balance[getUserIndex(username, pointer + 1)]);
        }
    }
    printf("1 - Play Again\n");
    printf("2 - Exit\n");
    int choice;
    choice = getUserInput();
    if (choice == 1)
        gusseTheNumber();
    else
        game();
}

void game()
{
    printf("Choose the game you want to play\n");
    printf("1 - Guess The Number\n");
    printf("2 - Rock Paper Scissors\n");
    printf("3 - Flip the Coin\n");
    printf("4 - Exit\n");
    int choice;
    choice = getUserInput();
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
    choice = getUserInput();
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
        clearScreen();
        authentication();
        return;
    }
}

int checkPass(const char *user_name, const char *pass, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(user_name, user[i]) == 0) {
            if(strcmp(pass, passkey[i]) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void adminPannel(){
    clearScreen();
    printf("\n\nAdmin pannel unlocked");
    printf("\n\n");
    int choice;
    printf("1 - Insights        ");
    printf("2 - Every Game Detail        ");
    printf("3 - Details of users        ");
    printf("4 - Logout \n");  
    choice = getUserInput();
    if (choice == 1) {
        insights();
    } 
    else if (choice == 2) {
        GameP_L();
    } 
    else if (choice == 3) {
        showData(); 
    } 
    else if (choice == 4) {  
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
    if(strcmp(username, user[0]) == 0 && strcmp(password, passkey[0]) == 0){
    adminPannel();
    }
    else{
        if (newUser(username, pointer + 1) == 0) {
        if (checkPass(username, password, pointer + 1)) {
            clearScreen();
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
        printf("\nUser does not exist. Please create a new account.\n");
        authentication();
        }
    }
    
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
    choice = getUserInput();
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
        authentication();
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
