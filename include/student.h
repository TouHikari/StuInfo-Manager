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

void studentsCore(void);
void studentWelcome(void);
void studentMenu(Student);
void changePwd(void);
void basicInfo(Student);
void queryScores(void);
void queryCurriculum(void);
void manageEmail(void);
void expressInfo(void);

#endif
