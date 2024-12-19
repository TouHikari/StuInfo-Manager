/*
* File: student.c
* Author: TouHikari
* Date: 2024-12-19
* Description: Student client program
* Version: 0.0.2
*/

#include "../include/student.h"

char stuFileName[MAX_ID];

extern LocalizationEntry * _entries_;   // Declared in localization.c
extern int _entryCount_;                // Declared in localization.c
extern Student localAccount;

// Student client core program
void studentsCore(void)
{
    Student read;       // Student is defined in login.h
    FILE *fp;           // File ptr
    strcpy(stuFileName, localAccount.id);    // File name

    // Read file by binary mode
    if ((fp = fopen(stuFileName, "rb")) == NULL)
    {
        // Enter when failed to read
        fprintf(stderr, _RED("%s: %s\n"),
                stuFileName, local("read_failed"));
        exit(EXIT_FAILURE);
    }
    fread(&read, sizeof(Student), 1, fp); // Read structure by structure

    studentWelcome();

    studentMenu(read);

    // Close file
    if (fclose(fp) != 0)
    {
        // Enter when failed to close
        fprintf(stderr, _RED("%s: %s\n"),
                stuFileName, local("close_failed"));
        exit(EXIT_FAILURE);
    }
}

// Welcome student login
void studentWelcome(void)
{
    printf(_BLUE("****************************************\n"));
    printf(_BLUE("\t%s%s! \n"), local("welcome"), localAccount.name);
    printf(_BLUE("****************************************\n"));
}

// Menu page
void studentMenu(Student read)
{
    char input;
    char action;
    bool ifError = false;

    do
    {
        printf("%s\n", local("choose_action"));
        printf("1 - %s\t", local("change_pwd"));
        printf("2 - %s\t", local("basic_information"));
        printf("3 - %s\n", local("query_scores"));
        printf("4 - %s\t", local("query_curriculum"));
        printf("5 - %s\t", local("manage_email"));
        printf("6 - %s\n", local("express_info"));
        printf("\t\t\t\t\t\tq - " _RED("%s\n"), local("exit"));
        printf(">>> ");
        scanf("%c", &action);

        while ((input = getchar()) != '\n')
            continue;

        switch (action)
        {
        case '1':
            ifError = false;
            changePwd();
            break;
        case '2':
            ifError = false;
            basicInfo(read);
            break;
        case '3':
            ifError = false;
            queryScores();
            break;
        case '4':
            ifError = false;
            queryCurriculum();
            break;
        case '5':
            ifError = false;
            manageEmail();
            break;
        case '6':
            ifError = false;
            expressInfo();
        case 'q':
            ifError = false;
            break;
        default:
            ifError = true;
            printf(_RED("%s\n"), local("illegal"));
            break;
        }

    } while (ifError);
}

void changePwd(void)
{
    
}

void basicInfo(Student info)
{
    printf("%s%s %s:", local("student"), info.name, local("basic_information"));
    printf("\t%s: %ld\n", local("serial_number"), info.serialNum);
    printf("\t%s: %s\n", local("student_ID"), info.id);
    
}

void queryScores(void)
{

}

void queryCurriculum(void)
{

}

void manageEmail(void)
{

}

void expressInfo(void)
{

}