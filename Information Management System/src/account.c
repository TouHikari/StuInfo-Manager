#include "..\include\headfiles.h"
#include "..\include\account.h"
#include "..\include\login.h"

extern char language[5];    // Declared in welcome.c
char identity[10];          // Identity of user
bool ifExit = false;        // If user wants to exit the whole program
bool ifLogin = false;       // Login state

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
        printf("选择身份组：\n");
        printf("1 - \033[;33m管理员\t\033[0m");
        printf("2 - \033[;32m职工\t\033[0m");
        printf("3 - \033[;34m学生\t\033[0m");
        printf("4 - \033[;35m访客\n\033[0m");
        printf("\t\t\t\t\t\tq - \033[;31m退出\n\033[0m");
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
            printf("\033[;31m非法输入！\n\033[0m");
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
        printf("请选择操作：\n");
        printf("1 - 登录\t");
        printf("2 - 注册\n");
        printf("\t\t\t\t\t\tq - \033[;31m退出\n\033[0m");
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
            printf("\033[;31m非法输入！\n\033[0m");
            break;
        }

    } while (ifError);
    printf("--------------------退出登录/注册--------------------\n\n");
}

void adminLogin(void)   // Administrator login prompt
{
    strcpy(identity, "admin");
    printf("--------------------"
            "\033[;33m管理员登录/注册\033[0m"
            "--------------------\n");
}

void staffLogin(void)   // Staff login prompt
{
    strcpy(identity, "staff");
    printf("--------------------"
            "\033[;32m职工登录/注册\033[0m"
            "--------------------\n");
}

void studentLogin(void) // Student login prompt
{
    strcpy(identity, "student");
    printf("--------------------"
            "\033[;34m学生登录/注册\033[0m"
            "--------------------\n");
}

void guestLogin(void)   // Guest login prompt
{
    strcpy(identity, "guest");
    printf("--------------------"
            "\033[;35m访客登录/注册\033[0m"
            "--------------------\n");
}