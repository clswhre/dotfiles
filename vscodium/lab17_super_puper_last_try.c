#include <ctype.h>
#define MAX_LENGH 128
#include <stddef.h>
#include <stdio.h>
#include <string.h>

char line[MAX_LENGH];

char menu_and_choice() {
    char menu;
    printf("\n1 - Введення\n");
    printf("2 - Вивід\n");
    printf("3 - Обробка\n");
    printf("4 - Аналіз\n");
    printf("0 - Вихід\n");
    if (scanf("%hhd", &menu) != 1) {
        while (getchar() != '\n');
        return -1;
    }
    while (getchar() != '\n');
    return menu;
}

void line_input() {
    printf("Введіть рядок:  ");
    fgets(line, MAX_LENGH, stdin);
    if (strlen(line) > MAX_LENGH) {
        printf("Переповнення!");
        return;
    } else {
        size_t line_lengh = strlen(line);
        if (line_lengh > 0 && line[line_lengh - 1] == '\n') {
            line[line_lengh - 1] = '\0';
            line_lengh--;
        }
        printf("Ви ввели: %s\n", line);
        printf("Довжина рядка: %zu\n", line_lengh);
    }
}

void line_output() {
    printf("Рядок: ");
    puts(line);
}

void line_change(char *line) {
    char line_copy[MAX_LENGH];
    size_t line_lengh = strlen(line);
    int j             = 0;
    for (int i = 0; i < line_lengh; i++) {
        if (!ispunct(line[i])) {
            line_copy[j] = line[i];
            j++;
        }
    }
    line_copy[j] = '\0';
    printf("РЯдок без розділових знаків:    %s\n", line_copy);
}

void line_analyze(char *line) {
    char line_copy[MAX_LENGH];
    strcpy(line_copy, line);
    size_t line_lengh = strlen(line);
    int j             = 0;
    for (int i = 0; i < line_lengh; i++) {
        if (!ispunct(line[i])) {
            line_copy[j] = line[i];
            j++;
        } else {
            line_copy[j] = ' ';
            j++;
        }
    }
    line_copy[j] = '\0';
    int words = 0, total_lenght = 0;
    char *token = strtok(line_copy, " \t\n");
    while (token != NULL) {
        size_t words_lenght = strlen(token);
        printf("%s - %zu\n", token, words_lenght);
        total_lenght += words_lenght;
        words++;

        token = strtok(NULL, " \t\n(),.");
    }
    if (words > 0) {
        int average_word_lengh = total_lenght / words;
        printf("\nСередНЯ довжина слова = %d", average_word_lengh);
    }
}

int main() {
    char menu;
    do {
        menu = menu_and_choice();
        switch (menu) {
            case 1:
                line_input();
                break;
            case 2:
                line_output();
                break;
            case 3:
                line_change(line);
                break;
            case 4:
                line_analyze(line);
                break;
            case 0:
                printf("Вихід:p\n");
                break;
            default:
                printf("Неправильний пункт!\n");
        }

    } while (menu != 0);

    return 0;
}