#include "welcome.h"

int language;
extern const char VERSION[];

void welcome_core(void)
{
    program_info();
}

void program_info(void)
{
    char input;

    reset:
    printf("请选择语言|Please choose the language\n");
    printf("1 - 简体中文|");
    printf("2 - English\n");

    scanf("%d", &language);
    switch (language)
    {
    case 1:
        welcome_chs();
        break;
    case 2:
        welcome_eng();
        break;
    
    default:
        printf("\033[;31m输入不合法！|Invalid input!\n\033[0m");
        while ((input = getchar()) != '\n')
            continue;
        goto reset;
    }
    
    while ((input = getchar()) != '\n')
        continue;
}

void welcome_chs(void)
{
    printf("*******************************************************\n");
    printf("\t\t信息管理系统 %s\n", VERSION);
    printf("\n");
    printf("\t\t  作者：TouHikari\n");
    printf("\tGithub主页：https://github.com/TouHikari\n");
    printf("*******************************************************\n");
}

void welcome_eng(void)
{
    printf("*******************************************************\n");
    printf("\tInformation Management System %s\n", VERSION);
    printf("\n");
    printf("\t\t  Author: TouHikari\n");
    printf("\tGithub: https://github.com/TouHikari\n");
    printf("*******************************************************\n");
}