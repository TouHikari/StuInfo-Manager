/*
* File: localization.h
* Author: TouHikari
* Date: 2024-12-17
* Description: Include headfiles and function prototypes for localization.c
* Version: 0.0.2
*/

#ifndef _LOCALIZATION_H_
#define _LOCALIZATION_H_

#include "../include/headfiles.h"

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

#endif
