#include "..\include\main.h"

const char VERSION[] = "v0.0.1"; // VERSION

extern char identity[10];   // Declared in account.c
extern bool ifLogin;        // Declared in account.c

int main(void)
{
    // Get language that user wants and output a welcome page
    welcomeCore();

    // Login and register accounts
    accountCore();

    ifLogin = true;

    printf("程序正在关闭...");  // Shutting down
    return 0;
}