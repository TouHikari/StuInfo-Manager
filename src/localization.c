/*
* File: localization.c
* Author: TouHikari
* Date: 2024-12-17
* Description: Include localization implementation
* Version: 0.0.2
*/

#include "..\include\localization.h"

LocalizationEntry * _entries_;
int _entryCount_;

// Localization startup module
void localizationLaunch(char lang[])
{
    // Load localized resource files
    loadLocalizationFile(lang, &_entries_, &_entryCount_);

    // // Use localization text
    // const char * helloText = localize("hello", _entries_, _entryCount_);
    // printf("%s\n", helloText); // 输出根据语言环境翻译后的文本
}

// Localization shutdown module
void localizationRelease(void)
{
    // Release resources
    for (int i = 0; i < _entryCount_; i++)
    {
        free((void *)_entries_[i].key);
        free((void *)_entries_[i].value);
    }
    free(_entries_);
}

// Load localization resource files
void loadLocalizationFile(const char * lang, LocalizationEntry ** entries,
                            int * entryCount)
{
    FILE* fp;
    char filePath[50];

    // Put together file path, such as "locales/eng/strings"
    snprintf(filePath, sizeof(filePath), "locales/%s/string.txt", lang);

    // Open localization resource file
    if ((fp = fopen(filePath, "r")) == NULL)
    {
        fprintf(stderr,
                "\033[;31mFailed to open \"locales/%s/string.txt\"\n\033[0m",
                lang);
        exit(EXIT_FAILURE);
    }

    // Read file content line by line, parse key value pairs
    char line[256];
    int count = 0;
    LocalizationEntry * localizations = NULL;

    while (fgets(line, sizeof(line), fp))
    {
        // Parse key value pairs
        char * key = strtok(line, "=");
        char * value = strtok(NULL, "=");

        if (key && value)
        {
            // Remove line breaks
            key[strcspn(key, "\n")] = '\0';
            value[strcspn(value, "\n")] = '\0';

            // Trim spaces around key and value
            while (isspace((unsigned char) *key)) key++;
            char * end = key + strlen(key) - 1;
            while (end > key && isspace((unsigned char) *end)) end--;
            end[1] = '\0';

            while (isspace((unsigned char) *value)) value++;
            end = value + strlen(value) - 1;
            while (end > value && isspace((unsigned char) *end)) end--;
            end[1] = '\0';

            // Add to the localizations array
            localizations = realloc(localizations,
                                    (count + 1) * sizeof(LocalizationEntry));
            localizations[count].key = strdup(key);
            localizations[count].value = strdup(value);
            count++;
        }
    }

    // Close localization resource file
    if (fclose(fp) != 0)
    {
        fprintf(stderr,
                "\033[;31mFailed to close localization file: %s\n\033[0m",
                lang);
        exit(EXIT_FAILURE);
    }

    // Return the results
    *entries = localizations;
    *entryCount = count;
}

// Get localized text based on keys
const char * localize(const char * key, LocalizationEntry * entries,
                        int entryCount)
{
    for (int i = 0; i < entryCount; i++)
    {
        if (strcmp(entries[i].key, key) == 0)
        {
            return entries[i].value;
        }
    }
    // If no matching translation text is found, return the original key value
    return key;
}