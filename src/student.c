/*
* File: student.c
* Author: TouHikari
* Date: 2025-01-03
* Description: Student client program
* Version: 1.0.0
*/

#include "../include/student.h"

extern LocalizationEntry * _entries_;   // Declared in localization.c
extern int _entryCount_;                // Declared in localization.c
extern User localAccount;               // Declared in login.c

// User client core program
void studentCore(void)
{
    User read;  // User is defined in login.h
    FILE *fp;   // File ptr

    // Read file
    openFile(&fp, "bin/student.txt", "r+");
    for (int i = 0; i < localAccount.serialNum + 1; i++)
    {
        fread(&read, sizeof(User), 1, fp); // Read structure by structure
    }

    studentWelcome();

    studentMenu(read, fp);

    // Close file
    closeFile(&fp, "bin/student.txt");
}

// Welcome student login
void studentWelcome(void)
{
    printf(_BLUE("****************************************\n"));
    printf(_BLUE("\t%s%s! \n"), local("welcome"), localAccount.name);
    printf(_BLUE("****************************************\n"));
}

// Menu page
void studentMenu(User read, FILE * fp)
{
    char input;
    char action;
    bool ifExit = false;

    do
    {
        printf("%s\n", local("choose_action"));
        printf("1 - %s\t", local("change_pwd"));
        printf("2 - %s\t", local("basic_information"));
        printf("3 - %s\n", local("query_scores"));
        printf("4 - %s\t", local("query_curriculum"));
        printf("\t\tq - " _RED("%s\n"), local("exit"));
        printf(">>> ");
        scanf("%c", &action);

        while ((input = getchar()) != '\n')
            continue;

        switch (action)
        {
        case '1':
            studentChangePwd(read, fp);
            break;
        case '2':
            studentBasicInfo(localAccount);
            break;
        case '3':
            queryScores();
            break;
        case '4':
            queryCurriculum();
            break;
        case 'q':
            ifExit = true;
            break;
        default:
            printf(_RED("%s\n"), local("illegal"));
            break;
        }
    } while (!ifExit);
}

// Change password
void studentChangePwd(User read, FILE * fp)
{
    char currentPassword[MAX_PASSWORD];
    char newPassword[MAX_PASSWORD];
    char confirmPassword[MAX_PASSWORD];
    int tryCount = 1;

    // Prompt the user to enter the current password
    printf("%s\n", local("enter_current_password"));
    printf(">>> ");
    getPassword(currentPassword);

    tryCount = 1;
    do
    {
        if (!strcmp(currentPassword, localAccount.password))
        {
            break;
        }
        else
        {
            printf(_RED("%s\n"), local("pwd_incorrect"));
            if (tryCount >= MAX_TRY_COUNT)
            {
                printf(_RED("%s (%d)\n"),
                        local("over_tries"), MAX_TRY_COUNT);
                return; 
            }
            printf("%s\n", local("re_input_pwd"));
            printf(">>> ");
            getPassword(currentPassword);
            tryCount++;
        }
    } while (1);

    // Prompt the user to enter a new password
    printf("%s\n", local("enter_new_password"));
    printf(">>> ");
    getPassword(newPassword);

    tryCount = 1;
    do
	{
        // Confirm the new password
        printf("%s\n", local("confirm_pwd"));
        printf(">>> ");
        getPassword(confirmPassword);
		if (!strcmp(newPassword, confirmPassword))
		{
            break; // Passwords match
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
            getPassword(newPassword);
            tryCount++;
		}
    } while (1);

    // Update the password in the read structure
    strcpy(read.password, newPassword);

    // Move the file pointer to the position of this user
    long position = (localAccount.serialNum) * sizeof(User);

    // Move the file pointer to the specific user's position in the file
    fseek(fp, position, SEEK_SET);

    // Save the updated user data back to the file
    if (fwrite(&read, sizeof(User), 1, fp) != 1) 
    {
        printf(_RED("%s\n"), local("save_failed"));
    } 
    else 
    {
        printf(_GREEN("%s\n"), local("save_succeeded"));
    }

    printf("\n");
}

// Print student's basic infomation
void studentBasicInfo(User info)
{
    printf(_BLUE("%s%s %s:\n"), local("student"),
           info.name, local("basic_information"));
    printf("\t%s: %ld\n", local("serial_number"), info.serialNum);
    printf("\t%s: %s\n", local("student_ID"), info.id);
    printf("\t%s: %s\n", local("gender"), local(info.gender));
    printf("\t%s: %d\n", local("session"), info.session);
    printf("\t%s: %s\n", local("if_graduated"), info.ifGraduated ?
                                                local("yes") : local("no"));
    printf("\n");
}

// Print scores
void queryScores(void) 
{
    int counter = 0;

    printf(_BLUE("%s\n"), local("your_scores")); // Display the title

    for (int i = 0; i < MAX_TERM; i++) 
    {
        for (int j = 0; j < MAX_LESSON; j++) 
        {
            // Check if the course has ended
            if (localAccount.curriculums[i][j].ifEnded)
            {
                printf("%s: \n",
                       localAccount.curriculums[i][j].courseCode);
                printf("\t%s: %.2f\n\t%s: %.2f\n\t%s: %.2f\n", 
                       local("perform_score"),
                       localAccount.curriculums[i][j].performScore,
                       local("midterm_score"),
                       localAccount.curriculums[i][j].midtermScore,
                       local("final_score"),
                       localAccount.curriculums[i][j].finalScore);
                counter++;
            }
        }
    }

    if (counter == 0)
    {
        printf(_RED("%s\n"), local("no_ended_course"));
    }

    printf("\n");
}

// Print curriculum
void queryCurriculum(void) 
{
    int counter = 0;

    printf(_BLUE("%s\n"), local("your_curriculum")); // Display the title

    for (int i = 0; i < MAX_TERM; i++) 
    {
        if (strcmp(localAccount.curriculums[i][0].courseCode, ""))
        {
            printf("%s %d:\n", local("term"), i + 1);
        }
        for (int j = 0; j < MAX_LESSON; j++) 
        {
            if (strcmp(localAccount.curriculums[i][j].courseCode, ""))
            {
                printf("\t%s - %s\n",
                    localAccount.curriculums[i][j].courseCode,
                    localAccount.curriculums[i][j].ifEnded ? 
                    local("ended") : local("ongoing"));
                counter++;
            }
        }
    }

    if (counter == 0)
    {
        printf(_RED("%s\n"), local("no_course"));
    }

    printf("\n");
}