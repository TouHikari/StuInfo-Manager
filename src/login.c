/*
* File: login.c
* Author: TouHikari
* Date: 2024-12-17
* Description: Include fuctions for login and register
* Version: 0.0.2
*/

#include "..\include\login.h"

extern char identity[10];   // Declared in account.c
extern bool ifLogin;        // Declared in account.c
extern LocalizationEntry * _entries_;   // Declared in localization.c
extern int _entryCount_;                // Declared in localization.c
char filename[20];          // Store name of the file that will be used

// Login module
void login(void)
{
    USER in, read;          // USER is defined in login.h
    FILE *fp;               // File ptr
    int tryCount = 1;       // User's error attempt counter

    nameFile(filename);             // Name filename[20];

    if ((fp = fopen(filename, "rb")) == NULL) // Read file by binary mode.
    {
        // Enter when failed to read
        fprintf(stderr, _RED("%s: %s\n"), filename, local("read_failed"));
        exit(EXIT_FAILURE);
    }

    fread(&read, sizeof(USER), 1, fp); // Read structure by structure

    // Get ID input
    printf("%s\n", local("input_ID"));
    printf("%s\n", local("ID_is"));
    printf(">>> ");
    gets(in.id);

    tryCount = 1;             // Initialize error attempt counter
    do
    {
        if (!strcmp(in.id, read.id)) // Found the ID in the first time
        {
            break;
        }
        else
        {
            if (!feof(fp))  // Keep finding until EOF
            {
                fread(&read, sizeof(USER), 1, fp);
            }
            else
            {
                rewind(fp); // Reset file ptr to the beginning
                // Get ID input again
                printf(_RED("%s\n"), local("account_no_exist"));
                if (tryCount >= MAX_TRY_COUNT)  // Try how many times exit
                {
                    printf(_RED("%s (%d)\n"),
                            local("over_tries"), MAX_TRY_COUNT);
                    return;
                }
                printf("%s\n", local("re_input_ID"));
                printf("%s\n", local("ID_is"));
                printf(">>> ");
                gets(in.id);
                tryCount++;
            }
        }
    } while (1);
    
    // Get password input
    printf("%s\n", local("input_pwd"));
    printf("%s\n", local("pwd_is"));
    printf(">>> ");
    gets(in.password);

    tryCount = 1;
    do
    {
        if (!strcmp(in.password, read.password))
        {
            break;
        }
        else
        {
            if (!feof(fp))
            {
                fread(&read, sizeof(USER), 1, fp);
            }
            else
            {
                rewind(fp);
                printf(_RED("%s\n"), local("pwd_incorrect"));
                if (tryCount >= MAX_TRY_COUNT)
                {
                    printf(_RED("%s (%d)\n"),
                            local("over_tries"), MAX_TRY_COUNT);
                    return;
                }
                printf("%s\n", local("re_input_pwd"));
                printf("%s\n", local("pwd_is"));
                printf(">>> ");
                gets(in.password);
                tryCount++;
            }
        }
    } while (1);

    // Succeed to login
    ifLogin = true;
    printf(_GREEN("%s\n"), local("login_succeeded"));

    if (fclose(fp) != 0)    // Close file
    {
        // Enter when failed to close
        fprintf(stderr, _RED("%s: %s\n"), filename, local("close_failed"));
        exit(EXIT_FAILURE);
    }
}

// Register module
void regis(void)
{
    USER in = { .password = "" };   // Initialize in.password
    USER read;
    FILE *fp;
    char passwordTemp[MAX_PASSWORD];
    int tryCount = 1;

    nameFile(filename);

    if ((fp = fopen(filename, "rb")) == NULL)
    {
        fprintf(stderr, _RED("%s: %s\n"), filename, local("read_failed"));
        exit(EXIT_FAILURE);
    }

    fread(&read, sizeof(USER), 1, fp);

    // Get ID input
    printf("%s\n", local("regis_ID"));
    printf("%s\n", local("ID_is"));
    printf(">>> ");
    gets(in.id);

    tryCount = 1;
    do
    {
        if (strcmp(in.id, read.id))
        {
            if (!feof(fp))
            {
                fread(&read, sizeof(USER), 1, fp);
            }
            else
            {
                break;
            }
        }
        else
        {
            rewind(fp);
            printf(_RED("%s\n"), local("account_already_exist"));
            if (tryCount >= MAX_TRY_COUNT)
            {
                printf(_RED("%s (%d)\n"),
                        local("over_tries"), MAX_TRY_COUNT);
                return;
            }
            printf("%s\n", local("re_regis_ID"));
            printf("%s\n", local("ID_is"));
            printf(">>> ");
            gets(in.id);
            tryCount++;
        }
    } while (1);

    // Get name input
    printf("%s\n", local("input_name"));
    printf(">>> ");
    gets(in.name);

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
			if ((fp = fopen(filename, "ab")) == NULL)
            {
                fprintf(stderr, _RED("%s: %s\n"), filename, local("read_failed"));
                exit(EXIT_FAILURE);
            }
			fwrite(&in, sizeof(USER), 1, fp);
			printf(_GREEN("%s\n\n"), local("regis_success"));
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

    if (fclose(fp) != 0)
    {
        fprintf(stderr, _RED("%s: %s\n"), filename, local("close_failed"));
        exit(EXIT_FAILURE);
    }
}

// Determine file name
void nameFile(char filename[])
{
    if (strcmp(identity, "admin") == 0)
    {
        strcpy(filename, "bin/admin.dat");
    }
    if (strcmp(identity, "staff") == 0)
    {
        strcpy(filename, "bin/staff.dat");
    }
    if (strcmp(identity, "student") == 0)
    {
        strcpy(filename, "bin/student.dat");
    }
    if (strcmp(identity, "guest") == 0)
    {
        strcpy(filename, "bin/guest.dat");
    }
}

// Get password in non echo mode
void getPassword(char pwd[])
{
    int i = 0;  // Cycle counter
    char ch;

    system("stty -echo");   // Turn off echo display

    while (i < MAX_PASSWORD - 1)
    {
        ch = getchar();

        if (ch == '\n')     // Exit when get '\n'
        {
            break;
        }
        else if (ch == 127 || ch == '\b')   // When get Delete or '\b'
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else    // When get normal char
        {
            pwd[i++] = ch;
            printf("*");
        }
    }
    pwd[i] = '\0';  // String ends with '\0' 

    system("stty echo");    // Turn on echo display
    printf("\n");
}