/*
* File: main.h
* Author: TouHikari
* Date: 2024-12-17
* Description: Include headfiles and function prototypes for main.c
* Version: 0.0.2
*/

#ifndef _MAIN_H_
#define _MAIN_H_

#include "..\include\headfiles.h"
#include "..\include\localization.h"
#include "..\include\output.h"

void welcomeCore(void); // Get language that user wants and output a welcome page
void accountCore(void); // Login and register accounts

#endif // main.h