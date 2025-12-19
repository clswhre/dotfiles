#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

double **pm25   = NULL;
double **pm10   = NULL;
double **target = NULL;
char menu;
int Sensor, Meas;
bool is_pm10_filled = false, is_pm25_filled = false;

void user_input() {
    int sensor_selection;
    printf("\tВиберіть масив для ручного введення:\n\t1 - PM25\n\t2 - PM10\n>>> ");
    scanf("%d", &sensor_selection);

    if (sensor_selection == 1) {
        target         = pm25;
        is_pm25_filled = true;
        printf("Введення даних для PM25:\n");
    } else if (sensor_selection == 2) {
        target         = pm10;
        is_pm10_filled = true;
        printf("Введення даних для PM10:\n");
    } else {
        printf("Неправильний вибір!\n");
        return;
    }

    for (int i = 0; i < Sensor; i++) {
        for (int j = 0; j < Meas; j++) {
            printf("Сенсор %d, вимір %d: ", i, j);
            scanf("%lf", &target[i][j]);
        }
    }
}
void auto_fill() {
    int array_selection;
    printf("Який масив заповнити?\n");
    printf("    1 - PM25\n    2 - PM10\n    3 - Обидва\n>>> ");
    scanf("%d", &array_selection);

    if (array_selection == 1 || array_selection == 3) {
        for (int i = 0; i < Sensor; i++) {
            for (int j = 0; j < Meas; j++) {
                pm25[i][j] = 5.0 + ((double) rand() / RAND_MAX) * 296;
            }
        }
        is_pm25_filled = true;
        printf("Масив PM25 заповнено\n");
    }
    if (array_selection == 2 || array_selection == 3) {
        for (int i = 0; i < Sensor; i++) {
            for (int j = 0; j < Meas; j++) {
                pm10[i][j] = 10.0 + ((double) rand() / RAND_MAX) * 490;
            }
        }
        is_pm10_filled = true;
        printf("Масив PM10 заповнено\n");
    }
}

double **dynamic_array(int Sensor, int Meas) {
    double **array = (double **) malloc(Sensor * sizeof(double *));
    if (array == NULL) return NULL;
    for (int i = 0; i < Sensor; i++) {
        array[i] = (double *) malloc(Meas * sizeof(double));
        if (array[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(array[k]);
            };
            free(array);
            return NULL;
        }
    }
    return array;
}

double **add_row(double **array, int Sensor, int Meas) {
    double **array_added_row = (double **) realloc(array, (Sensor + 1) * sizeof(double *));

    if (array_added_row == NULL) {
        printf("Помилка перевиділення");
        return array;
    }
    array_added_row[Sensor] = (double *) malloc(Meas * sizeof(double));
    printf("Додано рядок!\n");
    u_char add_ros_sel;
    printf("Хочете заповнити рядок?\n");
    printf(" 1-ТАК\n -НІ\n>>>");
    scanf("%hhd", &add_ros_sel);
    if (add_ros_sel == 1) {
        u_char add_method_sel;
        printf("ЯК заповнити рядок?\n");
        printf(" 1-Вручну\n 2-Автоматично\n>>>");
        scanf("%hhd", &add_method_sel);
        if (add_method_sel == 1) {
            for (int i = 0; i < Meas; i++) {
                printf("Сенсор %d, вимір %d: ", Sensor, i);
                scanf("%lf", &array_added_row[Sensor][i]);
            }
        } else if (add_method_sel == 2) {
            if (array == pm25) {
                for (int i = 0; i < Meas; i++) {
                    array_added_row[Sensor][i] = 5.0 + ((double) rand() / RAND_MAX) * 296;
                }
            } else {
                for (int i = 0; i < Meas; i++) {
                    array_added_row[Sensor][i] = 10.0 + ((double) rand() / RAND_MAX) * 490;
                }
            }
        } else {
            printf("Неправильний пункт! Заповнюється нулями!\n");
            for (int i = 0; i < Meas; i++) {
                array_added_row[Sensor][i] = 0.0;
            }
        }
    }
    Sensor++;

    return array_added_row;
}

double **delete_row(double **array, int Sensor, int row_to_delete) {
    free(array[row_to_delete]);

    for (int i = row_to_delete; i < Sensor - 1; i++) {
        array[i] = array[i + 1];
    }

    double **array_deleted_row = (double **) realloc(array, (Sensor - 1) * sizeof(double *));

    if (array_deleted_row == NULL && Sensor - 1 > 0) {
        return array;
    }
    return array_deleted_row;
}

void free_array(double **array, int Sensor) {
    if (array == NULL) {
        return;
    }
    for (int i = 0; i < Sensor; i++) {
        free(array[i]);
    }
    free(array);
}

char menu_and_choise() {
    printf("\n\t\t    МЕНЮ:\n");
    printf("\t1   Ручне введення\n");
    printf("\t2   Автоматичне заповнення даних\n");
    printf("\t3   Виведення даних\n");
    printf("\t4   Статистика [Рядки]\n");
    printf("\t5   Статистика [Стовбці]\n");
    printf("\t6   Статистика [Обрахунки]\n");
    printf("\t7   Монотонність\n");
    printf("\t8   Локальні максимуми\n");
    printf("\t9   Дисперсія\n");
    printf("\t10  Додавання рядка\n");
    printf("\t11  Видалення рядка\n");
    printf("\t0   Вихід з програми\n>>> ");
    scanf(" %hhd", &menu);
    return menu;
}

void see_table() {
    int selection;
    printf("Дані якого масиву вивести?\n    1 - PM25\n    2 - PM10\n>>> ");
    scanf("%d", &selection);

    double **target = NULL;
    if (selection == 1) {
        target = pm25;
        printf("\n--- PM25 ---\n");
    } else if (selection == 2) {
        target = pm10;
        printf("\n--- PM10 ---\n");
    } else {
        printf("Неправильний вибір!\n");
        return;
    }

    printf("    |");
    for (int j = 0; j < Meas; j++) {
        printf("%6d |", j);
    }
    printf("\n");
    printf("\n");

    for (int i = 0; i < Sensor; i++) {
        printf(" %2d | ", i);
        for (int j = 0; j < Meas; j++) {
            printf("%6.1f |", target[i][j]);
        }
        printf("\n");
    }
}

void row_stats() {
    printf("\n--- Статистика по рядках ---\n");

    for (int i = 0; i < Sensor; i++) {
        double pm10Min      = pm10[i][0];
        double pm10Max      = pm10[i][0];
        double pm25Sum      = 0;
        double pm10Sum      = 0;
        int pm25LessThan150 = 0, pm25LessThan150Andpm10GreaterThan250 = 0;

        for (int j = 0; j < Meas; j++) {
            if (pm10[i][j] < pm10Min) pm10Min = pm10[i][j];
            if (pm10[i][j] > pm10Max) pm10Max = pm10[i][j];

            pm25Sum += pm25[i][j];
            pm10Sum += pm10[i][j];

            if (pm25[i][j] < 150) {
                pm25LessThan150++;
            }
            if (pm25[i][j] > 150 && pm10[i][j] > 250) {
                pm25LessThan150Andpm10GreaterThan250++;
            }
        }

        printf("\nСенсор %d:\n", i);
        printf("  PM10 мін: %.2f | макс: %.2f\n", pm10Min, pm10Max);
        printf("  Середнє PM25: %.2f | PM10: %.2f\n", pm25Sum / Meas, pm10Sum / Meas);
        printf("  (PM25 < 150): %d\n", pm25LessThan150);
        printf("  (PM25 > 150 та PM10 > 250): %d\n", pm25LessThan150Andpm10GreaterThan250);
    }
}

void column_stats() {
    printf("\n--- Статистика по стовпцях ---\n");
    for (int j = 0; j < Meas; j++) {
        int countCombined = 0;
        double pm10Sum    = 0;

        for (int i = 0; i < Sensor; i++) {
            if (pm25[i][j] > 150 && pm10[i][j] > 300) countCombined++;
            pm10Sum += pm10[i][j];
        }
        printf("Вимір %d: Критичні сенсори: %d, PM10 сер: %.2f\n", j, countCombined, pm10Sum / Sensor);
    }
}

void stats() {
    double pm25Min = pm25[0][0], pm25Max = pm25[0][0];
    double pm10Min = pm10[0][0], pm10Max = pm10[0][0];
    double pm25Sum = 0;

    for (int i = 0; i < Sensor; i++) {
        for (int j = 0; j < Meas; j++) {
            if (pm25[i][j] < pm25Min) pm25Min = pm25[i][j];
            if (pm25[i][j] > pm25Max) pm25Max = pm25[i][j];
            pm25Sum += pm25[i][j];

            if (pm10[i][j] < pm10Min) pm10Min = pm10[i][j];
            if (pm10[i][j] > pm10Max) pm10Max = pm10[i][j];
        }
    }
    double pm25Average    = pm25Sum / (Sensor * Meas);
    double pm10Difference = pm10Max - pm10Min;

    int countPm25AboveAvg  = 0;
    int countPm10BelowDiff = 0;

    for (int i = 0; i < Sensor; i++) {
        for (int j = 0; j < Meas; j++) {
            if (pm25[i][j] > pm25Average) countPm25AboveAvg++;
            if (pm10[i][j] < pm10Difference) countPm10BelowDiff++;
        }
    }

    printf("\n--- Загальна статистика ---\n");
    printf("PM25: Мін %.2f, Макс %.2f, Сер %.2f (>сер: %d)\n", pm25Min, pm25Max, pm25Average, countPm25AboveAvg);
    printf("PM10: Мін %.2f, Макс %.2f, Різниця %.2f (<різн: %d)\n", pm10Min, pm10Max, pm10Difference,
           countPm10BelowDiff);
}

void check_monotonous(double **array, int Sensor, int Meas) {
    for (int j = 0; j < Sensor; j++) {
        bool is_increasing = true;
        bool is_decreasing = true;

        for (int i = 0; i < Meas - 1; i++) {
            if (array[j][i] < array[j][i + 1]) {
                is_decreasing = false;
            }
            if (array[j][i] > array[j][i + 1]) {
                is_increasing = false;
            }
        }

        printf("Рядок %d: ", j);
        if (is_increasing)
            printf("монотонно зростає\n");
        else if (is_decreasing)
            printf("монотонно спадає\n");
        else
            printf("немонотонний\n");
    }
}

void check_column_local_max(int Sensor, int Meas) {
    int arr_choice, N = 0;
    printf("Масив (1 - PM25, 2 - PM10): ");
    scanf("%d", &arr_choice);

    double **target = (arr_choice == 1) ? pm25 : pm10;

    for (int j = 0; j < Meas; j++) {
        N = 0;
        for (int i = 1; i < Sensor - 1; i++) {
            if (target[i][j] > target[i - 1][j] && target[i][j] > target[i + 1][j]) {
                N++;
            }
        }
        printf("Стовпець %d, максимумів: %d\n", j, N);
    }
}

void check_column_dispersion(int Sensor, int Meas) {
    int choice;
    printf("Масив (1 - PM25, 2 - PM10): ");
    scanf("%d", &choice);
    double **target = (choice == 1) ? pm25 : pm10;

    printf("\n--- Дисперсія ---\n");
    for (int j = 0; j < Meas; j++) {
        double sum = 0;
        for (int i = 0; i < Sensor; i++) sum += target[i][j];
        double mu = sum / Sensor;

        double sum_diff2 = 0;
        for (int i = 0; i < Sensor; i++) {
            double diff = target[i][j] - mu;
            sum_diff2 += diff * diff;
        }

        printf("Стовпець %d – дисперсія: %.4f\n", j, sum_diff2 / Sensor);
    }
}

int main() {
    srand(time(NULL));
    do {
        printf("\nВведіть кількість рядків: ");
        scanf(" %d", &Sensor);
        if (Sensor <= 0) {
            printf("\nКількість не може бути < 0 \n");
        }
        printf("\nВведіть кількість стовбців: ");
        if (Meas) {
            printf("\nКількість не може бути < 0 \n");
        }
        scanf(" %d", &Meas);

    } while (Sensor <= 0 || Meas <= 0);

    pm25 = dynamic_array(Sensor, Meas);
    pm10 = dynamic_array(Sensor, Meas);

    do {
        menu_and_choise();
        switch (menu) {
            case 1:
                user_input();
                break;
            case 2:
                auto_fill();
                break;
            case 3:
                if (is_pm10_filled && is_pm25_filled)
                    see_table();
                else
                    printf("Спочатку заповніть масиви!\n");
                break;
            case 4:
                if (is_pm10_filled && is_pm25_filled)
                    row_stats();
                else
                    printf("Спочатку заповніть масиви!\n");
                break;
            case 5:
                if (is_pm10_filled && is_pm25_filled)
                    column_stats();
                else
                    printf("Спочатку заповніть масиви!\n");
                break;
            case 6:
                if (is_pm10_filled && is_pm25_filled)
                    stats();
                else
                    printf("Спочатку заповніть масиви!\n");
                break;
            case 7:
                if (!is_pm10_filled && !is_pm25_filled) {
                    printf("Масиви пусті!\n");
                    break;
                }
                int m_choice;
                printf("Масив (1-pm25, 2-pm10): ");
                scanf("%d", &m_choice);
                if (m_choice == 1 && is_pm25_filled)
                    check_monotonous(pm25, Sensor, Meas);
                else if (m_choice == 2 && is_pm10_filled)
                    check_monotonous(pm10, Sensor, Meas);
                break;
            case 8:
                if (is_pm10_filled && is_pm25_filled) {
                    check_column_local_max(Sensor, Meas);
                }
                break;
            case 9:
                if (is_pm10_filled && is_pm25_filled) {
                    check_column_dispersion(Sensor, Meas);
                }
                break;
            case 10:
                if (!is_pm10_filled || !is_pm25_filled) {
                    printf("Спочатку заповніть масиви!\n");
                    continue;
                }
                printf("\t --PM25--\n");
                pm25 = add_row(pm25, Sensor, Meas);
                printf("\t --PM10--\n");
                pm10 = add_row(pm10, Sensor, Meas);
                Sensor++;
                break;
            case 11:
                if (!is_pm10_filled || !is_pm25_filled) {
                    printf("Спочатку заповніть масиви!\n");
                    continue;
                }
                int row_to_delete;
                do {
                    printf("Номер рядка для видалення (0 - %d): ", Sensor - 1);
                    scanf("%d", &row_to_delete);
                    if (row_to_delete < 0) {
                        printf("Рядок не може бути <0 :p\n");
                    } else if (row_to_delete > Sensor) {
                        printf("Номер рядка > кільеості сенсорів :(\n");
                    }
                } while (row_to_delete < 0 || row_to_delete >= Sensor);

                pm25 = delete_row(pm25, Sensor, row_to_delete);
                pm10 = delete_row(pm10, Sensor, row_to_delete);
                Sensor--;
                printf("Рядок %d видалено, нова к-ть сенсорів: %d\n", row_to_delete, Sensor);

                if (Sensor == 0) {
                    is_pm25_filled = false;
                    is_pm10_filled = false;
                    printf("Масиви очищено\n");
                }
                break;
            case 0:
                printf("Вихід!\n");
                break;
            default:
                printf("Не той пункт!\n");
                break;
        }
    } while (menu != 0);

    free_array(pm25, Sensor);
    free_array(pm10, Sensor);
    pm10   = NULL;
    pm25   = NULL;
    target = NULL;
    return 0;
}