#include "..\include\main.h"

const char VERSION[] = "v0.0.1"; // VERSION

extern LocalizationEntry * _entries_;   // Declared in localization.c
extern int _entryCount_;                // Declared in localization.c
extern char identity[10];               // Declared in account.c
extern bool ifLogin;                    // Declared in account.c

int main(void)
{
    // Get language that user wants and output a welcome page
    welcomeCore();

    // Login and register accounts
    accountCore();

    ifLogin = true;

    // Shutting down
    printf("%s",
            localize("shutting_down", _entries_, _entryCount_));
            
    localizationRelease();  // Release RAM
    return 0;
}