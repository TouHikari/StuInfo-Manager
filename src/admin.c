/*
* File: admin.c
* Author: TouHikari
* Date: 2025-01-04
* Description: Administrator client program
* Version: 1.0.0
*/

#include "../include/admin.h"

extern LocalizationEntry * _entries_;   // Declared in localization.c
extern int _entryCount_;                // Declared in localization.c
extern User localAccount;               // Declared in login.c

// User client core program
void adminCore(void)
{
    User read;  // User is defined in login.h
    FILE *fp;   // File ptr

    // Read file
    openFile(&fp, "bin/admin.txt", "r+");
    for (int i = 0; i < localAccount.serialNum + 1; i++)
    {
        fread(&read, sizeof(User), 1, fp); // Read structure by structure
    }

    adminWelcome();

    adminMenu(read, fp);

    // Close file
    closeFile(&fp, "bin/admin.txt");
}

// Welcome admin login
void adminWelcome(void)
{
    printf(_YELLOW("****************************************\n"));
    printf(_YELLOW("\t%s%s! \n"), local("welcome"), localAccount.name);
    printf(_YELLOW("****************************************\n"));
}

// Menu page
void adminMenu(User read, FILE * fp)
{
    char input;
    char action;
    bool ifExit = false;

    do
    {
        printf("%s\n", local("choose_action"));
        printf("1 - %s\t", local("change_pwd"));
        printf("2 - %s\t", local("basic_information"));
        printf("3 - %s\n", local("add_curriculum"));
        printf("4 - %s\t", local("modify_curriculum"));
        printf("5 - %s\t", local("register_score"));
        printf("q - " _RED("%s\n"), local("exit"));
        printf(">>> ");
        scanf("%c", &action);

        while ((input = getchar()) != '\n')
            continue;

        switch (action)
        {
        case '1':
            adminChangePwd(read, fp);
            break;
        case '2':
            adminBasicInfo(localAccount);
            break;
        case '3':
            addCurriculum();
            break;
        case '4':
            modifyCurriculum();
            break;
        case '5':
            registerScore();
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
void adminChangePwd(User read, FILE * fp)
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

// Print admin's basic infomation
void adminBasicInfo(User info)
{
    printf(_YELLOW("%s%s %s:\n"), local("admin"),
           info.name, local("basic_information"));
    printf("\t%s: %ld\n", local("serial_number"), info.serialNum);
    printf("\t%s: %s\n", local("ID"), info.id);
    printf("\t%s: %s\n", local("gender"), local(info.gender));
    printf("\t%s: %d\n", local("session"), info.session);
    printf("\n");
}

// Add curriculum for students
void addCurriculum(void)
{
    char studentId[MAX_ID];
    int term;
    User student;
    FILE *fp;
    bool found = false;
    bool ifError = false;
    char input;
    int tryCount = 1;

    openFile(&fp, "bin/student.txt", "r+");
    fread(&student, sizeof(User), 1, fp); // Read structure by structure

    printf("%s\n", local("input_id_add_curriculum"));
    printf(">>> ");
    gets(studentId);
    tryCount = 1; // Initialize error attempt counter
    do
    {
        if (!strcmp(studentId, student.id)) // Found the ID in the first time
        {
            break;
        }
        else
        {
            if (!feof(fp)) // Keep finding until EOF
            {
                fread(&student, sizeof(User), 1, fp);
            }
            else
            {
                rewind(fp); // Reset file ptr to the beginning
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
                gets(studentId);
                tryCount++;
            }
        }
    } while (1);

    // Enter course information
    struct Curriculum newCurriculum;
    printf("%s\n", local("input_course_name"));
    printf(">>> ");
    gets(newCurriculum.courseCode);

    printf("%s\n", local("input_class_code"));
    printf(">>> ");
    scanf("%d", &newCurriculum.classCode);
    while ((input = getchar()) != '\n')
        continue;

    char courseEnded;
    printf("%s\n", local("input_if_ended"));
    printf("y - %s\t\tn - %s\n", local("yes"), local("no"));
    printf(">>> ");
    scanf("%d", &newCurriculum.ifEnded);
    scanf("%c", &courseEnded);
    while ((input = getchar()) != '\n')
        continue;
    do
    {
        switch (courseEnded)
        {
        case 'y': // Yes
            ifError = false;
            newCurriculum.ifEnded = true;
            break;
        case 'n': // No
            ifError = false;
            newCurriculum.ifEnded = false;
            break;
        default: // Illegal input
            ifError = true;
            printf(_RED("%s\n"), local("illegal"));
            printf("%s\n", local("re_input_if_ended"));
            printf("y - %s\t\t", local("yes"));
            printf("n - %s\n", local("no"));
            printf(">>> ");
            scanf("%c", &courseEnded);
            while ((input = getchar()) != '\n')
                continue;
            break;
        }
    } while (ifError);

    printf("%s\n", local("input_term"));
    printf(">>> ");
    scanf("%d", &term);
    while ((input = getchar()) != '\n')
        continue;
    do
    {
        if (term > 0 && term <= MAX_TERM)
        {
            ifError = false;
        }
        else
        {
            ifError = true;
            printf(_RED("%s\n"), local("illegal"));
            printf("%s\n", local("re_input_term"));
            printf(">>> ");
            scanf("%d", &term);
            while ((input = getchar()) != '\n')
                continue;
        }
    } while (ifError);

    // Add the new course to the student's curriculum
    for (int i = 0; i < MAX_LESSON; i++)
    {
        // Find an empty position
        if (strcmp(student.curriculums[term - 1][i].courseCode, "") == 0)
        {
            student.curriculums[term - 1][i] = newCurriculum;
            break;
        }
    }

    // Save modifications
    long long position = (ftell(fp) / sizeof(User) - 1) * sizeof(User);
    fseek(fp, position, SEEK_SET); // Move to the student's data location
    fwrite(&student, sizeof(User), 1, fp);

    printf(_GREEN("%s\n"), local("add_course_succeeded"));

    // Ask if want to continue
    char choice;
    printf("%s\n", local("input_if_continue_add_courses"));
    printf("y - %s\t\tn - %s\n", local("yes"), local("no"));
    printf(">>> ");
    scanf("%c", &choice);
    while ((input = getchar()) != '\n')
        continue;
    do
    {
        switch (choice)
        {
        case 'y': // Yes
            ifError = false;
            addCurriculum();
            break;
        case 'n': // No
            ifError = false;
            break;
        default: // Illegal input
            ifError = true;
            printf(_RED("%s\n"), local("illegal"));
            printf("%s\n", local("re_input_if_continue"));
            printf("y - %s\t\t", local("yes"));
            printf("n - %s\n", local("no"));
            printf(">>> ");
            scanf("%c", &choice);
            while ((input = getchar()) != '\n')
                continue;
            break;
        }
    } while (ifError);

    closeFile(&fp, "bin/student.txt");
}

// Modify curriculum for students
void modifyCurriculum(void)
{
    char studentId[MAX_ID];
    char courseCode[MAX_COURSE_CODE];
    User student;
    FILE *fp;
    char input;
    int tryCount;
    int term;
    bool ifError = false;

    openFile(&fp, "bin/student.txt", "r+");
    fread(&student, sizeof(User), 1, fp); // Read structure by structure

    printf("%s\n", local("input_id_modify_curriculum"));
    printf(">>> ");
    gets(studentId);
    tryCount = 1; // Initialize error attempt counter
    do
    {
        if (!strcmp(studentId, student.id)) // Found the ID in the first time
        {
            break;
        }
        else
        {
            if (!feof(fp)) // Keep finding until EOF
            {
                fread(&student, sizeof(User), 1, fp);
            }
            else
            {
                rewind(fp); // Reset file ptr to the beginning
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
                gets(studentId);
                tryCount++;
            }
        }
    } while (1);

    printf("%s\n", local("input_term"));
    printf(">>> ");
    scanf("%d", &term);
    while ((input = getchar()) != '\n')
        continue;
    do
    {
        if (term > 0 && term <= MAX_TERM)
        {
            ifError = false;
        }
        else
        {
            ifError = true;
            printf(_RED("%s\n"), local("illegal"));
            printf("%s\n", local("re_input_term"));
            printf(">>> ");
            scanf("%d", &term);
            while ((input = getchar()) != '\n')
                continue;
        }
    } while (ifError);


    // Search for courses
    bool ifFoundCurriculum = false;
    tryCount = 1;
    do
    {
        if (tryCount >= MAX_TRY_COUNT) // Try how many times exit
        {
            printf(_RED("%s (%d)\n"),
                    local("over_tries"), MAX_TRY_COUNT);
            return; 
        }

        printf("%s\n", local("input_modify_course_name"));
        printf(">>> ");
        gets(courseCode);

        for (int i = 0; i < MAX_LESSON; i++)
        {
            if (strcmp(student.curriculums[term - 1][i].courseCode, courseCode) == 0)
            {
                struct Curriculum modifiedCurriculum;
                ifFoundCurriculum = true;

                printf("%s\n", local("input_new_course_name"));
                printf(">>> ");
                gets(modifiedCurriculum.courseCode);

                printf("%s\n", local("input_new_class_code"));
                printf(">>> ");
                scanf("%d", &modifiedCurriculum.classCode);
                while ((input = getchar()) != '\n')
                    continue;

                char courseEnded;
                printf("%s\n", local("input_if_ended"));
                printf("y - %s\t\tn - %s\n", local("yes"), local("no"));
                printf(">>> ");
                scanf("%d", &modifiedCurriculum.ifEnded);
                scanf("%c", &courseEnded);
                while ((input = getchar()) != '\n')
                    continue;
                do
                {
                    switch (courseEnded)
                    {
                    case 'y': // Yes
                        ifError = false;
                        modifiedCurriculum.ifEnded = true;
                        break;
                    case 'n': // No
                        ifError = false;
                        modifiedCurriculum.ifEnded = false;
                        break;
                    default: // Illegal input
                        ifError = true;
                        printf(_RED("%s\n"), local("illegal"));
                        printf("%s\n", local("re_input_if_ended"));
                        printf("y - %s\t\t", local("yes"));
                        printf("n - %s\n", local("no"));
                        printf(">>> ");
                        scanf("%c", &courseEnded);
                        while ((input = getchar()) != '\n')
                            continue;
                        break;
                    }
                } while (ifError);

                // Update course information
                student.curriculums[term - 1][i] = modifiedCurriculum;
                break;
            }
        }
        if (!ifFoundCurriculum)
        {
            printf(_RED("%s\n"), local("curriculum_no_exist"));
            tryCount++;
        }
    } while (!ifFoundCurriculum);

    // Save modifications
    long long position = (ftell(fp) / sizeof(User) - 1) * sizeof(User);
    fseek(fp, position, SEEK_SET); // Move to the student's data location
    fwrite(&student, sizeof(User), 1, fp);

    printf(_GREEN("%s\n"), local("modify_course_succeeded"));

    // Ask if want to continue
    char choice;
    printf("%s\n", local("input_if_continue_add_courses"));
    printf("y - %s\t\tn - %s\n", local("yes"), local("no"));
    printf(">>> ");
    scanf("%c", &choice);
    while ((input = getchar()) != '\n')
        continue;
    do
    {
        switch (choice)
        {
        case 'y': // Yes
            ifError = false;
            modifyCurriculum();
            break;
        case 'n': // No
            ifError = false;
            break;
        default: // Illegal input
            ifError = true;
            printf(_RED("%s\n"), local("illegal"));
            printf("%s\n", local("re_input_if_continue"));
            printf("y - %s\t\t", local("yes"));
            printf("n - %s\n", local("no"));
            printf(">>> ");
            scanf("%c", &choice);
            while ((input = getchar()) != '\n')
                continue;
            break;
        }
    } while (ifError);

    closeFile(&fp, "bin/student.txt");
}

// Register scores for students
void registerScore(void)
{
    char studentId[MAX_ID];
    char courseCode[MAX_COURSE_CODE];
    User student;
    FILE *fp;
    bool foundCourse = false;
    bool ifError = false;
    int tryCount = 1;
    char input;
    int term;

    openFile(&fp, "bin/student.txt", "r+");
    fread(&student, sizeof(User), 1, fp); // Read structure by structure

    printf("%s\n", local("input_id_regis_scores"));
    printf(">>> ");
    gets(studentId);
    tryCount = 1; // Initialize error attempt counter
    do
    {
        if (!strcmp(studentId, student.id)) // Found the ID in the first time
        {
            break;
        }
        else
        {
            if (!feof(fp)) // Keep finding until EOF
            {
                fread(&student, sizeof(User), 1, fp);
            }
            else
            {
                rewind(fp); // Reset file ptr to the beginning
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
                gets(studentId);
                tryCount++;
            }
        }
    } while (1);

    printf("%s\n", local("input_term"));
    printf(">>> ");
    scanf("%d", &term);
    while ((input = getchar()) != '\n')
        continue;
    do
    {
        if (term > 0 && term <= MAX_TERM)
        {
            ifError = false;
        }
        else
        {
            ifError = true;
            printf(_RED("%s\n"), local("illegal"));
            printf("%s\n", local("re_input_term"));
            printf(">>> ");
            scanf("%d", &term);
            while ((input = getchar()) != '\n')
                continue;
        }
    } while (ifError);

    bool ifFoundCurriculum = false;
    tryCount = 1;
    do
    {
        if (tryCount >= MAX_TRY_COUNT) // Try how many times exit
        {
            printf(_RED("%s (%d)\n"),
                    local("over_tries"), MAX_TRY_COUNT);
            return; 
        }

        printf("%s\n", local("input_regis_score_course_name"));
        printf(">>> ");
        gets(courseCode);

        for (int i = 0; i < MAX_LESSON; i++)
        {
            if (strcmp(student.curriculums[term - 1][i].courseCode,
                courseCode) == 0)
            {
                ifFoundCurriculum = true;
                foundCourse = true;

                // Enter scores
                printf("%s\n", local("input_perform_score"));
                printf(">>> ");
                scanf("%lf", &student.curriculums[term - 1][i].performScore);

                printf("%s\n", local("input_midterm_score"));
                printf(">>> ");
                scanf("%lf", &student.curriculums[term - 1][i].midtermScore);

                printf("%s\n", local("input_final_score"));
                printf(">>> ");
                scanf("%lf", &student.curriculums[term - 1][i].finalScore);

                while ((input = getchar()) != '\n')
                    continue;

                // Mark the course as ended
                student.curriculums[term - 1][i].ifEnded = true;
                break;
            }
        }
        if (!ifFoundCurriculum)
        {
            printf(_RED("%s\n"), local("curriculum_no_exist"));
            tryCount++;
        }
    } while (!ifFoundCurriculum);

    // Save modifications
    long long position = (ftell(fp) / sizeof(User) - 1) * sizeof(User);
    fseek(fp, position, SEEK_SET); // Move to the student's data location
    fwrite(&student, sizeof(User), 1, fp);

    printf(_GREEN("%s\n"), local("regis_score_succeed"));

    // Inquire whether to continue registering scores
    char choice;
    printf("%s\n", local("input_if_continue_regis_score"));
    printf("y - %s\t\tn - %s\n", local("yes"), local("no"));
    printf(">>> ");
    scanf("%c", &choice);
    while ((input = getchar()) != '\n')
        continue;
    do
    {
        switch (choice)
        {
        case 'y': // Yes
            ifError = false;
            registerScore();
            break;
        case 'n': // No
            ifError = false;
            break;
        default: // Illegal input
            ifError = true;
            printf(_RED("%s\n"), local("illegal"));
            printf("%s\n", local("re_input_if_continue"));
            printf("y - %s\t\t", local("yes"));
            printf("n - %s\n", local("no"));
            printf(">>> ");
            scanf("%c", &choice);
            while ((input = getchar()) != '\n')
                continue;
            break;
        }
    } while (ifError);

    closeFile(&fp, "bin/student.txt");
}
