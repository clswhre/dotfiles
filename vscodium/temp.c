#include <stdio.h>

void lll(){}
void swap(int *a, int *b) {
    int temp = *a;
    *a       = *b;
    *b       = temp;
}

void reverse_array(int *arr, int size) {
    // 1. Вказівник на початок (просто ім'я масиву)
    int *ptr_start = arr;

    // 2. Вказівник на кінець (адреса початку + зміщення на останній індекс)
    // Пам'ятайте: арифметика вказівників враховує розмір типу int автоматично
    int *ptr_end = arr + size - 1;

    // 3. Рухаємося назустріч, поки вказівники не зустрінуться
    while (ptr_start < ptr_end) {
        // Міняємо значення місцями (розіменовуємо вказівники через *)
        swap(ptr_start, ptr_end);

        // Зсуваємо вказівники
        ptr_start++;  // Вправо
        ptr_end--;    // Вліво
    }
}

int main() {
    int data[] = {1, 2, 3, 4, 5};
    int n      = 5;

    reverse_array(data, n);

    // Вивід результату
    for (int i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }
    // Очікуваний вивід: 5 4 3 2 1

    return 0;
}
