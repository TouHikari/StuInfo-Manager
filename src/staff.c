#include "../include/staff.h"

extern LocalizationEntry * _entries_;   // Declared in localization.c
extern int _entryCount_;                // Declared in localization.c

void staffCore(void)
{
    printf(_RED("%s\n"), local("sorry_bye"));
}
