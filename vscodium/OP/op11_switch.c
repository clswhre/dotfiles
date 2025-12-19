#define N 30
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int completed[N];
double time_spent[N];
char efficiency[N];
int found_indexes[N];

int main() {
    int menu, length = 0;
    int lowestCompleted, hCounter, completedAverage, first    = 1;
    int param_choise, direction_choise, method_choise, sorted = 0;
    int mode_choise, search_value, found_count = 0;
    double time_used;
    srand(time(NULL));

    do {
        printf("\t\t    МЕНЮ:\n\t");
        printf("1 ┌ Ручне введення\n\t");
        printf("2 ├ Автоматичне заповнення даних\n\t");
        printf("3 ├ Виведення даних\n\t");
        printf("4 ├ Виконання розрахунків\n\t");
        printf("5 ├ Сортування\n\t");
        printf("6 ├ Пошук данних\n\t");
        printf("0 └ Вихід з програми\n>>>");
        scanf("%d", &menu);

        switch (menu) {
            case 0: {
                break;
            };
            case 1: {
                printf("Кількість учнів?");
                scanf("%d", &length);

                if (length > N) {
                    printf("Кількість учнів > 30\n\n");
                    length = 0;
                    continue;
                };

                for (int i = 0; i < length; i++) {
                    printf("\t Елемент %d\n", i);

                    // completed [i]
                    printf("Виконано завдань: \t");
                    scanf("%d", &completed[i]);
                    if (completed[i] > 20) {
                        printf("К-сть завдань > 20!\n\n");
                        break;
                    } else if (completed[i] < 0) {
                        printf("К-сть завдань < 0!\n\n");
                        break;
                    };

                    // time_spent[i]
                    printf("Витрачено часу: \t");
                    scanf("%lf", &time_spent[i]);
                    if (time_spent[i] > 60) {
                        printf("Час > 60 хвилин\n\n");
                        break;
                    };

                    // efficiency [i]
                    if (completed[i] >= 15 && time_spent[i] < 20) {
                        efficiency[i] = 'H';

                    } else if (completed[i] <= 5 || time_spent[i] > 40) {
                        efficiency[i] = 'L';

                    } else {
                        efficiency[i] = 'M';
                    };
                };
                break;
            };
            case 2: {
                printf("К-сть елементів?:\t");
                scanf("%d", &length);
                if (length > N) {
                    printf("Кількість учнів > 30!\n\n");
                    length = 0;
                    continue;
                };

                for (int i = 0; i < length; i++) {
                    time_spent[i] = 5 + rand() % 55;
                    completed[i]  = 0 + rand() % 21;

                    if (completed[i] >= 15 && time_spent[i] < 20) {
                        efficiency[i] = 'H';

                    } else if (completed[i] <= 5 || time_spent[i] > 40) {
                        efficiency[i] = 'L';

                    } else {
                        efficiency[i] = 'M';
                    };
                };
                printf("\tДані згенеровано (Пункт 3 для перегляду)\n\n");
                break;
            };
            case 3: {
                if (length == 0) {
                    printf(
                        "Немає данних! Згенеруйте або заповніть (Пункт 1 / "
                        "2)\n");
                    continue;
                } else {
                    printf("\t--- Елементів: %d ---\n", length);
                    printf("\t| Completed\t| Time Spent\t| Efficiency\n");
                    printf(
                        "----------------------------------------------------"
                        "\n");

                    for (int i = 0; i < length; i++) {
                        printf("%d\t| %d\t\t| %.2f\t\t| %c\n", i, completed[i], time_spent[i], efficiency[i]);
                    };
                    printf("\n");
                };
                break;
            };
            case 4: {
                if (length == 0) {
                    printf(
                        "Немає данних! Згенеруйте або заповніть (Пункт 1 / "
                        "2)\n\n");
                    continue;
                } else {
                    hCounter         = 0;
                    first            = 1;
                    completedAverage = 0;
                    for (int i = 0; i < length; i++) {
                        if (first) {
                            lowestCompleted = i;
                            first           = 0;
                        } else if (completed[i] < completed[lowestCompleted]) {
                            lowestCompleted = i;
                        };
                        completedAverage += completed[i];
                        if (efficiency[i] == 'H') {
                            hCounter++;
                        };
                    }
                    completedAverage = completedAverage / length;
                    printf("┌────────────────────────────────────────┐\n");
                    printf("│ Виконано завдань в середньому: %7d │\n", completedAverage);
                    printf("│ Елемент з найменшою к-стю завдань: %3d │\n", lowestCompleted);
                    printf("│ Елементів з ефективністю 'H': %8d │\n", hCounter);
                    printf("└────────────────────────────────────────┘\n");
                };
                break;
            };
            case 5: {
                if (length == 0) {
                    printf(
                        "Немає данних! Згенеруйте або заповніть (Пункт 1 / "
                        "2)\n\n");
                    continue;
                };

                printf("\tПараметр сортування\t\n");
                printf("┌-- 1 Виконано завдань (completed)\n");
                printf("└-- 2 Витрачено часу (time_spent)\n>>>");
                scanf("%d", &param_choise);
                if (param_choise < 1 || param_choise > 2) {
                    printf("Неправильний параметр!\n\n");
                    continue;
                };

                printf("\tСортування даних\t\n");
                printf("┌Алгоритм сортування\n");
                printf("├-- 1 Алгоритм Шелла\n");
                printf("└-- 2 Баблсорт\n>>>");
                scanf("%d", &method_choise);
                if (method_choise > 2 || method_choise < 1) {
                    printf("Неправильний пункт!\n\n");
                    continue;
                };

                printf("┌Напрям сортування\n");
                printf("├-- 1 Зростання\n");
                printf("└-- 2 Спадання\n>>>");
                scanf("%d", &direction_choise);
                if (direction_choise > 2 || direction_choise < 1) {
                    printf("Неправильний пункт!\n\n");
                    continue;
                };

                clock_t start, end;
                start = clock();

                if (param_choise == 1) {
                    if (method_choise == 1) {
                        printf("\n Шелл, Completed, %s\n", (direction_choise == 1) ? "Зростання" : "Спадання");
                        for (int gap = length / 2; gap > 0; gap /= 2) {
                            for (int i = gap; i < length; i += 1) {
                                int temp_completed = completed[i];
                                double temp_time   = time_spent[i];
                                char temp_eff      = efficiency[i];
                                int j;

                                if (direction_choise == 1) {  // зростання
                                    for (j = i; j >= gap && completed[j - gap] > temp_completed; j -= gap) {
                                        completed[j]  = completed[j - gap];
                                        time_spent[j] = time_spent[j - gap];
                                        efficiency[j] = efficiency[j - gap];
                                    };
                                } else {  // спадання
                                    for (j = i; j >= gap && completed[j - gap] < temp_completed; j -= gap) {
                                        completed[j]  = completed[j - gap];
                                        time_spent[j] = time_spent[j - gap];
                                        efficiency[j] = efficiency[j - gap];
                                    };
                                };
                                completed[j]  = temp_completed;
                                time_spent[j] = temp_time;
                                efficiency[j] = temp_eff;
                            };
                        };
                        sorted = 1;
                    } else {
                        printf("\nБульбашка, Completed, %s\n", (direction_choise == 1) ? "Зростання" : "Спадання");
                        int is_swapped;
                        do {
                            is_swapped = 0;
                            for (int i = 0; i < length - 1; i++) {
                                int condition = (direction_choise == 1) ? (completed[i] > completed[i + 1])
                                                                        : (completed[i] < completed[i + 1]);
                                //  direction_choise == 1 (зростання) =>
                                //  (complted[i] > completed[i + 1]) [10,6,4] ,
                                //  10 > 6
                                if (condition) {
                                    int temp_completed = completed[i];
                                    completed[i]       = completed[i + 1];
                                    completed[i + 1]   = temp_completed;

                                    double temp_time  = time_spent[i];
                                    time_spent[i]     = time_spent[i + 1];
                                    time_spent[i + 1] = temp_time;

                                    char temp_eff     = efficiency[i];
                                    efficiency[i]     = efficiency[i + 1];
                                    efficiency[i + 1] = temp_eff;

                                    is_swapped = 1;
                                };
                            };
                        } while (is_swapped);
                        sorted = 1;
                    };
                } else if (param_choise == 2) {
                    if (method_choise == 1) {
                        printf("\n Шелл, Time Spent, %s\n", (direction_choise == 1) ? "Зростання" : "Спадання");
                        for (int gap = length / 2; gap > 0; gap /= 2) {
                            for (int i = gap; i < length; i += 1) {
                                int temp_completed = completed[i];
                                double temp_time   = time_spent[i];
                                char temp_eff      = efficiency[i];
                                int j;

                                if (direction_choise == 1) {  // зростання
                                    for (j = i; j >= gap && time_spent[j - gap] > temp_time; j -= gap) {
                                        completed[j]  = completed[j - gap];
                                        time_spent[j] = time_spent[j - gap];
                                        efficiency[j] = efficiency[j - gap];
                                    };
                                } else {  // спадання
                                    for (j = i; j >= gap && time_spent[j - gap] < temp_time; j -= gap) {
                                        completed[j]  = completed[j - gap];
                                        time_spent[j] = time_spent[j - gap];
                                        efficiency[j] = efficiency[j - gap];
                                    };
                                };
                                completed[j]  = temp_completed;
                                time_spent[j] = temp_time;
                                efficiency[j] = temp_eff;
                            };
                        };
                        sorted = 1;
                    } else {
                        printf("\nБульбашка, Time Spent, %s\n", (direction_choise == 1) ? "Зростання" : "Спадання");
                        int is_swapped;
                        do {
                            is_swapped = 0;
                            for (int i = 0; i < length - 1; i++) {
                                int condition = (direction_choise == 1) ? (time_spent[i] > time_spent[i + 1])
                                                                        : (time_spent[i] < time_spent[i + 1]);
                                //  direction_choise == 1 (зростання) =>
                                //  (complted[i] > completed[i + 1]) [10,6,4] ,
                                //  10 > 6
                                if (condition) {
                                    int temp_completed = completed[i];
                                    completed[i]       = completed[i + 1];
                                    completed[i + 1]   = temp_completed;

                                    double temp_time  = time_spent[i];
                                    time_spent[i]     = time_spent[i + 1];
                                    time_spent[i + 1] = temp_time;

                                    char temp_eff     = efficiency[i];
                                    efficiency[i]     = efficiency[i + 1];
                                    efficiency[i + 1] = temp_eff;

                                    is_swapped = 1;
                                };
                            };
                        } while (is_swapped);
                        sorted = 1;
                    };
                }
                end       = clock();
                time_used = (double) (end - start) / CLOCKS_PER_SEC;
                printf("Час виконання сортування: %.6f сек\n", time_used);
                break;
            };
            case 6: {
                found_count = 0;
                if (length == 0) {
                    printf(
                        "Немає данних! Згенеруйте або заповніть (Пункт 1 / "
                        "2)\n\n");
                    continue;
                };
                if (sorted == 0) {
                    printf("Посортуйте масив перед пошуком!\n");
                    continue;
                }

                printf("\tПараметр пошуку\t\n");
                printf("┌-- 1 Виконано завдань (completed)\n");
                printf("└-- 2 Витрачено часу (time_spent)\n>>>");
                scanf("%d", &param_choise);

                printf("\nМетод(?) пошуку\t\n");
                printf("┌-- 1 Пошук за значенням\n");
                printf("├-- 2 Пошук елементів, менших за введене значення\n");
                printf("└-- 3 Пошук елементів, більших за введене значення\n>>>");
                scanf("%d", &mode_choise);

                printf("Шукане значення = ");
                scanf("%d", &search_value);

                if (param_choise == 1) {
                    switch (mode_choise) {
                        case 1: {
                            for (int i = 0; i < length; i++) {
                                if (completed[i] == search_value) {
                                    printf("Значення %d знайдено в індексі %d\n", search_value, i);
                                    found_indexes[found_count] = i;
                                    found_count++;
                                };
                            };
                            break;
                        };
                        case 2: {
                            for (int i = 0, j = 0; i < length; i++, j++) {
                                if (completed[i] < search_value) {
                                    printf("Значення < %d знайдено в індексі %d\n", search_value, i);
                                    found_indexes[found_count] = i;
                                    found_count++;
                                };
                            };
                            break;
                        };
                        case 3: {
                            for (int i = 0; i < length; i++) {
                                if (completed[i] > search_value) {
                                    printf("Значення > %d знайдено в індексі %d\n", search_value, i);
                                    found_indexes[found_count] = i;
                                    found_count++;
                                };
                            };
                            break;
                        };
                    };
                } else if (param_choise == 2) {
                    switch (mode_choise) {
                        case 1: {
                            for (int i = 0; i < length; i++) {
                                if (time_spent[i] == search_value) {
                                    printf("Значення %d знайдено в індексі %d\n", search_value, i);
                                    found_indexes[found_count] = i;
                                    found_count++;
                                };
                            };
                            break;
                        };
                        case 2: {
                            for (int i = 0; i < length; i++) {
                                if (time_spent[i] < search_value) {
                                    printf("Значення < %d знайдено в індексі %d\n", search_value, i);
                                    found_indexes[found_count] = i;
                                    found_count++;
                                };
                            };
                            break;
                        };
                        case 3: {
                            for (int i = 0; i < length; i++) {
                                if (time_spent[i] > search_value) {
                                    printf("Значення > %d знайдено в індексі %d\n", search_value, i);
                                    found_indexes[found_count] = i;
                                    found_count++;
                                };
                            };
                            break;
                        };
                    };
                };
                if (found_count) {
                    printf("\t--- Елементів: %d ---\n", found_count);
                    printf("\t| Completed\t| Time Spent\t| Efficiency\n");
                    printf(
                        "----------------------------------------------------"
                        "\n");
                    for (int i = 0; i < found_count; i++) {
                        printf("%d\t| %d\t\t| %.2f\t\t| %c\n", i, completed[found_indexes[i]],
                               time_spent[found_indexes[i]], efficiency[found_indexes[i]]);
                    };
                    printf("\n");
                } else {
                    printf("Значення не знайдено!\n");
                };
            };
        };
    } while (menu != 0);
    return 0;
}