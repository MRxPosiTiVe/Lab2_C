#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// Структура для представления узла стека
struct StackNode {
    int data;               // Данные узла стека (значение элемента)
    struct StackNode* next; // Указатель на следующий узел в стеке
};

// Структура для представления стека
struct Stack {
    struct StackNode* top; // Указатель на верхний элемент стека
    int capacity;          // Вместимость стека (максимальное количество элементов)
    int size;               // Текущий размер стека (количество элементов)
};

// Прототипы функций для работы со стеком
void sAddElem(int value, struct Stack* stack);
int sPopElem(struct Stack* stack);
int sPeekElem(struct Stack* stack);
void initStack(struct Stack* stack, int capacity);
struct StackNode* sCreateElem(int data);

int main(void) {
    // Простой тест для структуры стека
    
    struct Stack stack;
    initStack(&stack, 10);
    sAddElem(10, &stack);
    sAddElem(13, &stack);
    sAddElem(18, &stack);

    sPeekElem(&stack);
    sPopElem(&stack);
    sAddElem(19, &stack);
    sAddElem(11, &stack);

    return 0;
}

// Функция для добавления элемента в стек
void sAddElem(int value, struct Stack *stack) {
    if (stack->size + 1 > stack->capacity) {
        perror("Stack Overflow Exception"); // Вывод сообщения об ошибке переполнения стека
        exit(EXIT_FAILURE);
    }
    struct StackNode *newNode = sCreateElem(value); // Создание нового узла стека
    newNode->next = stack->top; // Установка указателя next нового узла на текущий верхний узел
    stack->top = newNode; // Установка нового узла как верхний элемент стека
    stack->size++; // Увеличение размера стека
}

// Функция для извлечения элемента из стека
int sPopElem(struct Stack *stack) {
    if (stack->top == NULL) {
        perror("Stack is empty"); // Вывод сообщения об ошибке, если стек пуст
        exit(EXIT_FAILURE);
    }
    struct StackNode* temp = stack->top; // Временная переменная для хранения верхнего узла
    int data = temp->data; // Сохранение значения верхнего узла
    stack->top = temp->next; // Установка указателя верхнего узла на следующий узел
    free(temp); // Освобождение памяти, занятой верхним узлом
    stack->size--; // Уменьшение размера стека
    return data; // Возвращение значения верхнего узла
}

// Функция для просмотра верхнего элемента стека
int sPeekElem(struct Stack *stack) {
    if (stack->top == NULL) {
        perror("Stack is empty"); // Вывод сообщения об ошибке, если стек пуст
        exit(EXIT_FAILURE);
    }
    return stack->top->data; // Возвращение значения верхнего узла без его извлечения
}

// Функция для инициализации стека
void initStack(struct Stack *stack, int capacity) {
    stack->top = NULL; // Установка верхнего элемента стека в NULL (стек пуст)
    stack->capacity = capacity; // Установка вместимости стека
    stack->size = 0; // Начальный размер стека установлен в 0
}

// Функция для создания нового узла стека
struct StackNode *sCreateElem(int data) {
    struct StackNode* newNode = malloc(sizeof(struct StackNode)); // Выделение памяти под новый узел
    if (newNode == NULL) {
        perror("Failed to allocate memory"); // Вывод сообщения об ошибке, если не удалось выделить память
        exit(EXIT_FAILURE);
    }
    newNode->data = data; // Установка значения нового узла
    newNode->next = NULL; // Установка указателя next в NULL (новый узел становится верхним)
    return newNode; // Возвращение нового узла
}
