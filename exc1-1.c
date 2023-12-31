#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <malloc.h>

int main()
{
    // Инициализация генератора случайных чисел с использованием текущего времени
    srand(time(NULL));

    // Объявление переменной для длины массива
    int len;

    // Запрос пользователя на ввод длины массива
    printf("Введите длину массива: ");
    scanf("%d", &len);

    // Выделение динамической памяти под массив
    int *arr = (int *)malloc(len * sizeof(int));

    // Заполнение массива случайными числами и их вывод
    for (int i = 0; i < len; i++)
    {
        arr[i] = 10 + rand() % (99 - 10 + 1);
        printf("%d ", arr[i]);
    }

    // Открытие файла "exc1-1.txt" для записи
    FILE *file = fopen("exc1-1.txt", "w");

    // Проверка успешного открытия файла
    if (file == NULL)
        exit(1);

    // Запись элементов массива в обратном порядке в файл
    for (int i = len - 1; i >= 0; i--)
    {
        fprintf(file, "%d ", arr[i]);
    }

    // Освобождение выделенной памяти для массива
    free(arr);

    // Закрытие файла
    fclose(file);

    // Возвращение значения 0, что указывает на успешное завершение программы
    return 0;
}
