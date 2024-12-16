#ifndef _LOGIN_H_
#define _LOGIN_H_

#define MAX_ID 15           // Maximum of length of ID
#define MAX_PASSWORD 30     // Maximum of length of password
#define MAX_NAME 40         // Maximum of length of name

#define MAX_TRY_COUNT 5     // Maximum of tries

typedef struct User         // Structure of user data
{
    char id[MAX_ID];
    char password[MAX_PASSWORD];
    char name[MAX_NAME];
} USER;

void login(void);           // Login module
void regis(void);           // Register module
void nameFile(char []);     // Determine file name
void getPassword(char []);  // Get password in non echo mode

#endif // login.h