#include "welcome.h"
#include "account.c"

char language[5];
extern const char VERSION[];

void welcomeCore(void)
{
    programInfo();
    accountCore();
}

void programInfo(void)
{
    int lang;
    char input;

    resetLang:
    printf("请选择语言|Please choose the language:\n");
    printf("1 - 简体中文\t");
    printf("2 - English\n");
    printf(">>> ");
    scanf("%d", &lang);

    while ((input = getchar()) != '\n')
        continue;

    switch (lang)
    {
    case 1:
        strcpy(language, "chs");
        welcome_chs();
        break;
    case 2:
        strcpy(language, "eng");
        welcome_eng();
        break;
    default:
        printf("\033[;31m非法输入！|Invalid input!\n\033[0m");
        goto resetLang;
    }
}

void welcome_chs(void)
{
    printf("*******************************************************\n");
    printf("                信息管理系统 %s\n", VERSION);
    printf("\n");
    printf("                  作者：TouHikari\n");
    printf("       Github主页：https://github.com/TouHikari\n");
    printf("*******************************************************\n");
}

void welcome_eng(void)
{
    printf("*******************************************************\n");
    printf("        Information Management System %s\n", VERSION);
    printf("\n");
    printf("                 Author: TouHikari\n");
    printf("        Github: https://github.com/TouHikari\n");
    printf("*******************************************************\n");
}