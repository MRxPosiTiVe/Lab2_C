#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <malloc.h>

int main()
{

    srand(time(NULL));
    int len;
    printf("Введите длину массива: ");
    scanf("%d", &len);
    int *arr = (int *)malloc(len * sizeof(int));
    printf("Gowno_1\n");

    for (int i = 0; i < len; i++)
    {
        arr[i] = 10 + rand() % (99 - 10 + 1);
        printf("%d ", arr[i]);
    }

    FILE *file = fopen("exc1-1.txt", "w");

    if (file == NULL)
        exit(1);
    printf("\nGowno_2\n");
    for (int i = len - 1; i >= 0; i--)
    {
        fprintf(file, "%d ", arr[i]);
    }

    free(arr);
    fclose(file);

    return 0;
}