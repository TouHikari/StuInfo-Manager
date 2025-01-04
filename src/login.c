/*
* File: login.c
* Author: TouHikari
* Date: 2024-12-19
* Description: Include fuctions for login and register
* Version: 1.0.0
*/

#include "../include/login.h"

User localAccount;

extern char filename[20];   // Declared in account.c
extern FILE * user_fp;      // Declared in account.c
extern char identity[10];   // Declared in account.c
extern bool ifLogin;        // Declared in account.c
extern LocalizationEntry * _entries_;   // Declared in localization.c
extern int _entryCount_;                // Declared in localization.c

// Login module
void Login(void)
{
    User in, read; // User is defined in login.h
    int tryCount = 1; // User's error attempt counter

    fread(&read, sizeof(User), 1, user_fp); // Read structure by structure

    // Get ID input
    printf("%s\n", local("input_ID"));
    printf(">>> ");
    gets(in.id);

    tryCount = 1; // Initialize error attempt counter
    do
    {
        if (!strcmp(in.id, read.id)) // Found the ID in the first time
        {
            break;
        }
        else
        {
            if (!feof(user_fp)) // Keep finding until EOF
            {
                fread(&read, sizeof(User), 1, user_fp);
            }
            else
            {
                rewind(user_fp); // Reset file ptr to the beginning
                // Get ID input again
                printf(_RED("%s\n"), local("account_no_exist"));
                if (tryCount >= MAX_TRY_COUNT) // Try how many times exit
                {
                    printf(_RED("%s (%d)\n"),
                            local("over_tries"), MAX_TRY_COUNT);
                    return; 
                }
                printf("%s\n", local("re_input_ID"));
                printf(">>> ");
                gets(in.id);
                tryCount++;
            }
        }
    } while (1);
    
    // Get password input
    printf("%s\n", local("input_pwd"));
    printf(">>> ");
    getPassword(in.password);

    tryCount = 1;
    do
    {
        if (!strcmp(in.password, read.password))
        {
            localAccount = read; // Store login account information separately
            break;
        }
        else
        {
            if (!feof(user_fp))
            {
                fread(&read, sizeof(User), 1, user_fp);
            }
            else
            {
                rewind(user_fp);
                printf(_RED("%s\n"), local("pwd_incorrect"));
                if (tryCount >= MAX_TRY_COUNT)
                {
                    printf(_RED("%s (%d)\n"),
                            local("over_tries"), MAX_TRY_COUNT);
                    return; 
                }
                printf("%s\n", local("re_input_pwd"));
                printf(">>> ");
                getPassword(in.password);
                tryCount++;
            }
        }
    } while (1);

    // Succeed to login
    ifLogin = true;
    printf(_GREEN("%s\n"), local("login_succeeded"));
}

// Register module
void Regis(void)
{
    FILE * fp;
    User in = { .password = "" }; // Initialize in.password
    User read;
    char passwordTemp[MAX_PASSWORD];
    int serialNum = 0;
    int tryCount = 1;

    fread(&read, sizeof(User), 1, user_fp);

    // Get ID input
    printf("%s\n", local("regis_ID"));
    printf(">>> ");
    gets(in.id);

    tryCount = 1;
    do
    {
        if (strcmp(in.id, read.id))
        {
            if (!feof(user_fp))
            {
                fread(&read, sizeof(User), 1, user_fp);
                serialNum++;
            }
            else
            {
                break;
            }
        }
        else
        {
            rewind(user_fp);
            printf(_RED("%s\n"), local("account_already_exist"));
            if (tryCount >= MAX_TRY_COUNT)
            {
                printf(_RED("%s (%d)\n"),
                        local("over_tries"), MAX_TRY_COUNT);
                return; 
            }
            printf("%s\n", local("re_regis_ID"));
            printf(">>> ");
            gets(in.id);
            tryCount++;
        }
    } while (1);

    // Save serial number
    in.serialNum = serialNum;

    // Get name input
    printf("%s\n", local("input_name"));
    printf(">>> ");
    gets(in.name);

    // Get gender
    char gender, input;
    bool ifError = false;
    printf("%s\n", local("choose_gender"));
    printf("1 - %s\t\t", local("male"));
    printf("2 - %s\n", local("female"));
    printf(">>> ");
    scanf("%c", &gender);
    while ((input = getchar()) != '\n')
        continue;
    do
    {
        switch (gender)
        {
        case '1': // Male
            ifError = false;
            strcpy(in.gender, "male");
            break;
        case '2': // Female
            ifError = false;
            strcpy(in.gender, "female");
            break;
        default: // Illegal input
            ifError = true;
            printf(_RED("%s\n"), local("illegal"));
            printf("%s\n", local("re_choose_gender"));
            printf("1 - %s\t\t", local("male"));
            printf("2 - %s\n", local("female"));
            printf(">>> ");
            scanf("%c", &gender);
            while ((input = getchar()) != '\n')
                continue;
            break;
        }
    } while (ifError);

    // Get session
    printf("%s\n", local("input_session"));
    printf(">>> ");
    scanf("%d", &in.session);
    while ((input = getchar()) != '\n')
        continue;
    while (in.session < MIN_SESSION || in.session > MAX_SESSION)
    {
        printf(_RED("%s\n"), local("illegal"));
        printf("%s\n", local("re_input_session"));
        printf(">>> ");
        scanf("%d", &in.session);
        while ((input = getchar()) != '\n')
            continue;
    }
    
    if (!strcmp(identity, "student")) // When is student registering
    {
        // Get ifGraduated
        char graduated;
        printf("%s\n", local("choose_if_graduated"));
        printf("y - %s\t\t", local("yes"));
        printf("n - %s\n", local("no"));
        printf(">>> ");
        scanf("%c", &graduated);
        while ((input = getchar()) != '\n')
            continue;
        do
        {
            switch (graduated)
            {
            case 'y': // Yes
                ifError = false;
                in.ifGraduated = true;
                break;
            case 'n': // No
                ifError = false;
                in.ifGraduated = false;
                break;
            default: // Illegal input
                ifError = true;
                printf(_RED("%s\n"), local("illegal"));
                printf("%s\n", local("re_choose_if_graduated"));
                printf("y - %s\t\t", local("yes"));
                printf("n - %s\n", local("no"));
                printf(">>> ");
                scanf("%c", &graduated);
                while ((input = getchar()) != '\n')
                    continue;
                break;
            }
        } while (ifError);
    }
    

    // Get password input
    printf("%s\n", local("input_pwd"));
    printf(">>> ");
    getPassword(in.password);
    printf("%s\n", local("confirm_pwd")); // Confirm password input
    printf(">>> ");
    getPassword(passwordTemp);

    tryCount = 1;
    do
	{
		if (!strcmp(in.password, passwordTemp))
		{
            break;
		}
		else
		{
            printf(_RED("%s\n"), local("different_pwd"));
            if (tryCount >= MAX_TRY_COUNT)
            {
                printf(_RED("%s (%d)\n"),
                        local("over_tries"), MAX_TRY_COUNT);
                return; 
            }
			printf("%s\n", local("re_input_pwd"));
            printf(">>> ");
            getPassword(in.password);
            printf("%s\n", local("confirm_pwd"));
            printf(">>> ");
            getPassword(passwordTemp);
            tryCount++;
		}
    } while (1);

    // Write all the data into file
    openFile(&fp, filename, "a");
    if (fwrite(&in, sizeof(User), 1, fp) != 1)
    {
        printf(_RED("%s\n"), local("write_error"));
        exit(EXIT_FAILURE);
    }
    else
    {
        printf(_GREEN("%s\n\n"), local("regis_success"));
    }

    // Close file
    closeFile(&fp, filename);
}

// Open file function
void openFile(FILE ** fp, char fileName[], char openWay[])
{
    if ((*fp = fopen(fileName, openWay)) == NULL)
    {
        fprintf(stderr, _RED("%s: %s\n"),
                fileName, local("read_failed"));
        exit(EXIT_FAILURE);
    }
}

// Close file function
void closeFile(FILE ** fp, char fileName[])
{
    if (fclose(*fp) != 0)
    {
        fprintf(stderr, _RED("%s: %s\n"),
                fileName, local("close_failed"));
        exit(EXIT_FAILURE);
    }
}

// Get password in non echo mode
void getPassword(char pwd[])
{
    int i = 0; // Cycle counter
    char ch;
    
    // LINUX
    #ifdef __linux__
        system("stty -echo"); // Turn off echo display

        while (i < MAX_PASSWORD - 1)
        {
            ch = getchar();

            if (ch == '\n') // Exit when get line break
            {
                break;
            }
            else if (ch == 127 || ch == '\b') // When get Delete or Backspace
            {
                if (i > 0)
                {
                    i--;
                    printf("\b \b");
                }
            }
            else // When get normal char
            {
                pwd[i++] = ch;
                printf("*");
            }
        }
        pwd[i] = '\0'; // String ends with '\0'

        system("stty echo"); // Turn on echo display
        printf("\n");
    #endif

    // WINDOWS
    #ifdef _WIN32
        #include <conio.h>
        while (i < MAX_PASSWORD)
        {
            ch = getch();

            if ('\n' == ch || '\r' == ch) // Exit when get line break
            {
                break;
            }
            else if (127 == ch || '\b' == ch) // When get Delete or Backspace
            {
                if (i > 0)
                {
                    i--;
                    printf("\b \b");
                }
            }
            else // When get normal char
            {
                pwd[i++] = ch;
                printf("*");
            }
        }
        pwd[i] = '\0'; // String ends with '\0'
        printf("\n");
    #endif
}