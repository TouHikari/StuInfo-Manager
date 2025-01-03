/*
* File: output.h
* Author: TouHikari
* Date: 2024-12-17
* Description: Include headfiles, macro definitions and function prototypes
*              for output.c
* Version: 1.0.0
*/

#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include "../include/localization.h"

// Color strings
#define _BLACK(string) "\033[;30m" string "\033[0m"
#define _RED(string) "\033[;31m" string "\033[0m"
#define _GREEN(string) "\033[;32m" string "\033[0m"
#define _YELLOW(string) "\033[;33m" string "\033[0m"
#define _BLUE(string) "\033[;34m" string "\033[0m"
#define _PURPLE(string) "\033[;35m" string "\033[0m"
#define _DEEP_GREEN(string) "\033[;36m" string "\033[0m"
#define _WHITE(string) "\033[;37m" string "\033[0m"

// Simplified way to localize
#define local(key) localize(key, _entries_, _entryCount_)

#endif
