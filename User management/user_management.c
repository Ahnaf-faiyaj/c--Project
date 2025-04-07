#include <stdio.h>
#include <string.h>
#include <unistd.h>
//  #include <windows.h>
// #include <termios.h>

#define MAX_USERS 10
#define CREDENTIAN_LENGTH 30

typedef struct
{
    char username[CREDENTIAN_LENGTH];
    char password[CREDENTIAN_LENGTH];
} User;

User users[MAX_USERS];
int user_count = 0;

void Register_user();
int login_user();
void fix_fgets_input(char *);
void input_credentials(char *username, char *password);

void main()
{
    int option;
    int user_index;
    while (1)
    {
        printf("\n Welcome to User Management");
        printf("\n 1. Register");
        printf("\n 2. Login");
        printf("\n 3. Exit");
        printf("\n Select an option: ");
        scanf("%d", &option);
        getchar();

        switch (option)
        {
        case 1:
            Register_user();
            break;
        case 2:
            user_index = login_user();
            if (user_index >= 0)
            {
                printf("\nLogin successful! Welcome, %s !\n", users[user_index].username);
            }
            else
            {
                printf("\n Login failed ! Incorrect username or password.\n ");
            }
            break;
        case 3:
            printf("\nExiting Program");
            return;
            break;

        default:
            printf("\n Invalid option.Please try again.\n");
            break;
        }
    }
}

void Register_user()
{
    if (user_count == MAX_USERS)
    {
        printf("\n Maxxium %d users are supported ! No more registrstions Allowed!!!\n", MAX_USERS);
        return;
    }

    int new_index = user_count;
    printf("\nRegister a new user");
    input_credentials(users[new_index].username, users[new_index].password);
    user_count++;
    printf("\nRegistration successful!\n");
    // printf("-%s-%s-" , users[new_index].username,users[new_index].password);
}

int login_user()
{
    char username[CREDENTIAN_LENGTH];
    char password[CREDENTIAN_LENGTH];
    input_credentials(username, password);
    // printf("-%s-%s-" , username,password);

    for (int i = 0; i < user_count; i++)
    {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0)
        {
            return i;
        }
    }
    return -1;
}

void fix_fgets_input(char *string)
{
    int index = strcspn(string, "\n");
    string[index] = '\0';
}

void input_credentials(char *username, char *password)
{
    printf("\nEnter username : ");
    fgets(username, CREDENTIAN_LENGTH, stdin);
    fix_fgets_input(username);

    // printf("Enter password (masking enabled): ");
    // fflush(stdout);

    // Change terminal Properties

    // struct termios old_props, new_props;
    // tcgetattr(STDIN_FILENO, &old_props);
    // new_props = old_props;
    // new_props.c_lflag = ~(ECHO | ICANON);
    // tcsetattr(STDIN_FILENO, TCSANOW, &new_props);

    // char ch;
    // int i = 0;
    // while ((ch = getchar()) != '\n' && ch != EOF)
    // {
    //     // 127 is ASCII for DEL
    //     if (ch == '\b' || ch == 127)
    //     {
    //         if (i > 0)
    //         {
    //             i--;
    //             printf("\b \b");
    //         }
    //     }
    //     else
    //     {
    //         password[i++] = ch;
    //         printf("*");
    //     }
    // }
    // password[i] = '\0';
    // tcsetattr(STDIN_FILENO, TCSANOW, &old_props);
    printf("Enter password : ");
    fgets(password, CREDENTIAN_LENGTH, stdin);
    fix_fgets_input(password);
}
