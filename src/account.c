/*
* File: account.c
* Author: TouHikari
* Date: 2025-01-03
* Description: User input and output, including menu page
* Version: 1.0.0
*/

#include "../include/account.h"

char identity[10];         // Identity of the user
bool ifExit = false;       // Flag to indicate if the user wants to exit the whole program
bool ifLogin = false;      // Login state
char filename[20];         // Store the name of the file that will be used
FILE *user_fp;             // File pointer for user data

extern LocalizationEntry * _entries_;   // Declared in localization.c
extern int _entryCount_;                // Declared in localization.c
extern char language[5];                // Declared in welcome.c

// File names corresponding to each identity
const char* identityFiles[MAX_IDENTITY] = {
    "bin/admin.txt", 
    "bin/staff.txt", 
    "bin/student.txt", 
    "bin/guest.txt"
};

// Main function to manage account-related processes
void accountCore(void)
{
    while (!ifLogin) // Loop until the user is logged in
    {
        chooseIdentity(); // Prompt user to choose an identity

        if (ifExit) // Check if the user wants to exit
        {
            ifExit = false;
            return;
        }

        nameFile(filename); // Determine the filename based on identity
        
        openFile(&user_fp, filename, "r");

        menu(); // Display the menu for the user
    }

    if (fclose(user_fp) != 0) // Close the file and check for errors
    {
        fprintf(stderr, _RED("%s: %s\n"), filename, local("close_failed"));
        exit(EXIT_FAILURE);
    }

    // Enter the corresponding function of the identity group
    if (!strcmp(identity, "admin"))
    {
        adminCore();
    }
    else if (!strcmp(identity, "staff"))
    {
        staffCore();
    }
    else if (!strcmp(identity, "student"))
    {
        studentCore();
    }
    else if (!strcmp(identity, "guest"))
    {
        guestCore();
    }
}

// Function to prompt the user to choose an identity
void chooseIdentity(void)
{
    char ident; // Variable to store user input
    bool ifError; // Flag to check for input errors

    do
    {
        // Prompt for identity choice
        printf("%s\n", local("choose_identity"));
        // Display choices with corresponding colors
        printf("1 - " _YELLOW("%s\t"), local("admin"));
        printf("2 - " _GREEN("%s\t"), local("staff"));
        printf("3 - " _BLUE("%s\t"), local("student"));
        printf("4 - " _PURPLE("%s\n"), local("guest"));
        printf("\t\t\t\t\t\tq - " _RED("%s\n"), local("exit"));
        printf(">>> ");
        scanf("%c", &ident);
        emptyInputBuffer(); // Clear the input buffer

        switch (ident) // Determine action based on input
        {
        case '1':
            loginPrompt("admin"); // Prompt admin login
            break;
        case '2':
            loginPrompt("staff"); // Prompt staff login
            break;
        case '3':
            loginPrompt("student"); // Prompt student login
            break;
        case '4':
            loginPrompt("guest"); // Prompt guest login
            break;
        case 'q':
            ifExit = true;
            return; // Exit the function
        default:
            printf(_RED("%s\n"), local("illegal"));
            ifError = true;
            continue; // Continue loop for new input
        }
        ifError = false; // Reset error flag
        
    } while (ifError);
}

// Function to prompt the user to log in based on their role
void loginPrompt(const char *role)
{
    strcpy(identity, role); // Store the identity

    // Choose color according to identity and display login prompt
    if (!strcmp(role, "admin"))
    {
        printf("--------------------" _YELLOW("%s")
               "%s/%s--------------------\n",
               local(role), local("login"), local("regis"));
    }
    else if (!strcmp(role, "staff"))
    {
        printf("--------------------" _GREEN("%s")
               "%s/%s--------------------\n",
               local(role), local("login"), local("regis"));
    }
    else if (!strcmp(role, "student"))
    {
        printf("--------------------" _BLUE("%s")
               "%s/%s--------------------\n",
               local(role), local("login"), local("regis"));
    }
    else if (!strcmp(role, "guest"))
    {
        printf("--------------------" _PURPLE("%s")
               "%s/%s--------------------\n",
               local(role), local("login"), local("regis"));
    }
}

// Function to determine the filename based on identity
void nameFile(char *fileName)
{
    int index = getIdentityCode(identity) - '1';  // Convert character to index
    if (index >= 0 && index < MAX_IDENTITY)
    {
        strcpy(fileName, identityFiles[index]); // Set the filename
    }
}

// Function to display the menu for the user
void menu(void)
{
    char action; // Variable to store user action
    bool ifError; // Flag to check for input errors

    do
    {
        // Prompt for action choice
        printf("%s\n", local("choose_action"));
        printf("1 - %s\t", local("login"));
        printf("2 - %s\t", local("regis"));
        printf("\t\tq - " _RED("%s\n"), local("exit"));
        printf(">>> ");
        scanf("%c", &action);
        emptyInputBuffer(); // Clear the input buffer

        switch (action) // Determine action based on input
        {
        case '1':
            Login();
            ifError = false; // Reset error flag
            break;

        case '2':
            Regis();
            ifError = false; // Reset error flag
            break;

        case 'q':
            ifError = false; // Set exit flag
            break;

        default:
            printf(_RED("%s\n"), local("illegal"));
            ifError = true;
            break;
        }

    } while (ifError);

    // Display exit message
    printf("--------------------%s%s/%s--------------------\n\n",
           local("exit"), local("login"), local("regis"));
}

// Function to get the identity code based on the role
char getIdentityCode(const char *ident)
{
    if (strcmp(ident, "admin") == 0)
        return '1';
    if (strcmp(ident, "staff") == 0)
        return '2';
    if (strcmp(ident, "student") == 0)
        return '3';
    if (strcmp(ident, "guest") == 0)
        return '4';
    return '0'; // Default case
}

// Function to clear the input buffer to avoid unwanted characters
void emptyInputBuffer(void)
{
    char input; // Variable to store character
    while ((input = getchar()) != '\n') // Read until newline
        continue;
}