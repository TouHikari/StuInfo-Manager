#include "..\include\headfiles.h"
#include "..\include\login.h"

extern char identity[10];
char filename[20];

void login(void)
{
    USER in, read;
    FILE *fp;

    nameFile();

    if ((fp = fopen(filename, "rb")) == NULL)
    {
        fprintf(stderr,
                "\033[;31m读取%s失败！文件不存在或无权限。\033[0m\n",
                filename);
        exit(EXIT_FAILURE);
    }

    fread(&read, sizeof(USER), 1, fp);

    printf("请输入要登录的账号。\n");
    printf("账号/ID：\n");
    printf(">>> ");
    gets(in.id);

    do
    {
        if (!strcmp(in.id, read.id))
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
                printf("\033[;31m账号不存在！如忘记账号请联系管理员！\033[0m\n");
                printf("请重新输入账号。\n");
                printf("账号/ID：\n");
                printf(">>> ");
                gets(in.id);
            }
        }
    } while (1);
    
    printf("请输入密码。\n");
    printf("密码：\n");
    printf(">>> ");
    gets(in.password);

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
                printf("\033[;31m密码错误！如忘记密码请联系管理员！\033[0m\n");
                printf("请重新输入密码。\n");
                printf("密码：\n");
                printf(">>> ");
                gets(in.password);
            }
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

void regis(void)
{
    USER in = { .password = "" };
    USER read;
    FILE *fp;
    char passwordTemp[MAX_PASSWORD];

    nameFile();

    if ((fp = fopen(filename, "rb")) == NULL)
    {
        fprintf(stderr,
                "\033[;31m读取%s失败！文件不存在或无权限。\033[0m\n",
                filename);
        exit(EXIT_FAILURE);
    }

    fread(&read, sizeof(USER), 1, fp);

    printf("请输入要注册的账号。\n");
    printf("账号/ID：\n");
    printf(">>> ");
    gets(in.id);

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
                printf("\033[;31m账号已存在！如忘记密码请联系管理员！\033[0m\n");
                printf("请重新输入要注册的账号。\n");
                printf("账号/ID：\n");
                printf(">>> ");
                gets(in.id);
        }
    } while (1);

    printf("请输入注册人姓名：\n");
    printf(">>> ");
    gets(in.name);

    printf("请输入密码：\n");
    printf(">>> ");
    getPassword(in.password);
    printf("确认密码：\n");
    printf(">>> ");
    getPassword(passwordTemp);

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
			printf("请重新输入密码：\n");
            printf(">>> ");
            getPassword(in.password);
            printf("确认密码：\n");
            printf(">>> ");
            getPassword(passwordTemp);
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

void nameFile(void)
{
    if (strcmp(identity, "admin") == 0)
    {
        strcpy(filename, "bin\\admin.dat");
    }
    if (strcmp(identity, "staff") == 0)
    {
        strcpy(filename, "bin\\staff.dat");
    }
    if (strcmp(identity, "student") == 0)
    {
        strcpy(filename, "bin\\student.dat");
    }
    if (strcmp(identity, "guest") == 0)
    {
        strcpy(filename, "bin\\guest.dat");
    }
}

void getPassword(char pwd[])
{
    int i = 0;
    char ch;

    system("stty -echo");

    while (i < MAX_PASSWORD - 1)
    {
        ch = getchar();

        if (ch == '\n')
        {
            break;
        }
        else if (ch == 127 || ch == '\b')
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            pwd[i++] = ch;
            printf("*");
        }
    }
    pwd[i] = '\0';

    system("stty echo");
    printf("\n");
}