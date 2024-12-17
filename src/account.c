#include "..\include\headfiles.h"
#include "..\include\account.h"
#include "..\include\login.h"
#include "..\include\localization.h"

char identity[10];          // Identity of user
bool ifExit = false;        // If user wants to exit the whole program
bool ifLogin = false;       // Login state

extern LocalizationEntry * _entries_;   // Declared in localization.c
extern int _entryCount_;                // Declared in localization.c
extern char language[5];    // Declared in welcome.c

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

void chooseIdentity(void)   // For user to choose identity
{
    char mode;
    char input;
    bool ifError = false;

    do
    {
        printf("%s\n",
                localize("choose_identity", _entries_, _entryCount_));
        printf("1 - \033[;33m%s\t\033[0m",
                localize("admin", _entries_, _entryCount_));
        printf("2 - \033[;32m%s\t\033[0m",
                localize("staff", _entries_, _entryCount_));
        printf("3 - \033[;34m%s\t\033[0m",
                localize("student", _entries_, _entryCount_));
        printf("4 - \033[;35m%s\n\033[0m",
                localize("guest", _entries_, _entryCount_));
        printf("\t\t\t\t\t\tq - \033[;31m%s\n\033[0m",
                localize("exit", _entries_, _entryCount_));
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
            printf("\033[;31m%s\n\033[0m",
                    localize("illegal", _entries_, _entryCount_));
            break;
        }

        if (ifExit)
        {
            return;
        }
        
    } while (ifError);
}

void menu(void) // Menu page
{
    char input;
    char action;
    bool ifError = false;

    do
    {
        printf("%s\n",
                localize("choose_action", _entries_, _entryCount_));
        printf("1 - %s\t",
                localize("login", _entries_, _entryCount_));
        printf("2 - %s\n",
                localize("regis", _entries_, _entryCount_));
        printf("\t\t\t\t\t\tq - \033[;31m%s\n\033[0m",
                localize("exit", _entries_, _entryCount_));
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
            printf("\033[;31m%s\n\033[0m",
                    localize("illegal", _entries_, _entryCount_));
            break;
        }

    } while (ifError);
    printf("--------------------%s %s/%s--------------------\n\n",
            localize("exit", _entries_, _entryCount_),
            localize("login", _entries_, _entryCount_),
            localize("regis", _entries_, _entryCount_));
}

void adminLogin(void)   // Administrator login prompt
{
    strcpy(identity, "admin");
    printf("--------------------"
            "\033[;33m%s %s/%s\033[0m"
            "--------------------\n",
            localize("admin", _entries_, _entryCount_),
            localize("login", _entries_, _entryCount_),
            localize("regis", _entries_, _entryCount_));
}

void staffLogin(void)   // Staff login prompt
{
    strcpy(identity, "staff");
    printf("--------------------"
            "\033[;32m%s %s/%s\033[0m"
            "--------------------\n",
            localize("staff", _entries_, _entryCount_),
            localize("login", _entries_, _entryCount_),
            localize("regis", _entries_, _entryCount_));
}

void studentLogin(void) // Student login prompt
{
    strcpy(identity, "student");
    printf("--------------------"
            "\033[;34m%s %s/%s\033[0m"
            "--------------------\n",
            localize("student", _entries_, _entryCount_),
            localize("login", _entries_, _entryCount_),
            localize("regis", _entries_, _entryCount_));
}

void guestLogin(void)   // Guest login prompt
{
    strcpy(identity, "guest");
    printf("--------------------"
            "\033[;35m%s %s/%s\033[0m"
            "--------------------\n",
            localize("guest", _entries_, _entryCount_),
            localize("login", _entries_, _entryCount_),
            localize("regis", _entries_, _entryCount_));
}