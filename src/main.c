/*
* File: main.c
* Author: TouHikari
* Date: 2024-12-17
* Description: Main file
* Version: 0.0.2
*/

#include "../include/main.h"

const char VERSION[] = "v0.0.2"; // VERSION

extern LocalizationEntry * _entries_;   // Declared in localization.c
extern int _entryCount_;                // Declared in localization.c
extern char identity[10];               // Declared in account.c
extern bool ifLogin;                    // Declared in account.c

int main(void)
{
#ifdef _WIN32
    // Change code page to UTF-8 on Windows
    system("CHCP 65001 && CLS");
#endif

    // Get language that user uses and output a welcome page
    welcomeCore();

    // Login and register accounts
    accountCore();

    // Shutting down
    printf("%s", local("shutting_down"));

    localizationRelease();  // Release RAM
    
    return 0;
}