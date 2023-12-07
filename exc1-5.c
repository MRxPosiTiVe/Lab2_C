#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>

// Объявление функции sCreateElem перед использованием
struct StackNode *sCreateElem(int data);

// Структура для представления узла стека
struct StackNode {
    int data;                // Данные узла
    struct StackNode* next;  // Ссылка на следующий узел
};

// Структура для представления стека
struct Stack {
    struct StackNode* top;    // Вершина стека
    int capacity;             // Максимальная вместимость стека
    int size;                 // Текущий размер стека
};

// Добавление элемента в стек
void sAddElem(int value, struct Stack *stack) {
    // Проверка на переполнение стека
    if (stack->size + 1 > stack->capacity) {
        perror("Stack Overflow Exception");
        exit(EXIT_FAILURE);
    }
    // Создание нового узла
    struct StackNode *newNode = sCreateElem(value);
    // Установка ссылки на предыдущий верхний узел
    newNode->next = stack->top;
    // Установка нового узла как вершины стека
    stack->top = newNode;
    // Увеличение размера стека
    stack->size++;
}

// Извлечение элемента из стека
int sPopElem(struct Stack *stack) {
    // Проверка на пустоту стека
    if (stack->top == NULL) {
        perror("Stack is empty");
        exit(EXIT_FAILURE);
    }
    // Сохранение верхнего узла
    struct StackNode* temp = stack->top;
    // Получение данных из верхнего узла
    int data = temp->data;
    // Обновление вершины стека
    stack->top = temp->next;
    // Освобождение памяти верхнего узла
    free(temp);
    // Уменьшение размера стека
    stack->size--;
    // Возвращение извлеченных данных
    return data;
}

// Получение значения верхнего элемента стека без его удаления
int sPeekElem(struct Stack *stack) {
    // Проверка на пустоту стека
    if (stack->top == NULL) {
        perror("Stack is empty");
        exit(EXIT_FAILURE);
    }
    // Возвращение данных верхнего узла
    return stack->top->data;
}

// Инициализация стека
void initStack(struct Stack *stack, int capacity) {
    // Начальные значения стека
    stack->top = NULL;
    stack->capacity = capacity;
    stack->size = 0;
}

// Создание узла стека
struct StackNode *sCreateElem(int data) {
    // Выделение памяти под новый узел
    struct StackNode* newNode = malloc(sizeof(struct StackNode));
    // Проверка успешности выделения памяти
    if (newNode == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    // Инициализация данных нового узла
    newNode->data = data;
    newNode->next = NULL;
    // Возвращение созданного узла
    return newNode;
}

// Проверка, является ли символ оператором
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Выполнение операции для двух операндов и оператора
int performOperation(char operator, int operand1, int operand2) {
    switch (operator) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            // Проверка деления на ноль
            if (operand2 == 0) {
                perror("Division by zero");
                exit(EXIT_FAILURE);
            }
            return operand1 / operand2;
        default:
            // Некорректный оператор
            perror("Invalid operator");
            exit(EXIT_FAILURE);
    }
}

// Оценка выражения в постфиксной записи
int evaluatePostfixExpression(FILE *file) {
    // Инициализация стека
    struct Stack stack;
    initStack(&stack, 100);

    char token;
    // Чтение символов из файла до конца
    while (fscanf(file, " %c", &token) != EOF) {
        if (isdigit(token)) {
            // Если символ - число, помещаем его в стек
            sAddElem(token - '0', &stack);
        } else if (isOperator(token)) {
            // Если символ - оператор, выполняем операцию
            int operand2 = sPopElem(&stack);
            int operand1 = sPopElem(&stack);
            int result = performOperation(token, operand1, operand2);
            // Результат помещаем обратно в стек
            sAddElem(result, &stack);
        } else {
            // Некорректный символ в выражении
            perror("Invalid character in input");
            exit(EXIT_FAILURE);
        }
    }

    // Проверка корректности выражения
    if (stack.size != 1) {
        perror("Invalid expression");
        exit(EXIT_FAILURE);
    }

    // Возвращение результата выражения
    return sPopElem(&stack);
}

// Главная функция
int main() {
    // Открытие файла с постфиксным выражением
    FILE *file = fopen("exc4.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Оценка постфиксного выражения и вывод результата
    int result = evaluatePostfixExpression(file);
    printf("Result: %d\n", result);

    // Закрытие файла
    fclose(file);
    return EXIT_SUCCESS;
}
