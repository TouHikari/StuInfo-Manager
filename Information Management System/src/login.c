#include "..\include\headfiles.h"
#include "..\include\login.h"

extern char identity[10];   // Declared in account.c
extern bool ifLogin;        // Declared in account.c
char filename[20];          // Store name of the file that will be used

void login(void)    // Login module
{
    USER in, read;          // USER is defined in login.h
    FILE *fp;               // File ptr
    int tryCount = 1;       // User's error attempt counter

    nameFile(filename);             // Name filename[20];

    if ((fp = fopen(filename, "rb")) == NULL) // Read file by binary mode.
    {
        // Enter when failed to read
        fprintf(stderr,
                "\033[;31m读取%s失败！文件不存在或无权限。\033[0m\n",
                filename);
        exit(EXIT_FAILURE);
    }

    fread(&read, sizeof(USER), 1, fp); // Read structure by structure

    // Get ID input
    printf("请输入要登录的账号。\n");
    printf("账号/ID：\n");
    printf(">>> ");
    gets(in.id);

    tryCount = 1;             // Initialize error attempt counter
    do
    {
        if (!strcmp(in.id, read.id)) // Found the ID in the first time
        {
            break;
        }
        else
        {
            if (!feof(fp))  // Keep finding until EOF
            {
                fread(&read, sizeof(USER), 1, fp);
            }
            else
            {
                rewind(fp); // Reset file ptr to the beginning
                // Get ID input again
                printf("\033[;31m账号不存在！如忘记账号请联系管理员！\033[0m\n");
                if (tryCount >= MAX_TRY_COUNT)  // Try how many times exit
                {
                    printf("\033[;31m重试次数已达%d次！\033[0m\n", MAX_TRY_COUNT);
                    return;
                }
                printf("请重新输入账号。\n");
                printf("账号/ID：\n");
                printf(">>> ");
                gets(in.id);
                tryCount++;
            }
        }
    } while (1);
    
    // Get password input
    printf("请输入密码。\n");
    printf("密码：\n");
    printf(">>> ");
    gets(in.password);

    tryCount = 1;
    do
    {
        if (!strcmp(in.password, read.password))
        {
            break;
        }
        else
        {
            if (!feof(fp))
            {
                fread(&read, sizeof(USER), 1, fp);
            }
            else
            {
                rewind(fp);
                printf("\033[;31m密码错误！如忘记密码请联系管理员！\033[0m\n");
                if (tryCount >= MAX_TRY_COUNT)
                {
                    printf("\033[;31m重试次数已达%d次！\033[0m\n", MAX_TRY_COUNT);
                    return;
                }
                printf("请重新输入密码。\n");
                printf("密码：\n");
                printf(">>> ");
                gets(in.password);
                tryCount++;
            }
        }
    } while (1);

    // Succeed to login
    ifLogin = true;
    printf("\033[;32m账号登录成功！\033[0m\n");

    if (fclose(fp) != 0)    // Close file
    {
        // Enter when failed to close
        fprintf(stderr,
                "\033[;31m关闭%s失败！文件不存在或无权限。\033[0m\n",
                filename);
        exit(EXIT_FAILURE);
    }
}

void regis(void)    // Register module
{
    USER in = { .password = "" };   // Initialize in.password
    USER read;
    FILE *fp;
    char passwordTemp[MAX_PASSWORD];
    int tryCount = 1;

    nameFile(filename);

    if ((fp = fopen(filename, "rb")) == NULL)
    {
        fprintf(stderr,
                "\033[;31m读取%s失败！文件不存在或无权限。\033[0m\n",
                filename);
        exit(EXIT_FAILURE);
    }

    fread(&read, sizeof(USER), 1, fp);

    // Get ID input
    printf("请输入要注册的账号。\n");
    printf("账号/ID：\n");
    printf(">>> ");
    gets(in.id);

    tryCount = 1;
    do
    {
        if (strcmp(in.id, read.id))
        {
            if (!feof(fp))
            {
                fread(&read, sizeof(USER), 1, fp);
            }
            else
            {
                break;
            }
        }
        else
        {
            rewind(fp);
            printf("\033[;31m账号已存在！如忘记密码请联系管理员！\033[0m\n");
            if (tryCount >= MAX_TRY_COUNT)
            {
                printf("\033[;31m重试次数已达%d次！\033[0m\n", MAX_TRY_COUNT);
                return;
            }
            printf("请重新输入要注册的账号。\n");
            printf("账号/ID：\n");
            printf(">>> ");
            gets(in.id);
            tryCount++;
        }
    } while (1);

    // Get name input
    printf("请输入注册人姓名：\n");
    printf(">>> ");
    gets(in.name);

    // Get password input
    printf("请输入密码：\n");
    printf(">>> ");
    getPassword(in.password);
    printf("确认密码：\n"); // Confirm password input
    printf(">>> ");
    getPassword(passwordTemp);

    tryCount = 1;
    do
	{
		if (!strcmp(in.password, passwordTemp))
		{
			if ((fp = fopen(filename, "ab")) == NULL)
            {
                fprintf(stderr,
                        "\033[;31m读取%s失败！文件不存在或无权限。\033[0m\n",
                        filename);
                exit(EXIT_FAILURE);
            }
			fwrite(&in, sizeof(USER), 1, fp);
			printf("\033[;32m账号注册成功！\033[0m\n\n");
            break;
		}
		else
		{
            printf("\033[;31m两次密码不相同！\033[0m\n");
            if (tryCount >= MAX_TRY_COUNT)
            {
                printf("\033[;31m重试次数已达%d次！\033[0m\n", MAX_TRY_COUNT);
                return;
            }
			printf("请重新输入密码：\n");
            printf(">>> ");
            getPassword(in.password);
            printf("确认密码：\n");
            printf(">>> ");
            getPassword(passwordTemp);
            tryCount++;
		}
    } while (1);

    if (fclose(fp) != 0)
    {
        fprintf(stderr,
                "\033[;31m关闭%s失败！文件不存在或无权限。\033[0m\n",
                filename);
        exit(EXIT_FAILURE);
    }
}

void nameFile(char filename[])  // Determine file name
{
    if (strcmp(identity, "admin") == 0)
    {
        strcpy(filename, "bin/admin.dat");
    }
    if (strcmp(identity, "staff") == 0)
    {
        strcpy(filename, "bin/staff.dat");
    }
    if (strcmp(identity, "student") == 0)
    {
        strcpy(filename, "bin/student.dat");
    }
    if (strcmp(identity, "guest") == 0)
    {
        strcpy(filename, "bin/guest.dat");
    }
}

void getPassword(char pwd[])    // Get password in non echo mode
{
    int i = 0;  // Cycle counter
    char ch;

    system("stty -echo");   // Turn off echo display

    while (i < MAX_PASSWORD - 1)
    {
        ch = getchar();

        if (ch == '\n')     // Exit when get '\n'
        {
            break;
        }
        else if (ch == 127 || ch == '\b')   // When get Delete or '\b'
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else    // When get normal char
        {
            pwd[i++] = ch;
            printf("*");
        }
    }
    pwd[i] = '\0';  // String ends with '\0' 

    system("stty echo");    // Turn on echo display
    printf("\n");
}