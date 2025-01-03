/*
* File: student.h
* Author: TouHikari
* Date: 2024-12-19
* Description: Include headfiles and function prototypes for student.c
* Version: 0.0.2
*/

#ifndef _STUDENT_H_
#define _STUDENT_H_

#include "../include/headfiles.h"
#include "../include/localization.h"
#include "../include/output.h"
#include "../include/login.h"

// Function prototypes
void studentCore(void);     // User client core program
void studentWelcome(void);  // Welcome student login
void studentMenu(User, FILE*);     // Menu page
void changePwd(User, FILE*);       // 
void basicInfo(User);       // 
void queryScores(void);     // 
void queryCurriculum(void); // 

#endif
