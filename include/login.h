/*
* File: login.h
* Author: TouHikari
* Date: 2025-01-03
* Description: Include headfiles, macro definitions, and function prototypes 
*              for login.c. Include structure definitions of user.
* Version: 1.0.0
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
#define MIN_SESSION 1980    // Minimum of year of attendance
#define MAX_SESSION 2025    // Maximum of year of attendance

struct Curriculum
{
    char courseCode[MAX_COURSE_CODE];
    int classCode;
    bool ifEnded;
    double performScore;
    double midtermScore;
    double finalScore;
};

typedef struct // Structure of user data
{
    long serialNum;
    char name[MAX_NAME];
    char id[MAX_ID];
    char password[MAX_PASSWORD];
    char gender[7];
    int session;
    bool ifGraduated;
    struct Curriculum curriculums[MAX_TERM][MAX_LESSON];
} User;

// Function prototypes
void Login(void); // Login module
void Regis(void); // Register module
// Open file function
void openFile(FILE ** fp, char fileName[], char openWay[]);
void closeFile(FILE ** fp, char fileName[]); // Close file function
void getPassword(char []); // Get password in non echo mode

#endif
