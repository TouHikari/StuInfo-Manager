/*
* File: account.c
* Author: TouHikari
* Date: 2024-12-17
* Description: Manage accounts, including menu page
* Version: 0.0.2
*/

#include "../include/account.h"

char identity[10];          // Identity of user
bool ifExit = false;        // If user wants to exit the whole program
bool ifLogin = false;       // Login state

extern LocalizationEntry * _entries_;   // Declared in localization.c
extern int _entryCount_;                // Declared in localization.c
extern char language[5];    // Declared in welcome.c

// Login and register accounts
void accountCore(void)
{
    while (!ifLogin)
    {
        // Enter only when user didn't login
        chooseIdentity();
        if (ifExit)
        {
            ifExit = false;
            return;
        }
        menu();
    }
}

// For user to choose identity
void chooseIdentity(void)
{
    char mode;
    char input;
    bool ifError = false;

    do
    {
        printf("%s\n", local("choose_identity"));
        printf("1 - " _YELLOW("%s\t"), local("admin"));
        printf("2 - " _GREEN("%s\t"), local("staff"));
        printf("3 - " _BLUE("%s\t"), local("student"));
        printf("4 - " _PURPLE("%s\n"), local("guest"));
        printf("\t\t\t\t\t\tq - " _RED("%s\n"), local("exit"));
        printf(">>> ");
        scanf("%c", &mode);

        while ((input = getchar()) != '\n')
            continue;

        switch (mode)
        {
        case '1':
            ifError = false;
            adminLogin();
            break;
        case '2':
            ifError = false;
            staffLogin();
            break;
        case '3':
            ifError = false;
            studentLogin();
            break;
        case '4':
            ifError = false;
            guestLogin();
            break;
        case 'q':
            ifError = false;
            ifExit = true;
            break;
        default:
            ifError = true;
            printf(_RED("%s\n"), local("illegal"));
            break;
        }

        if (ifExit)
        {
            return;
        }
        
    } while (ifError);
}

// Menu page
void menu(void)
{
    char input;
    char action;
    bool ifError = false;

    do
    {
        printf("%s\n", local("choose_action"));
        printf("1 - %s\t", local("login"));
        printf("2 - %s\n", local("regis"));
        printf("\t\t\t\t\t\tq - " _RED("%s\n"), local("exit"));
        printf(">>> ");
        scanf("%c", &action);

        while ((input = getchar()) != '\n')
            continue;

        switch (action)
        {
        case '1':
            ifError = false;
            login();
            break;
        case '2':
            ifError = false;
            regis();
            break;
        case 'q':
            ifError = false;
            break;
        default:
            ifError = true;
            printf(_RED("%s\n"), local("illegal"));
            break;
        }

    } while (ifError);
    printf("--------------------%s %s/%s--------------------\n\n",
            local("exit"), local("login"), local("regis"));
}

// Administrator login prompt
void adminLogin(void)
{
    strcpy(identity, "admin");
    printf("--------------------" _YELLOW("%s %s/%s") "--------------------\n",
            local("admin"), local("login"), local("regis"));
}

// Staff login prompt
void staffLogin(void)
{
    strcpy(identity, "staff");
    printf("--------------------" _GREEN("%s %s/%s") "--------------------\n",
            local("staff"), local("login"), local("regis"));
}

// Student login prompt
void studentLogin(void)
{
    strcpy(identity, "student");
    printf("--------------------" _BLUE("%s %s/%s") "--------------------\n",
            local("student"), local("login"), local("regis"));
}

// Guest login prompt
void guestLogin(void)
{
    strcpy(identity, "guest");
    printf("--------------------" _PURPLE("%s %s/%s") "--------------------\n",
            local("guest"), local("login"), local("regis"));
}