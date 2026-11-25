#include <stdio.h>
#include <string.h>

int main()
{
    char filename[20] = "expenses.txt";
    char description[100];
    char temp[100];
    int current = 0;
    int expense;

    FILE *file = fopen(filename , "a+");
    if(file == NULL)
    {

    }

    while(current != 2)
    {
        char temp[100];

        printf("\nEnter an operation write(1) / exit(2): ");
        scanf("%d" , &current);

        int c;

        while((c = getchar()) != '\n' && c != EOF);

        switch(current)
        {
            case 1:
                printf("Enter Expense Description: ");
                fgets(description , 100 , stdin);
                printf("Enter Expense Amount: ");
                scanf("%d" , &expense);

                description[strcspn(description , "\n")] = '\0';

                sprintf(temp , "%s : Rs. %d\n" , description , expense);

                fprintf(file , temp);
            case 2:
                break;
        
            default:
                printf("Invalid input.");
                break;
        }
    }

    rewind(file);

    while(fgets(temp , sizeof(temp) , file) != NULL)
    {
        printf("%s", temp);
    }

    fclose(file);

}