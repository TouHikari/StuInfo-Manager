/*
* File: account.h
* Author: TouHikari
* Date: 2024-12-17
* Description: Include headfiles and function prototypes for account.c
* Version: 0.0.2
*/

#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include "..\include\headfiles.h"
#include "..\include\login.h"
#include "..\include\localization.h"
#include "..\include\output.h"

void chooseIdentity(void);  // For user to choose identity
void menu(void);            // Menu page
void adminLogin(void);      // Administrator login prompt
void staffLogin(void);      // Staff login prompt
void studentLogin(void);    // Student login prompt
void guestLogin(void);      // Guest login prompt

#endif // account.h