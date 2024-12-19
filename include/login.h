/*
* File: login.h
* Author: TouHikari
* Date: 2024-12-19
* Description: Include headfiles, macro definitions, and function prototypes 
*              for login.c. Include structure definitions of user.
* Version: 0.0.2
*/

#ifndef _LOGIN_H_
#define _LOGIN_H_

#include "../include/headfiles.h"
#include "../include/localization.h"
#include "../include/output.h"

#define MAX_ID 15           // Maximum of length of ID
#define MAX_PASSWORD 30     // Maximum of length of password
#define MAX_NAME 40         // Maximum of length of name
#define MAX_COURSE_CODE 50
#define MAX_STUDENT_ID 20
#define MAX_TERM 10
#define MAX_LESSON 20

#define MAX_TRY_COUNT 5     // Maximum of tries

struct Curriculum
{
    char courseCode[MAX_COURSE_CODE];
    int classCode;
    bool ifEnded;
    double performScore;
    double midtermScore;
    double finalScore;
};

typedef struct         // Structure of user data
{
    long serialNum;
    char name[MAX_NAME];
    char id[MAX_ID];
    char password[MAX_PASSWORD];
    char gender[7];
    int session;
    bool ifGraduated;
    struct Curriculum curriculums[MAX_TERM][MAX_LESSON];
} Student;

void login(void);           // Login module
void regis(void);           // Register module
void nameFile(char [], Student * in);     // Determine file name
void getPassword(char []);  // Get password in non echo mode

#endif
