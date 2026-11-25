#include <stdio.h>
#include <string.h>

int main()
{
    int current;
    char item[100];
    char location[100];
    char contact[100];
    char temp[300];
    int c;

    char filename[20] = "lostfound.txt";
    FILE *file = fopen(filename , "a+");
    if(file == NULL)
    {
        printf("File does not exist.");
        return 0;
    }

    while(current != 4)
    {
        printf("Enter operation enter(1)/search(2)/display(3)/exit(4): ");
        scanf("%d" , &current);

        switch (current)
        {
        case 1:
            printf("Enter Name of item: ");

            while((c = getchar()) != '\n' && c != EOF);
            fgets(item , sizeof(item) , stdin);
            item[strcspn(item , "\n")] = '\0';

            printf("Enter location found: ");

            fgets(location , sizeof(location) , stdin);
            location[strcspn(location , "\n")] = '\0';

            printf("Enter Contact ID: ");

            fgets(contact , sizeof(location) , stdin);
            contact[strcspn(contact , "\n")] = '\0';

            sprintf(temp , "%s %s %s\n" , item , location , contact);

            fprintf(file , temp);

            break;
        
        case 2:
            rewind(file);
            printf("Enter item to look for: ");

            while((c = getchar()) != '\n' && c != EOF);
            fgets(item , sizeof(item) , stdin);

            while(fgets(temp , sizeof(temp) , file) != NULL)
            {
                if(strstr(temp , item))
                {
                    printf("%s" , temp);
                    break;
                }
            }
            printf("Record not found\n");
            break;
        case 3:
            rewind(file);

            while(fgets(temp , sizeof(temp) , file) != NULL)
            {
                printf("%s" , temp);   
            }
            break;
        case 4:
            break;
        
        default:
            printf("Invalid option.");
            break;
        }
    }

    fclose(file);
}
