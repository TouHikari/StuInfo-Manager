#include "login.h"

extern char identity[10];
char filename[20];

void menu(void)
{
    char input;
    int action;

    resetAction:
    printf("请选择操作：\n");
    printf("1 - 登录\t");
    printf("2 - 注册\n");
    printf(">>> ");
    scanf("%d", &action);

    while ((input = getchar()) != '\n')
        continue;

    switch (action)
    {
    case 1:
        login();
        break;
    case 2:
        regis();
        break;
    default:
        printf("\033[;31m非法输入！\n\033[0m");
        goto resetAction;
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

    printf("请输入账号。\n");
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
                printf("\033[;31m账号不存在！\033[0m\n");
                printf("请输入账号。\n");
                printf("账号/ID：\n");
                printf(">>> ");
                gets(in.id);
            }
        }
    } while (1);
    

    printf("密码：\n");
    printf(">>> ");
    gets(in.password);

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
    
}