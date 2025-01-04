#include "../include/guest.h"

extern LocalizationEntry * _entries_;   // Declared in localization.c
extern int _entryCount_;                // Declared in localization.c

void guestCore(void)
{
    printf(_RED("%s\n"), local("sorry_bye"));
}
