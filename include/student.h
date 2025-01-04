/*
* File: student.h
* Author: TouHikari
* Date: 2024-12-19
* Description: Include headfiles and function prototypes for student.c
* Version: 1.0.0
*/

#ifndef _STUDENT_H_
#define _STUDENT_H_

#include "../include/headfiles.h"
#include "../include/localization.h"
#include "../include/output.h"
#include "../include/login.h"

// Function prototypes
void studentCore(void);         // User client core program
void studentWelcome(void);      // Welcome student login
void studentMenu(User, FILE *); // Menu page
void studentChangePwd(User, FILE *);   // Change password
void studentBasicInfo(User);           // Print student's basic infomation
void queryScores(void);         // Print scores
void queryCurriculum(void);     // Print curriculum

#endif
