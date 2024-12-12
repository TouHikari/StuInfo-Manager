#include "account.h"
#include "login.c"

extern char language[5];
char identity[10];

void accountCore(void)
{
    chooseIdentity();
}

void chooseIdentity(void)
{
    int mode;
    char input;

    resetLogin:
    printf("选择身份组：\n");
    printf("1 - \033[;33m管理员登录\t\033[0m");
    printf("2 - \033[;32m职工登录\t\033[0m");
    printf("3 - \033[;34m学生登录\t\033[0m");
    printf("4 - \033[;35m访客登录\n\033[0m");
    printf(">>> ");
    scanf("%d", &mode);

    while ((input = getchar()) != '\n')
        continue;

    switch (mode)
    {
    case 1:
        strcpy(identity, "admin");
        adminLogin();
        break;
    case 2:
        strcpy(identity, "staff");
        staffLogin();
        break;
    case 3:
        strcpy(identity, "student");
        studentLogin();
        break;
    case 4:
        strcpy(identity, "guest");
        guestLogin();
        break;
    default:
        printf("\033[;31m非法输入！\n\033[0m");
        goto resetLogin;
    }
}

void adminLogin(void)
{
    printf("----------\033[;33m管理员登录\033[0m----------\n");
    menu();
}

void staffLogin(void)
{
    printf("----------\033[;32m职工登录\033[0m----------\n");
    menu();
}

void studentLogin(void)
{
    printf("----------\033[;34m学生登录\033[0m----------\n");
    menu();
}

void guestLogin(void)
{
    printf("----------\033[;35m访客登录\033[0m----------\n");
    menu();
}