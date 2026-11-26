#include <stdio.h>
#include <string.h>

struct book
{
    char bookID[50];
    char title[100];
    char author[100];
    int copies;
};

int main()
{
    int current = 0;
    int c;
    int found;
    int count;
    int i;
    struct book temp;
    char compare[50];

    char filename[20] = "books.dat";

    struct book newFile[100];

    FILE *file = fopen(filename , "r+b");

    if(file == NULL)
    {
        file = fopen(filename , "w+b");

        if(file == NULL)
        {
            printf("File could not be opened");
            return 0;
        }
    }

    while(current != 4)
    {
        printf("Enter operation add(1)/search(2)/display(3)/exit(4) : ");
        scanf("%d" , &current);

        switch(current)
        {
        case 1:
            printf("Enter BookID: ");

            while((c = getchar()) != '\n' && c != EOF);
            fgets(compare , sizeof(compare) , stdin);
            compare[strcspn(compare , "\n")] = '\0';

            found = 0;
            rewind(file);

            while(fread(&temp , sizeof(struct book) , 1 , file) == 1)
            {
                if(strcmp(temp.bookID , compare) == 0)
                {
                    found = 1;
                    break;
                }
            }

            if(found == 1)
            {
                printf("A book with this ID already exists\n");
                break;
            }

            strcpy(temp.bookID , compare);

            printf("Enter book title: ");
            fgets(temp.title , sizeof(temp.title) , stdin);
            temp.title[strcspn(temp.title , "\n")] = '\0';

            printf("Enter Author name: ");
            fgets(temp.author , sizeof(temp.author) , stdin);
            temp.author[strcspn(temp.author , "\n")] = '\0';

            printf("Enter available copies: ");
            scanf("%d" , &temp.copies);

            fseek(file , 0 , SEEK_END);
            fwrite(&temp , sizeof(struct book) , 1 , file);

            printf("Book added\n");
            break;

        case 2:
            printf("Enter BookID to look for: ");

            while((c = getchar()) != '\n' && c != EOF);
            fgets(compare , sizeof(compare) , stdin);
            compare[strcspn(compare , "\n")] = '\0';

            found = 0;
            rewind(file);

            while(fread(&temp , sizeof(struct book) , 1 , file) == 1)
            {
                if(strcmp(temp.bookID , compare) == 0)
                {
                    found = 1;
                    printf("Book found: \n%s %s %s %d\n" , temp.bookID , temp.title , temp.author , temp.copies);
                    break;
                }
            }

            if(found == 0)
            {
                printf("Book with this ID does not exist\n");
            }

            while(found == 1)
            {
                printf("\nEnter operation delete(1)/update(2)/back(3): ");
                scanf("%d" , &current);

                switch(current)
                {
                case 1:
                    // copy every other book into the array
                    count = 0;
                    rewind(file);

                    while(count < 100 && fread(&temp , sizeof(struct book) , 1 , file) == 1)
                    {
                        if(strcmp(temp.bookID , compare) != 0)
                        {
                            newFile[count] = temp;
                            count++;
                        }
                    }

                    fclose(file);
                    file = fopen(filename , "wb");

                    for(i = 0 ; i < count ; i++)
                    {
                        fwrite(&newFile[i] , sizeof(struct book) , 1 , file);
                    }

                    fclose(file);
                    file = fopen(filename , "r+b");

                    printf("Book deleted\n");
                    found = 0;
                    break;

                case 2:
                    printf("Enter new available copies: ");
                    scanf("%d" , &temp.copies);

                    fseek(file , -(long)sizeof(struct book) , SEEK_CUR);
                    fwrite(&temp , sizeof(struct book) , 1 , file);
                    fflush(file);

                    printf("Copies updated\n");
                    found = 0;
                    break;

                case 3:
                    found = 0;
                    break;

                default:
                    printf("Invalid option\n");
                    break;
                }
            }

            break;

        case 3:
            count = 0;
            rewind(file);

            while(fread(&temp , sizeof(struct book) , 1 , file) == 1)
            {
                printf("%s %s %s %d\n" , temp.bookID , temp.title , temp.author , temp.copies);
                count++;
            }

            if(count == 0)
            {
                printf("No books to display\n");
            }
            break;
        }
    }

    fclose(file);
    return 0;
}
