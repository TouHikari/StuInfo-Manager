#include "..\include\headfiles.h"
#include "..\include\account.h"
#include "login.c"

extern char language[5];
char identity[10];

void accountCore(void)
{
    chooseIdentity();
    menu();
}

void chooseIdentity(void)
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
        default:
            ifError = true;
            printf("\033[;31m非法输入！\n\033[0m");
            break;
        }
    } while (ifError);
}

void menu(void)
{
    char input;
    char action;
    bool ifError = false;

    do
    {
    printf("请选择操作：\n");
    printf("1 - 登录\t");
    printf("2 - 注册\n");
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
    default:
        ifError = true;
        printf("\033[;31m非法输入！\n\033[0m");
        break;
    }
    } while (ifError);
}

void adminLogin(void)
{
    strcpy(identity, "admin");
    printf("--------------------"
            "\033[;33m管理员登录/注册\033[0m"
            "--------------------\n");
}

void staffLogin(void)
{
    strcpy(identity, "staff");
    printf("--------------------"
            "\033[;32m职工登录/注册\033[0m"
            "--------------------\n");
}

void studentLogin(void)
{
    strcpy(identity, "student");
    printf("--------------------"
            "\033[;34m学生登录/注册\033[0m"
            "--------------------\n");
}

void guestLogin(void)
{
    strcpy(identity, "guest");
    printf("--------------------"
            "\033[;35m访客登录/注册\033[0m"
            "--------------------\n");
}