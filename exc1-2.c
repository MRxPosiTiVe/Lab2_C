#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

void sort(double *arr, const int SIZE);

int main()
{

    srand(time(NULL));

    int len;

    printf("Input array length here: ");
    scanf("%d", &len);

    double *array = malloc(len * sizeof(double));

    for (int i = 0; i < len; i++)
    {
        double rand_num = (0 + rand() % (1000 - 0 + 1)) / 1000.0;
        *(array + i) = rand_num;
        printf("%f ", rand_num);
    }

    FILE *file = fopen("exc1-2.txt", "w");

    if (file == NULL)
    {
        printf("Hui");
        exit(1);
    }

    sort(array, len);

    for (int i = 0; i < len; i++)
    {
        fprintf(file, "%f ", *(array + i));
    }

    return 0;
}

void sort(double *arr, const int SIZE)
{
    for (int i = 0; i < SIZE - 1; i++)
    {
        for (int j = 0; j < SIZE - i - 1; j++)
        {
            if (*(arr + j) > *(arr + j + 1))
            {
                double temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
}
