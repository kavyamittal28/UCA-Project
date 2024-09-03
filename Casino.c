
#include <stdio.h>
// #include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

void roulette_game();
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
int getUserInput();
void adminPannel();
void wait();
int usernameExists(const char *filename, const char *username);
void updateCombinedTotals(int depositAmount, int withdrawalAmount);
void updateWalletBalance(const char *filename, const char *username, int newBalance);
int getTotalDeposits();
int getTotalWithdrawals();
int getUserIndex(const char *target, int size);

#define MAX_NUM 36
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20



char passwordFetched[21];
char currentUsername[21];
void clearScreen() {printf("\e[1;1H\e[2J");};
const char *filename = "userdata.csv";
const char *transaction_filename = "transactions.csv";



void walletChange(){
    char username[MAX_USERNAME_LENGTH];
    printf("Enter Username: ");
    scanf("%s", username);
    if(usernameExists(filename,username)==1){
        printf("Enter Amount: ");
        int amount;
        scanf("%d",&amount);
        updateWalletBalance(filename,username,amount);
        printf("Balance Updated Sucssfully!!\n");
        printf("Redirecting to Previous Menu");
        wait();
    }
    else{
        printf("Username does not exist!!\n");
        printf("Redirecting to Previous Menu");
        wait();
    }
    clearScreen();
    adminPannel();
}

void load(){
    int i, j;

    for (i = 0; i < 6; i++) {
        printf("\rProgress: [");
        for (j = 0; j <= i * 5; j++) {
            printf("#");
        }
        for (j = 0; j < 25 - i * 5; j++) {
            printf(" ");
        }
        printf("] %d%%", i * 20);
        fflush(stdout);
        sleep(1);

    }


    return 0;
}

void wait(){
    for (int j = 0; j < 3; j++) {
        fflush(stdout);
        sleep(1);
    }
}

void spin(){
    const char spinners[] = "|/-\\|/-\\|/-\\";
    int i = 0;

    for (int j = 0; j < 5; j++) {
        printf("\rSpining %c", spinners[i++ % 8]);
        fflush(stdout);
        sleep(1);
    }
}

void updateCombinedTotals(int depositAmount, int withdrawalAmount) {
    FILE *file = fopen(transaction_filename, "r");
    FILE *tempFile = fopen("temp_transactions.csv", "w");

    if (!file || !tempFile) {
        printf("Error opening transaction files.\n");
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return;
    }

    char line[256];
    int totalDeposit = 0, totalWithdrawal = 0;

    // Read the current totals from the file
    if (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d,%d", &totalDeposit, &totalWithdrawal);
    }

    // Update totals
    totalDeposit += depositAmount;
    totalWithdrawal += withdrawalAmount;

    // Write updated totals back to the file
    fprintf(tempFile, "%d,%d\n", totalDeposit, totalWithdrawal);

    fclose(file);
    fclose(tempFile);

    // Replace the old file with the updated one
    remove(transaction_filename);
    rename("temp_transactions.csv", transaction_filename);
}

int getTotalDeposits() {
    FILE *file = fopen(transaction_filename, "r");
    if (!file) {
        printf("Error opening transaction file.\n");
        return -1;
    }

    int totalDeposit = 0, totalWithdrawal = 0;
    fscanf(file, "%d,%d", &totalDeposit, &totalWithdrawal);
    fclose(file);

    return totalDeposit;
}

int getTotalWithdrawals() {
    FILE *file = fopen(transaction_filename, "r");
    if (!file) {
        printf("Error opening transaction file.\n");
        return -1;
    }

    int totalDeposit = 0, totalWithdrawal = 0;
    fscanf(file, "%d,%d", &totalDeposit, &totalWithdrawal);
    fclose(file);

    return totalWithdrawal;
}

void insights()
{
    clearScreen();
    int totalDeposit = getTotalDeposits();
    int totalWithdrawal = getTotalWithdrawals();

    printf("Total Deposit: %d\n", totalDeposit);
    printf("Total Withdrawal: %d\n", totalWithdrawal);

    if (totalDeposit > totalWithdrawal){
        printf("Total Profit is: %.2f\n\n", (float)(totalDeposit - totalWithdrawal));
    }
    else if (totalDeposit == totalWithdrawal){
        printf("Total Deposit and Total Withdrawal are the same.\n");
    }
    else{
        printf("Total Loss is: %.2f\n\n", (float)(totalWithdrawal - totalDeposit));
    }

    printf("Enter any key to exit - ");
    scanf("%*s");
    clearScreen();
    adminPannel();
}

void showData(const char *filename) {
    // Open the CSV file in read mode
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: Could not open file %s.\n", filename);
        return;
    }

    char username[50];
    char password[50];
    double walletBalance;

    // Read and print data from the CSV file line by line
    while (fscanf(file, "%49[^,],%49[^,],%lf\n", username, password, &walletBalance) == 3) {
        printf("Username: %s\n", username);
        printf("Password: %s\n", password);
        printf("Wallet Balance: %.2f\n\n", walletBalance);
    }

    // Close the file after reading
    fclose(file);
    printf("\n\n");
    printf("Enter Anything To go back : ");
    scanf("%*s");
    admin();
}

void admin(){
    clearScreen();
    printf("--------------------------------------------------\n");
    printf("--------------------------------------------------\n");
    printf("                Welcome Admin!\n");
    printf("--------------------------------------------------\n");
    printf("--------------------------------------------------\n");
    printf("\n\n");
    adminPannel();
}

void adminPannel(){
    int choice;
    printf("1 - Insights\t\t");
    printf("2 - User List \t\t");
    printf("3 - Change Wallet Balance \t\t");
    printf("4 - Exit\n");
    choice = getUserInput();
    if (choice == 1) {
         insights();
    } else if (choice == 2) {
        showData(filename);
    } else if (choice == 3) {
        walletChange();
    } else if (choice == 4) {
        printf("Exiting...\n");
        wait();
        Welcome();
    } else {
        printf("Invalid choice. Please try again.\n");
        adminPannel();
    }
}

void updateWalletBalance(const char *filename, const char *username, int newBalance) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("helo");
         return;
    }

    FILE *tempFile = fopen("tempfile.csv", "w");
    if (tempFile == NULL) {
        fclose(file);
        printf("helo 1");
        return;
    }

    char line[256];
    int userFound = 0;

    if (fgets(line, sizeof(line), file) != NULL) {
        fprintf(tempFile, "%s", line);
    }

    while (fgets(line, sizeof(line), file)) {
        char fileUsername[20], password[20];
        int walletBalance;

        sscanf(line, "%19[^,],%19[^,],%d", fileUsername, password, &walletBalance);

        if (strcmp(fileUsername, username) == 0) {
            walletBalance = newBalance;
            userFound = 1;
        }

        fprintf(tempFile, "%s,%s,%d\n", fileUsername, password, walletBalance);
    }

    fclose(file);
    fclose(tempFile);

    if (remove(filename) != 0) {
        printf("helo 2");
        return;
    }

    if (rename("tempfile.csv", filename) != 0) {
        printf("helo 3");
        return;
    }

    
}

int getUserInput() {
    int choice;
    while (scanf("%d", &choice) != 1) {
        printf("Invalid input. Please enter a number.\n");
        while (getchar() != '\n'); // Clear the buffer
    }
    return choice;
}

void appendUserData(const char *filename, const char *username, const char *password) {

    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Set initial wallet balance to zero
    int walletBalance = 0;

    // Append the new user data to the CSV file
    fprintf(file, "%s,%s,%d\n", username, password, walletBalance);
    fclose(file);
}

int usernameExists(const char *filename, const char *username) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        // File does not exist, so the username cannot exist either
        return 0;
    }

    char line[256];
    char *fileUsername;

    // Read header line
    fgets(line, sizeof(line), file);

    // Read each line of the CSV file
    while (fgets(line, sizeof(line), file)) {
        // Strip newline characters
        line[strcspn(line, "\n")] = 0;

        // Tokenize the line to extract the username
        fileUsername = strtok(line, ",");

        // Compare the file username with the input username
        if (strcmp(fileUsername, username) == 0) {
            fclose(file);
            return 1; // Username exists
        }
    }

    fclose(file);
    return 0; // Username does not exist
}

int fetchWalletDetail(const char *filename, const char *username) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return -1;
    }

    char line[256];

    while (fgets(line, sizeof(line), file)) {
        char fileUsername[20], password[20];
        int walletBalance;

        if (sscanf(line, "%19[^,],%19[^,],%d", fileUsername, password, &walletBalance) != 3) {
            // Handle malformed lines gracefully
            fprintf(stderr, "Error parsing line: %s\n", line);
            continue;
        }

        if (strcmp(fileUsername, username) == 0) {
            fclose(file);
            return walletBalance;
        }
    }

    fclose(file);
    printf("User not found.\n");
    return -1;
}

const char* fetchPassword(const char *filename, const char *username) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }

    char line[256];
    char *fileUsername, *password;

    // Read header line
    fgets(line, sizeof(line), file);

    // Read each line of the CSV file
    while (fgets(line, sizeof(line), file)) {
        // Strip newline characters
        line[strcspn(line, "\n")] = 0;

        // Tokenize the line
        fileUsername = strtok(line, ",");
        password = strtok(NULL, ",");

        // Compare the file username with the input username
        if (strcmp(fileUsername, username) == 0) {
            fclose(file);
            return password;
        }
    }

    fclose(file);
    return NULL; // Username not found
}

int isRed(int number) {
    int reds[] = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};
    for (int i = 0; i < 18; i++) {
        if (reds[i] == number)
            return 1; // Number is red
    }
    return 0; // Number is black
}

void printRouletteTable() {
    printf("Roulette Table:\n\n");
    
    printf("   |");
    // Print numbers 1 to 36 with their colors
    for (int i = 1; i <= 36; i++) {
        if (isRed(i)) {
            printf(" \033[1;31m%2d \033[0m|", i); // Print red numbers
        } else {
            printf(" \033[1;30m%2d \033[0m|", i); // Print black numbers
        }
        if (i % 12 == 0) printf("\n   |"); // New line for every 12 numbers
    }
    printf("   0  |");
    printf("\n");
}

void roulette_rule(){
    clearScreen();
    printf("Welcome to Roulette Game!\n");
    printRouletteTable();
    printf("\nChoose your bet type:\n");
    printf("1. Bet on a number (0-36)\n");
    printf("2. Bet on color (r for red, b for black)\n");
    printf("3. Bet on 1st 12 (1-12), 2nd 12 (13-24), or 3rd 12 (25-36)\n\n");
    wait();
    roulette_game();
}

void roulette_game(){
    int choice, bet, numberBet, spinResult,betAmount;
    char colorBet;
    srand(time(0));
    printf("Enter your choice: ");
    choice = getUserInput();
    
    switch(choice) {
        case 1:
            printf("Enter the number you want to bet on (0-36): ");
            scanf("%d", &numberBet);
            if (numberBet < 0 || numberBet > MAX_NUM) {
                printf("Invalid number. Please choose a number between 0 and 36.\n");
                roulette_game() ;
            }
            break;
        case 2:
            printf("Enter the color you want to bet on (r for red, b for black): ");
            scanf(" %c", &colorBet);
            if (colorBet != 'r' && colorBet != 'b') {
                printf("Invalid color. Please choose 'r' for red or 'b' for black.\n");
                roulette_game() ;
            }
            break;
        case 3:
            printf("1 - 1st 12 \n2 - 2nd 12 \n3 - 3rd 12: ");
            printf("Choose your bet: ");
            scanf("%d", &bet);
            if (bet < 1 || bet > 3) {
                printf("Invalid choice. Please choose 1, 2, or 3.\n");
                roulette_game() ;
            }
            break;
        default:
            printf("Invalid choice. Restarting game.\n");
            roulette_game() ;
    }
    printf("Enter bet Ammount - ");
    scanf("%d",&betAmount);
    if (betAmount > fetchWalletDetail(filename,currentUsername))
        {
            printf("You don't have enough balance to bet.\n");
            printf("1 - Deposit         ");
            printf("2 - Restart \n");
            choice = getUserInput();
            if (choice == 1)
                deposit();
            else roulette_game();
        }
        else{
            spin();
            printf("\n");
            spinResult = rand() % 37; // Generate a random number between 0 and 36
            printf("The roulette spins and lands on %d.\n", spinResult);
            if (choice == 1) {
                if (spinResult == numberBet) {
                    updateWalletBalance(filename,currentUsername,fetchWalletDetail(filename,currentUsername) + betAmount*35);
                    printf("\nYou Win The Bet And Get $%d\nAvailable balance is $%d\n", betAmount * 36, fetchWalletDetail(filename,currentUsername));
                } 
                else {
                    updateWalletBalance(filename,currentUsername,fetchWalletDetail(filename,currentUsername) - betAmount);
                    printf("\nYou Loss The Bet\n Spin Result is - %d \nAvailable balance is $%d\n",spinResult , fetchWalletDetail(filename,currentUsername));
                    }
            } 
            else if (choice == 2) {
                int red = isRed(spinResult);
                if ((red && colorBet == 'r') || (!red && colorBet == 'b')) {
                    updateWalletBalance(filename,currentUsername,fetchWalletDetail(filename,currentUsername) + betAmount);
                    printf("\nYou Win The Bet And Get $%d\nAvailable balance is $%d\n", betAmount * 2, fetchWalletDetail(filename,currentUsername));
                } else {
                    updateWalletBalance(filename,currentUsername,fetchWalletDetail(filename,currentUsername) - betAmount);
                    printf("\nYou Loss The Bet\n Spin Result is - %d  \nAvailable balance is $%d\n",spinResult , fetchWalletDetail(filename,currentUsername));           }
            } 
            else if (choice == 3) {
                if ((bet == 1 && spinResult >= 1 && spinResult <= 12) ||
                    (bet == 2 && spinResult >= 13 && spinResult <= 24) ||
                    (bet == 3 && spinResult >= 25 && spinResult <= 36)) {
                    updateWalletBalance(filename,currentUsername,fetchWalletDetail(filename,currentUsername) + betAmount*2);
                    printf("\nYou Win The Bet And Get $%d\nAvailable balance is $%d\n", betAmount * 3, fetchWalletDetail(filename,currentUsername));
                } 
                else {
                    updateWalletBalance(filename,currentUsername,fetchWalletDetail(filename,currentUsername) - betAmount);
                    printf("\nYou Loss The Bet\n Spin Result is - %d  \nAvailable balance is $%d\n",spinResult , fetchWalletDetail(filename,currentUsername));
                }
            }
        }
        printf("1 - Play Again\n");
        printf("2 - Exit\n");
        choice = getUserInput();
        if(choice == 1) roulette_rule();
        else if(choice == 2) game();
        else printf("Invalid Input!\nExiting");wait();game();
}

void deposit() {
    clearScreen();
    printf("Deposit Amount Should be less than $50,000\n");
    printf("Enter amount you want to deposit: ");
    int balance;
    scanf("%d", &balance);
    if (balance > 49999) {
        printf("Amount should be less than $50,000\n");
        deposit();
    } else {
        printf("Enter Your UPI ID: ");
        scanf("%*s");
        printf("Accept the payment request on UPI app");
        wait();
        printf("Deposit successful!!!\n");

        updateWalletBalance(filename, currentUsername, fetchWalletDetail(filename, currentUsername) + balance);
        updateCombinedTotals(balance, 0);  // Update combined deposit total
        printf("Your Total Balance is $%d\n", fetchWalletDetail(filename, currentUsername));
    }
    clearScreen();
    gameWalletChoice();
}

void withdraw() {
    clearScreen();
    char inputPassword[MAX_PASSWORD_LENGTH];
    char *storedPassword;
    int userFound = 0;
    int passwordCorrect = 0;
    while (1) {
        printf("Enter amount you want to withdraw: ");
        int balance;
        scanf("%d", &balance);
        if (balance > fetchWalletDetail(filename, currentUsername)) {
            printf("Your entered amount is larger than your balance.\n");
            break;
        } else if (balance == 0) {
            printf("You can't withdraw $0.\n");
        } else {
            printf("Enter your password: ");
            scanf("%s", inputPassword);

            FILE *file = fopen(filename, "r");
            if (file == NULL) {
                printf("Error opening user data file.\n");
                return;
            }

            char csvUsername[20], csvPassword[20];
            int csvWalletBalance;

            // Skip header line
            fgets(csvUsername, sizeof(csvUsername), file);

            // Search for the user in the CSV file
            while (fscanf(file, "%[^,],%[^,],%d\n", csvUsername, csvPassword, &csvWalletBalance) == 3) {
                if (strcmp(currentUsername, csvUsername) == 0) {
                    userFound = 1;
                    if (strcmp(inputPassword, csvPassword) == 0) {
                        passwordCorrect = 1;
                        break;
                    }
                }
            }

            fclose(file);

            if (userFound && passwordCorrect) {
                load();
                printf("\nWithdrawal successful.\n");
                printf("Redirecting to previous menu");
                wait();
                clearScreen();
                updateWalletBalance(filename, currentUsername, fetchWalletDetail(filename, currentUsername) - balance);
                updateCombinedTotals(0, balance);  // Update combined withdrawal total
                wallet();
            } else if (userFound) {
                printf("Incorrect password. Please try again.\n");
                withdraw();
            }
        }
    }
}

void wallet()
{
    printf("Your Wallet Balance is - $%d \n", fetchWalletDetail(filename,currentUsername));
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
    clearScreen();
     printf("********************* Rules ************************\n");
    printf("----------------------------------------------------\n");
    printf("1. You have to guess between Head and Tail\n");
    printf("2. If you guess correct number you win the bet and get Double of your bet Amount.\n");
    printf("3. If you guess wrong you loss your betting Amount.\n\n");
    wait();
    coin();
}

void coin(){
    int choice;
        printf("Your Wallet Balance is - $%d\n", fetchWalletDetail(filename,currentUsername));
        printf("Choose Between Head and Tail \n1 - Head\n2 - Tail\n");
        int number;
        scanf("%d", &number);
        printf("Enter The Amount You Want To Bet - ");
        if(number>2 || number < 1){
        printf("Invalid Input");
        printf("Choose Either Head or Tail");
        coin();
    }
        int betAmount;
        scanf("%d", &betAmount);

        if (betAmount > fetchWalletDetail(filename,currentUsername))
        {
            printf("You don't have enough balance to bet.\n");
            printf("1 - Deposit         ");
            printf("2 - Restart \n");
            choice = getUserInput();
            if (choice == 1)
                deposit();
            else coin_rule();
        }
        else
        {
            printf("Fliping the coin...\n");
            wait();
            int randomnumber = 1 + rand() % 2;
            if (number == randomnumber)
            {
                updateWalletBalance(filename,currentUsername,fetchWalletDetail(filename,currentUsername) + betAmount);
                printf("\nYou Win The Bet And Get $%d\nAvailable balance is $%d\n", betAmount * 2, fetchWalletDetail(filename,currentUsername));
            }
            else
            {
                updateWalletBalance(filename,currentUsername,fetchWalletDetail(filename,currentUsername) - betAmount); 
                printf("\nYou Lose The Bet \nAvailable balance is $%d\n", fetchWalletDetail(filename,currentUsername));
            }
        }

        printf("1 - Play Again\n");
        printf("2 - Exit\n");
        choice = getUserInput();
        if(choice == 1) coin_rule();
        else if(choice == 2) game();
        else printf("Invalid Input!\nExiting");wait();game();
}

void sps_rule(){
    clearScreen();
    printf("********************* Rules ************************\n");
    printf("----------------------------------------------------\n");
    printf("1. You have to choose from Stone , Paper and Scissors\n");
    printf("2. If you win the bet and get Double of your bet Amount.\n");
    printf("3. If you lose , you loss your betting Amount.\n\n");
    wait();
    sps();
}

void sps(){
    printf("Your Wallet Balance is - $%d\n",fetchWalletDetail(filename,currentUsername));
    printf("Choose One from the three menioned below:\n1 - Stone\n2 - Paper\n3 - Scissors\n");
    int number;
    scanf("%d", &number);
    if(number>3 || number < 1){
        printf("Invalid Input!!\n");
        printf("Choose from Stone , Paper and Scissors\n");
        sps();
    }
    printf("Enter The Amount You Want To Bet - ");
    int betAmount;
    scanf("%d", &betAmount);
    if (betAmount > fetchWalletDetail(filename,currentUsername))
    {
        printf("You don't have enough balance to bet.\n");
        printf("1 - Deposit         ");
        printf("2 - Restart \n");
        int choice;
        choice = getUserInput();
        if (choice == 1)
            deposit();
        else
            sps_rule();
    }
    else
    {
        wait();
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
                updateWalletBalance(filename,currentUsername,fetchWalletDetail(filename,currentUsername) - betAmount);
                printf("\nYou Loss The Bet \nAvailable balance is $%d\n", fetchWalletDetail(filename,currentUsername));
            }
            if (number == 3){
                updateWalletBalance(filename,currentUsername,fetchWalletDetail(filename,currentUsername) + betAmount);
                printf("\nYou Win The Bet And Get $%d\nAvailable balance is $%d\n", betAmount * 2, fetchWalletDetail(filename,currentUsername));
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
                updateWalletBalance(filename,currentUsername,fetchWalletDetail(filename,currentUsername) - betAmount);                
                printf("\nYou Loss The Bet \nAvailable balance is $%d\n", fetchWalletDetail(filename,currentUsername));
            }
            if (number == 3){
                updateWalletBalance(filename,currentUsername,fetchWalletDetail(filename,currentUsername) + betAmount);                
                printf("\nYou Win The Bet And Get $%d\nAvailable balance is $%d\n", betAmount * 2, fetchWalletDetail(filename,currentUsername));
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
                updateWalletBalance(filename,currentUsername,fetchWalletDetail(filename,currentUsername) - betAmount);                
                printf("\nYou Loss The Bet \nAvailable balance is $%d\n", fetchWalletDetail(filename,currentUsername));
            }
            if (number == 1){
                updateWalletBalance(filename,currentUsername,fetchWalletDetail(filename,currentUsername) + betAmount);                
                printf("\nYou Win The Bet And Get $%d\nAvailable balance is $%d\n", betAmount * 2, fetchWalletDetail(filename,currentUsername));
            }
        }
    }
    printf("1 - Play Again\n");
    printf("2 - Exit\n");
    int choice;
    choice = getUserInput();
    if(choice == 1) sps_rule();
    else if(choice == 2) game();
    else printf("Invalid Input!\nExiting");wait();game();
}

void gusseTheNumber_rule(){
    clearScreen();
    printf("********************* Rules ************************\n");
    printf("----------------------------------------------------\n");
    printf("1. You have to guess a number between 1 to 10\n");
    printf("2. If you guess correct number you win the bet and get 10 times of your bet Amount.\n");
    printf("3. If you guess wrong you loss your betting Amount.\n\n");
    wait();
    gusseTheNumber();
}

void gusseTheNumber()
{
    
    printf("Your Wallet Balance is - $%d\n", fetchWalletDetail(filename,currentUsername));
    printf("Choose The Number between 1 to 10 - ");
    int number;
    scanf("%d", &number);
    if(number>10 || number < 1){
        printf("Invalid Input");
        printf("Enter Number Between 1 to 10");
        gusseTheNumber();
    } 
        
    printf("Enter The Amount You Want To Bet - ");
    int betAmount;
    scanf("%d", &betAmount);
    if (betAmount > fetchWalletDetail(filename,currentUsername))
    {
        printf("You don't have enough balance to bet.\n");
        printf("1 - Deposit         ");
        printf("2 - Restart \n");
        int choice;
        choice = getUserInput();
        if (choice == 1)
            deposit();
        else
            gusseTheNumber_rule();
    }
    else
    {
        int randomnumber;
        randomnumber = rand() % 10 +1;
        wait();
        if (number == randomnumber)
        {
            updateWalletBalance(filename,currentUsername,fetchWalletDetail(filename,currentUsername) + betAmount*9);
            printf("\nYou Win The Bet And Get $%d\nAvailable balance is $%d\n", betAmount * 10, fetchWalletDetail(filename,currentUsername));
        }
        else
        {
            printf("Correct Number is %d \n",randomnumber);
            updateWalletBalance(filename,currentUsername,fetchWalletDetail(filename,currentUsername) - betAmount);
            printf("\nYou Loss The Bet \nAvailable balance is $%d\n", fetchWalletDetail(filename,currentUsername));
        }
    }
    printf("1 - Play Again\n");
    printf("2 - Exit\n");
    int choice;
    choice = getUserInput();
    if(choice == 1) gusseTheNumber_rule();
    else if(choice == 2) game();
    else printf("Invalid Input!\nExiting");wait();game();
}

void game()
{
    clearScreen();
    printf("Choose the game you want to play\n");
    printf("1 - Guess The Number\n");
    printf("2 - Rock Paper Scissors\n");
    printf("3 - Flip the Coin\n");
    printf("4 - Roulette\n");
    printf("5 - Exit\n");
    int choice = getUserInput();
    if (choice == 1)        gusseTheNumber_rule();
    if (choice == 2)        sps_rule();
    if (choice == 3)        coin_rule();
    if (choice == 4)        roulette_rule();
    if (choice == 5)        gameWalletChoice();
    else{
        printf("Invalid Choice....Returning Back");
        wait();
        game();
    }
}

void gameWalletChoice()
{
    clearScreen();
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
    }else{
        printf("Invalid Choice....Returning Back");
        wait();
        gameWalletChoice();
    }
}

int isValidPassword(const char *password) {
    int hasUppercase = 0, hasSpecialChar = 0, hasNumeric = 0;
    int i;

    if (password == NULL || strlen(password) < 8) {
        return 0; // Password must be at least 8 characters long
    }

    for (i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) {
            hasUppercase = 1;
        } else if (isdigit(password[i])) {
            hasNumeric = 1;
        } else if (!isalpha(password[i]) && !isspace(password[i])) {
            hasSpecialChar = 1;
        }

        if (hasUppercase && hasNumeric && hasSpecialChar) {
            return 1; // Password meets all criteria
        }
    }

    return 0; // Password does not meet all criteria
}

void login()
{
    char inputUsername[MAX_USERNAME_LENGTH], inputPassword[MAX_PASSWORD_LENGTH];
    char *storedPassword;

    clearScreen();
    printf("*************** Login ***************\n");
    printf("Enter your username: ");
    scanf("%s", inputUsername);
    printf("Enter your password: ");
    scanf("%s", inputPassword);

    // Fetch stored password for the given username
    storedPassword = fetchPassword(filename, inputUsername);

    if (strcmp("admin", inputUsername) == 0 && strcmp("admin", inputPassword) == 0)
    {
        admin();
    }
    else
    {
        if (storedPassword != NULL && strcmp(inputPassword, storedPassword) == 0)
        {
            clearScreen();
            printf("Welcome back, %s!\n", inputUsername);
            strcpy(currentUsername, inputUsername); // Initialize currentUsername
            gameWalletChoice();
        }
        else
        {
            printf("Incorrect password. Please try again.\n");
            authentication();
        }
    }
}

void createAccount() {
    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];

    clearScreen();
    printf("\n");
    printf("**********************************************\n");
    printf("*************** Create Account ***************\n");
    printf("**********************************************\n");
    printf("Instructions:-\n");
    printf("1 - Enter Usename Without any Spaces\n");
    printf("2 - Password Must Contain at least 8 characters, 1 uppercase letter, 1 special character, and 1 numeric value.\n");
    printf("\nEnter Username: ");
    scanf("%s", username);
    // Check if username already exists
    if (usernameExists(filename, username)) {
        printf("Username already exists. Please try another.\n");
        printf("Redirecting Back..");
        wait();
        createAccount();
    }
    
    printf("Enter Password: ");
    scanf("%s", password);
    if (isValidPassword(password)) {
        appendUserData(filename, username, password);
        load();
        printf("\nAccount created successfully!\n\n");
        wait();
        Welcome();
    } else {
        printf("Invalid password. \nPlease ensure it has at least 8 characters, 1 uppercase letter, 1 special character, and 1 numeric value.\n");
    }
    // Append user data to the CSV file
    
    authentication();
}

void authentication() {
    int choice;
    printf("1 - Login\t\t");
    printf("2 - Create New Account \t\t");
    printf("3 - Exit\n");
    choice = getUserInput();
    if (choice == 1) {
        login();
    } else if (choice == 2) {
        createAccount();
    } else if (choice == 3) {
        printf("Exiting...\n");
        exit(0);
    } else {
        printf("Invalid choice. Please try again.\n");
        authentication();
    }
}

void Welcome()
{
    clearScreen();
    printf("--------------------------------------------------\n");
    printf("--------------------------------------------------\n");
    printf("             Welcome To Casino Hunter!\n");
    printf("--------------------------------------------------\n");
    printf("--------------------------------------------------\n");
    printf("\n\n");
    authentication();
};

int main() {
    clearScreen();
    Welcome();
    return 0;
}
