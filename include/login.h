/*
* File: login.h
* Author: TouHikari
* Date: 2024-12-17
* Description: Include headfiles, macro definitions and
*              function prototypes for login.c
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

#define MAX_TRY_COUNT 5     // Maximum of tries

typedef struct User         // Structure of user data
{
    int identity;   // 1 - Admin, 2 - Staff, 3 - Student, 4 - guest
    char id[MAX_ID];
    char password[MAX_PASSWORD];
    char name[MAX_NAME];
} USER;

void login(void);           // Login module
void regis(void);           // Register module
void nameFile(char [], USER * in);     // Determine file name
void getPassword(char []);  // Get password in non echo mode

#endif
