#include <stdio.h>
#include <string.h>

int main()
{
    char stack[50], ip[50];
    char opt[10][10][10];
    char ter[10];

    int i, j, k, n;
    int top = 0;
    int row, col;

    /* Initialize arrays */
    for (i = 0; i < 50; i++)
    {
        stack[i] = '\0';
        ip[i] = '\0';
    }

    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            opt[i][j][0] = '\0';
        }
    }

    /* Input number of terminals */
    printf("Enter the no. of terminals: ");
    scanf("%d", &n);

    /* Remove newline left by scanf */
    getchar();

    /* Input terminals */
    printf("\nEnter the terminals: ");
    fgets(ter, sizeof(ter), stdin);

    /* Remove newline */
    ter[strcspn(ter, "\n")] = '\0';

    /* Input precedence table */
    printf("\nEnter the table values:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            char value[10];

            printf("Enter the value for %c %c: ",
                   ter[i], ter[j]);

            /*
             * fgets allows the user to simply press ENTER
             * for a blank precedence relation.
             */
            fgets(value, sizeof(value), stdin);

            /* Remove newline */
            value[strcspn(value, "\n")] = '\0';

            /*
             * If user enters nothing or '-',
             * store it as an empty relation.
             */
            if (strlen(value) == 0 || strcmp(value, "-") == 0)
            {
                opt[i][j][0] = '\0';
            }
            else
            {
                strcpy(opt[i][j], value);
            }
        }
    }

    /* Display precedence table */
    printf("\nOPERATOR PRECEDENCE TABLE:\n");

    printf("\t");

    for (i = 0; i < n; i++)
    {
        printf("%c\t", ter[i]);
    }

    printf("\n");

    for (i = 0; i < n; i++)
    {
        printf("%c\t", ter[i]);

        for (j = 0; j < n; j++)
        {
            if (strcmp(opt[i][j], "accept") == 0)
            {
                printf("accept\t");
            }
            else if (opt[i][j][0] == '\0')
            {
                printf("\t");
            }
            else
            {
                printf("%c\t", opt[i][j][0]);
            }
        }

        printf("\n");
    }

    /* Initialize stack with $ */
    stack[top] = '$';

    /* Input string */
    printf("\nEnter the input string: ");
    fgets(ip, sizeof(ip), stdin);

    ip[strcspn(ip, "\n")] = '\0';

    /* Add $ at the end */
    strcat(ip, "$");

    i = 0;

    printf("\n%-25s%-25s%-25s\n",
           "STACK", "INPUT STRING", "ACTION");

    printf("%-25s%-25s%-25s\n",
           stack, ip, "");

    /* Parsing */
    while (1)
    {
        row = -1;
        col = -1;

        /*
         * Find the top-most terminal in stack.
         */
        for (k = top; k >= 0; k--)
        {
            for (j = 0; j < n; j++)
            {
                if (stack[k] == ter[j])
                {
                    row = j;
                    break;
                }
            }

            if (row != -1)
                break;
        }

        /* Find column for current input symbol */
        for (k = 0; k < n; k++)
        {
            if (ip[i] == ter[k])
            {
                col = k;
                break;
            }
        }

        /* Invalid symbol */
        if (row == -1 || col == -1)
        {
            printf("\nString is not accepted\n");
            break;
        }

        /* Accept */
        if (stack[top] == '$' && ip[i] == '$')
        {
            printf("\nString is accepted\n");
            break;
        }

        /* Shift */
        else if (opt[row][col][0] == '<' ||
                 opt[row][col][0] == '=')
        {
            stack[++top] = opt[row][col][0];
            stack[++top] = ip[i];

            printf("Shift %c", ip[i]);

            i++;
        }

        /* Reduce */
        else if (opt[row][col][0] == '>')
        {
            while (top > 0 && stack[top] != '<')
            {
                top--;
            }

            if (top > 0)
            {
                top--;
            }

            printf("Reduce");
        }

        /* Invalid relation */
        else
        {
            printf("\nString is not accepted\n");
            break;
        }

        /* Display current stack */
        printf("\n");

        for (k = 0; k <= top; k++)
        {
            printf("%c", stack[k]);
        }

        printf("\t\t\t");

        /* Display remaining input */
        for (k = i; k < (int)strlen(ip); k++)
        {
            printf("%c", ip[k]);
        }

        printf("\t\t\t");
    }

    return 0;
}

