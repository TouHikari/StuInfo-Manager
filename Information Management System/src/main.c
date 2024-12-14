#include "welcome.c"
#include "account.c"

const char VERSION[] = "v0.0.1";

int main(void)
{
    welcomeCore();
    accountCore();

    return 0;
}