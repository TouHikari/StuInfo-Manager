/*
* File: admin.h
* Author: TouHikari
* Date: 2025-01-04
* Description: Include headfiles and function prototypes for admin.c
* Version: 1.0.0
*/

#ifndef _ADMIN_H_
#define _ADMIN_H_

#include "../include/headfiles.h"
#include "../include/localization.h"
#include "../include/output.h"
#include "../include/login.h"

// Function prototypes
void adminCore(void);           // User client core program
void adminWelcome(void);        // Welcome admin login
void adminMenu(User, FILE *);   // Menu page
void adminChangePwd(User, FILE *);  // Change password
void adminBasicInfo(User);          // Print admin's basic infomation
void addCurriculum(void);       // Add curriculum for students
void modifyCurriculum(void);    // Modify curriculum for students
void registerScore(void);       // Register scores for students

#endif