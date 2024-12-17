#ifndef _LOCALIZATION_H_
#define _LOCALIZATION_H_

// The structure of localized resources
typedef struct
{
    const char * key;
    const char * value;
} LocalizationEntry;

// Localization startup module
void localizationLaunch(char []);
// Localization shutdown module
void localizationRelease(void);
// Load localization resource files
void loadLocalizationFile(const char *, LocalizationEntry **, int *);
// Get localized text based on keys
const char * localize(const char *, LocalizationEntry *, int);

#endif // localization.h