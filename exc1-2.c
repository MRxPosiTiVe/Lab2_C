#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

// Объявление прототипа функции сортировки
void sort(double *arr, const int SIZE);

int main()
{
    // Инициализация генератора случайных чисел с использованием текущего времени
    srand(time(NULL));

    // Объявление переменной для длины массива
    int len;

    // Запрос пользователя на ввод длины массива
    printf("Input array length here: ");
    scanf("%d", &len);

    // Выделение динамической памяти под массив вещественных чисел
    double *array = malloc(len * sizeof(double));

    // Заполнение массива случайными вещественными числами от 0 до 1 и их вывод
    for (int i = 0; i < len; i++)
    {
        double rand_num = (0 + rand() % (1000 - 0 + 1)) / 1000.0;
        *(array + i) = rand_num;
        printf("%f ", rand_num);
    }

    // Открытие файла "exc1-2.txt" для записи
    FILE *file = fopen("exc1-2.txt", "w");

    // Проверка успешного открытия файла
    if (file == NULL)
    {
        printf("Press F");
        exit(1);
    }

    // Вызов функции сортировки массива
    sort(array, len);

    // Запись отсортированных элементов массива в файл
    for (int i = 0; i < len; i++)
    {
        fprintf(file, "%f ", *(array + i));
    }

    // Освобождение выделенной памяти для массива
    free(array);

    // Возвращение значения 0, что указывает на успешное завершение программы
    return 0;
}

// Определение функции сортировки пузырьком для массива вещественных чисел
void sort(double *arr, const int SIZE)
{
    for (int i = 0; i < SIZE - 1; i++)
    {
        for (int j = 0; j < SIZE - i - 1; j++)
        {
            // Поменять местами элементы, если они стоят в неправильном порядке
            if (*(arr + j) > *(arr + j + 1))
            {
                double temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
}
