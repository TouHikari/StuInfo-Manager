#include "..\include\headfiles.h"
#include "..\include\welcome.h"
#include "..\include\localization.h"

char language[5];                       // Language

extern const char VERSION[];            // Declared in main.c
extern LocalizationEntry * _entries_;   // Declared in localization.c
extern int _entryCount_;                // Declared in localization.c

void welcomeCore(void)  // Welcome program
{
    programInfo();
    localizationLaunch(language);
}

void programInfo(void)  // Choose language and output info page
{
    char langCode;
    char input;
    bool ifError = false;

    do
    {
        printf("请选择语言|Please choose the language:\n");
        printf("1 - 简体中文\t");
        printf("2 - English\n");
        printf(">>> ");
        scanf("%c", &langCode);

        while ((input = getchar()) != '\n')
            continue;

        switch (langCode)
        {
        case '1':
            ifError = false;
            welcome_chs();
            break;
        case '2':
            ifError = false;
            welcome_eng();
            break;
        default:
            ifError = true;
            printf("\033[;31m非法输入！|Invalid input!\n\033[0m");
            break;
        }
    } while (ifError);
}

void welcome_chs(void)  // Simplified Chinese info page
{
    strcpy(language, "chs");
    printf("\n*******************************************************\n");
    printf("                信息管理系统 %s\n", VERSION);
    printf("\n");
    printf("                  作者：TouHikari\n");
    printf("       Github主页：https://github.com/TouHikari\n");
    printf("*******************************************************\n\n");
}

void welcome_eng(void)  // English info page
{
    strcpy(language, "eng");
    printf("\n*******************************************************\n");
    printf("        Information Management System %s\n", VERSION);
    printf("\n");
    printf("                 Author: TouHikari\n");
    printf("        Github: https://github.com/TouHikari\n");
    printf("*******************************************************\n\n");
}