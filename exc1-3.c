#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct product
{
    char name[256];
    int price;
};

void sort(struct product *arr, const int SIZE);
int getFileSize(FILE *file);

int main()
{
    FILE *file = fopen("exc1-3.txt", "r");
    if (file == NULL)
    {
        printf("Error, file was not found");
        exit(EXIT_FAILURE);
    }
    int fileSize = getFileSize(file);
    struct product *products = malloc(fileSize * sizeof(struct product));

    int i = 0;
    while (fscanf(file, "%s %d", products[i].name, &products[i].price) == 2)
    {
        fseek(file, 2, SEEK_CUR);
        printf("Name: %s; Price: %dр\n", products[i].name, products[i].price);
        i++;
    }
    fclose(file);
    file = fopen("exc1-3Output.txt", "w");
    sort(products, fileSize);
    for (int i = 0; i < fileSize; i++)
        fprintf(file, "Name: %s; Cost: %dp\n", products[i].name, products[i].price);

    fclose(file);
    free(products);
    return 0;
}

int getFileSize(FILE *file)
{
    int lineCount = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            lineCount++;
        }
    }
    lineCount--;
    fseek(file, 0, SEEK_SET);
    return lineCount;
}
void sort(struct product *arr, const int SIZE)
{
    // Sort by cost
    for (int i = 0; i < SIZE - 1; i++)
    {
        for (int j = 0; j < SIZE - i - 1; j++)
        {
            if ((arr + j)->price > (arr + j + 1)->price)
            {
                struct product temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
}