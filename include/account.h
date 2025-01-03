/*
* File: account.h
* Author: TouHikari
* Date: 2025-01-03
* Description: Include headfiles and function prototypes for account.c
* Version: 0.1.0
*/

#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include "../include/headfiles.h"
#include "../include/login.h"
#include "../include/localization.h"
#include "../include/output.h"
#include "../include/admin.h"
#include "../include/staff.h"
#include "../include/student.h"
#include "../include/guest.h"

#define MAX_IDENTITY 4

// Function prototypes
void chooseIdentity(void);               // For user to choose identity
void menu(void);                         // Menu page
void loginPrompt(const char *role);      // Login prompt for given role
void nameFile(char *fileName);           // Determine the file name based on identity
char getIdentityCode(const char *ident); // Get identity code
void emptyInputBuffer(void);             // Clear input buffer

#endif