/*
* File: welcome.h
* Author: TouHikari
* Date: 2024-12-17
* Description: Include headfiles, macro definitions and
*              function prototypes for welcome.c
* Version: 0.0.2
*/

#ifndef _WELCOME_H_
#define _WELCOME_H_

#include "..\include\headfiles.h"
#include "..\include\localization.h"
#include "..\include\output.h"

void programInfo(void); // Localization and info page
void welcome_chs(void); // Simplified Chinese info page
void welcome_eng(void); // English info page

#endif // welcome.h