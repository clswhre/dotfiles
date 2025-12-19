#define MAX_LEN 256
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char text[MAX_LEN], line_for_work[MAX_LEN];

char menu = 0;
char menu_and_choise() {
    printf("\n1 - Введення рядка\n");
    printf("2 - Виведення рядка\n");
    printf("3 - Обробка рядка\n");
    printf("4 - Аналіз рядка\n");
    printf("0 - Вихід\n>>>");
    if (scanf("%hhu", &menu) != 1) {
        while (getchar() != '\n');
        return -1;
    }
    while (getchar() != '\n');

    return menu;
}
void display_line() { printf("Рядок:    %s\n", text); }

void line_work(char *text) {
    // Видалити всі розділові знаки з рядка
    size_t len = strlen(text);
    int j      = 0;
    for (int i = 0; i < len; i++) {
        if (!ispunct(text[i])) {
            line_for_work[j] = text[i];
            j++;
        }
    }
    line_for_work[j] = '\0';
    printf("Результат: %s", line_for_work);
}

void line_analyze(char *text) {
    // Визначити середню довжину слова у рядку
    int word_counter = 0, lenght = 0;
    char line_for_analyze[MAX_LEN];

    strcpy(line_for_analyze, text);

    char *word = strtok(line_for_analyze, " \t\n.,!?\"():;-");

    while (word != NULL) {
        lenght += strlen(word);
        word_counter++;
        word = strtok(NULL, " \t\n.,!?\"():;-");
    }
    if (word_counter > 0) {
        float average = (float) lenght / word_counter;
        printf("Кількість слів %d\n", word_counter);
        printf("Середня довжина %.3f\n", average);
    } else {
        printf("Слів нема(\n");
    }
}

int main() {
    do {
        menu_and_choise();
        switch (menu) {
            case 1: {
                printf("Введіть рядок: ");
                fgets(text, MAX_LEN, stdin);
                size_t len       = strlen(text);
                int word_counter = 0, wo_space = 0;
                char *edited_line = strtok(text, "\t\n.,!?\"():;-");

                for (int i = 0; i < len; i++) {
                    while (edited_line != NULL) {
                        word_counter++;
                        edited_line = strtok(NULL, " \t\n.,!?\"():;-");
                    }
                }

                for (int i = 0; i < len; i++) {
                    if (!isspace(text[i])) {
                        wo_space++;
                    }
                }

                printf("-=-=-=-\nДовжина рядка: %9zu\n", strlen(text));
                printf("Кількість слів:%9d\n", word_counter);
                printf("Довжина без пробілів:%3d\n", wo_space);
            } break;
            case 2:
                if (strlen(text) != 0) {
                    display_line();
                } else {
                    printf("Рядок порожній!\n");
                }
                break;
            case 3:
                line_work(text);
                break;
            case 4:
                line_analyze(text);
                break;
            case 0:
                break;
            default:
                printf("Неправильний пункт!\n");
        }
    } while (menu != 0);

    return 0;
}