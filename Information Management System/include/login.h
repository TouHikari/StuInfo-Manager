#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ID 15
#define MAX_PASSWORD 30
#define MAX_NAME 40

typedef struct User
{
    char id[MAX_ID];
    char password[MAX_PASSWORD];
    char name[MAX_NAME];
} USER;

void menu(void);
void login(void);
void regis(void);
void nameFile(void);