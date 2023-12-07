#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// Структура, представляющая товар
struct product
{
    char name[256];
    int price;
};

// Прототип функции сортировки массива товаров по цене
void sort(struct product *arr, const int SIZE);

// Функция для определения размера файла (количество строк)
int getFileSize(FILE *file);

int main()
{
    // Открытие файла "exc1-3.txt" для чтения
    FILE *file = fopen("exc1-3.txt", "r");
    if (file == NULL)
    {
        // Вывод сообщения об ошибке, если файл не найден
        printf("Error, file was not found");
        exit(EXIT_FAILURE);
    }

    // Определение размера файла (количество строк)
    int fileSize = getFileSize(file);

    // Выделение динамической памяти под массив товаров
    struct product *products = malloc(fileSize * sizeof(struct product));

    // Заполнение массива данными из файла и их вывод
    int i = 0;
    while (fscanf(file, "%s %d", products[i].name, &products[i].price) == 2)
    {
        fseek(file, 2, SEEK_CUR);
        printf("Name: %s; Price: %dр\n", products[i].name, products[i].price);
        i++;
    }

    // Закрытие файла
    fclose(file);

    // Открытие файла "exc1-3Output.txt" для записи
    file = fopen("exc1-3Output.txt", "w");

    // Сортировка массива товаров по цене
    sort(products, fileSize);

    // Запись отсортированных товаров в файл
    for (int i = 0; i < fileSize; i++)
        fprintf(file, "Name: %s; Cost: %dp\n", products[i].name, products[i].price);

    // Закрытие файла
    fclose(file);

    // Освобождение выделенной памяти для массива товаров
    free(products);

    // Возвращение значения 0, что указывает на успешное завершение программы
    return 0;
}

// Функция для определения размера файла (количество строк)
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

// Функция сортировки массива товаров по цене (пузырьковая сортировка)
void sort(struct product *arr, const int SIZE)
{
    for (int i = 0; i < SIZE - 1; i++)
    {
        for (int j = 0; j < SIZE - i - 1; j++)
        {
            // Поменять местами товары, если их цены стоят в неправильном порядке
            if ((arr + j)->price > (arr + j + 1)->price)
            {
                struct product temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
}
