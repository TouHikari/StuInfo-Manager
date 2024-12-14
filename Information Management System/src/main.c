#include "welcome.c"
#include "account.c"

const char VERSION[] = "v0.0.1";

int main(void)
{
    welcomeCore();
    accountCore();

    printf("程序正在关闭...");
    return 0;
}