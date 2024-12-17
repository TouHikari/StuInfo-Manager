/*
* File: main.c
* Author: TouHikari
* Date: 2024-12-17
* Description: Main file
* Version: 0.0.2
*/

#include "..\include\main.h"

const char VERSION[] = "v0.0.2"; // VERSION

extern LocalizationEntry * _entries_;   // Declared in localization.c
extern int _entryCount_;                // Declared in localization.c
extern char identity[10];               // Declared in account.c
extern bool ifLogin;                    // Declared in account.c

int main(void)
{
    // Get language that user uses and output a welcome page
    welcomeCore();

    // Login and register accounts
    accountCore();

    ifLogin = true;

    // Shutting down
    printf("%s", local("shutting_down"));
            
    localizationRelease();  // Release RAM
    
    return 0;
}