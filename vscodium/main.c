#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double **pm25 = NULL;
double **pm10 = NULL;
char menu, pm10Filled = 0, pm25Filled = 0;
int ActualSensor, ActualMeas;

double **dyn_arr(int ActualSensor, int ActualMeas) {
    double **arr = (double **) malloc(ActualSensor * sizeof(double *));
    if (pm10 == NULL) {
        printf("Помилка виділення пам'яті\n");
        return NULL;
    }
    for (int i = 0; i < ActualSensor; i++) {
        double **arr = (double **) malloc(ActualSensor * sizeof(double *));
    }
    return 0;
};

char MenuAndChoise() {
    printf("\n\t\t    МЕНЮ:\n");
    printf("\t1 ├ Ручне введення\n");
    printf("\t2 ├ Автоматичне заповнення даних\n");
    printf("\t3 ├ Виведення даних\n");
    printf("\t4 ├ Статистика по рядках\n");
    printf("\t5 ├ Статистика по стовпцях\n");
    printf("\t6 ├ Статистика по всім даним\n");
    printf("\t7 ├ Перевірка на монотонність\n");
    printf("\t8 ├ Кількість локальних максимумів\n");
    printf("\t9 ├ Дисперсія по стовбцях\n");
    printf("\t0 └ Вихід з програми\n>>> ");
    scanf(" %hhd", &menu);
    return 0;
}

void user_input() {
    int sensorSelection;
    printf(
        "Виберіть масив для ручного введення:\n   1 - PM25\n   2 - "
        "PM10\n>>> ");
    scanf("%d", &sensorSelection);
    if (sensorSelection == 1) {
        printf("Введення даних для PM25:\n");
        for (int i = 0; i < ActualSensor; i++) {
            for (int j = 0; j < ActualMeas; j++) {
                printf("Сенсор %d, вимір %d: ", i, j);
                scanf("%lf", &pm25[i][j]);
            };
        };
        pm25Filled = 1;
    } else if (sensorSelection == 2) {
        printf("Введення даних для PM10:\n");
        for (int i = 0; i < ActualSensor; i++) {
            for (int j = 0; j < ActualMeas; j++) {
                printf("Сенсор %d, вимір %d: ", i, j);
                scanf("%lf", &pm10[i][j]);
            };
        };
        pm10Filled = 1;
    } else {
        printf("Неправильний вибір!\n");
    };
}

void auto_fill() {
    int selection;
    printf("Який масив заповнити?\n");
    printf("    1 - PM25\n    2 - PM10\n    3 - Обидва\n>>> ");
    scanf("%d", &selection);

    if (selection == 1 || selection == 3) {
        for (int i = 0; i < ActualSensor; i++) {
            for (int j = 0; j < ActualMeas; j++) {
                pm25[i][j] = 5.0 + ((double) rand() / RAND_MAX) * 296;
            };
        };
        pm25Filled = 1;
        printf("Масив PM25 заповнено\n");
    };
    if (selection == 2 || selection == 3) {
        for (int i = 0; i < ActualSensor; i++) {
            for (int j = 0; j < ActualMeas; j++) {
                pm10[i][j] = 10.0 + ((double) rand() / RAND_MAX) * 490;
            };
        };
        pm10Filled = 1;
        printf("Масив PM10 заповнено\n");
    };
    if (selection < 1 || selection > 3) {
        printf("Неправильний вибір!\n");
    }
}

void see_table() {
    int selection;
    printf(
        "Дані якого масиву вивести?\n    1 - PM25\n    2 - "
        "PM10\n>>> ");
    scanf("%d", &selection);

    if (selection == 1) {
        printf("\n--- PM25 ---\n");
        printf("      ");
        for (int j = 0; j < ActualMeas; j++) {
            printf("%6d", j);
        };
        printf("\n");
        for (int i = 0; i < ActualSensor; i++) {
            printf(" %2d | ", i);
            for (int j = 0; j < ActualMeas; j++) {
                printf("%6.1f", pm25[i][j]);
            }
            printf("\n");
        };
    } else if (selection == 2) {
        printf("\n--- PM10 ---\n");
        printf("      ");
        for (int j = 0; j < ActualMeas; j++) {
            printf("%6d", j);
        };

        printf("\n");
        for (int i = 0; i < ActualSensor; i++) {
            printf(" %2d | ", i);
            for (int j = 0; j < ActualMeas; j++) {
                printf("%6.1f", pm10[i][j]);
            };
            printf("\n");
        };
    } else {
        printf("Неправильний вибір!\n");
    };
}

void row_stats() {
    printf("\n--- Статистика по рядках (для кожного сенсора) ---\n");

    for (int i = 0; i < ActualSensor; i++) {
        double pm10Min      = pm10[i][0];
        double pm10Max      = pm10[i][0];
        double pm25Sum      = 0;
        double pm10Sum      = 0;
        int pm25LessThan150 = 0, pm25LessThan150Andpm10GreaterThan250 = 0;

        for (int j = 0; j < ActualMeas; j++) {
            if (pm10[i][j] < pm10Min) {
                pm10Min = pm10[i][j];
            };
            if (pm10[i][j] > pm10Max) {
                pm10Max = pm10[i][j];
            };

            pm25Sum += pm25[i][j];
            pm10Sum += pm10[i][j];

            // pm25 < 150
            if (pm25[i][j] < 150) {
                pm25LessThan150++;
            }

            // pm25 > 150 , pm10 > 250
            if (pm25[i][j] > 150 && pm10[i][j] > 250) {
                pm25LessThan150Andpm10GreaterThan250++;
            };
        };

        double pm25Average = pm25Sum / ActualMeas;
        double pm10Average = pm10Sum / ActualMeas;

        printf("\nСенсор %d:\n", i);
        printf("  PM10 мін: %.2f\n", pm10Min);
        printf("  PM10 макс: %.2f\n", pm10Max);
        printf("  PM25 середнє: %.2f\n", pm25Average);
        printf("  PM10 середнє: %.2f\n", pm10Average);
        printf("  К-ть вимірів (PM25 < 150): %d\n", pm25LessThan150);
        printf("  К-ть вимірів (PM25 > 150 та PM10 > 250): %d\n", pm25LessThan150Andpm10GreaterThan250);
    };
}

void column_stats() {
    printf("\n--- Статистика по стовпцях (для кожного виміру) ---\n");

    for (int j = 0; j < ActualMeas; j++) {
        int countCombined = 0;
        double pm10Sum    = 0;

        for (int i = 0; i < ActualSensor; i++) {
            if (pm25[i][j] > 150 && pm10[i][j] > 300) {
                countCombined++;
            }

            pm10Sum += pm10[i][j];
        }

        double pm10Average = pm10Sum / ActualSensor;

        printf("\nВимір %d:\n", j);
        printf("  К-ть сенсорів (PM25 > 150, PM10 > 300): %d\n", countCombined);
        printf("  PM10 середнє по сенсорах: %.2f\n", pm10Average);
    };
}

void stats() {
    double pm25Min = pm25[0][0], pm25Max = pm25[0][0];
    double pm10Min = pm10[0][0], pm10Max = pm10[0][0];
    double pm25Sum = 0;

    for (int i = 0; i < ActualSensor; i++) {
        for (int j = 0; j < ActualMeas; j++) {
            if (pm25[i][j] < pm25Min) {
                pm25Min = pm25[i][j];
            }
            if (pm25[i][j] > pm25Max) {
                pm25Max = pm25[i][j];
                pm25Sum += pm25[i][j];
            }

            if (pm10[i][j] < pm10Min) {
                pm10Min = pm10[i][j];
            }
            if (pm10[i][j] > pm10Max) {
                pm10Max = pm10[i][j];
            }
        };
    };
    double pm25Average    = pm25Sum / (ActualSensor * ActualMeas);
    double pm10Difference = pm10Max - pm10Min;

    int countPm25AboveAvg  = 0;
    int countPm10BelowDiff = 0;

    for (int i = 0; i < ActualSensor; i++) {
        for (int j = 0; j < ActualMeas; j++) {
            if (pm25[i][j] > pm25Average) {
                countPm25AboveAvg++;
            }
            if (pm10[i][j] < pm10Difference) {
                countPm10BelowDiff++;
            };
        };
    };

    printf("\n--- Загальна статистика по всім даним ---\n");
    printf("Масив PM25:\n");
    printf("  Мінімальне значення: %.2f\n", pm25Min);
    printf("  Максимальне значення: %.2f\n", pm25Max);
    printf("  Середнє значення: %.2f\n", pm25Average);
    printf("  К-ть елементів > середнього: %d\n", countPm25AboveAvg);

    printf("\nМасив PM10:\n");
    printf("  Мінімальне значення: %.2f\n", pm10Min);
    printf("  Максимальне значення: %.2f\n", pm10Max);
    printf("  Різниця (Макс - Мін): %.2f\n", pm10Difference);
    printf("  К-ть елементів < різниці: %d\n", countPm10BelowDiff);
}

void check_monotonous_pm10(double pm10[][MEAS], int ActualSensor, int ActualMeas) {
    for (int j = 0; j < ActualSensor; j++) {
        int is_increasing = 1;
        int is_decreasing = 1;

        for (int i = 0; i < ActualMeas - 1; i++) {
            if (pm10[j][i] < pm10[j][i + 1]) {
                is_decreasing = 0;
            }
            if (pm10[j][i] > pm10[j][i + 1]) {
                is_increasing = 0;
            }
        }
        if (is_increasing) {
            printf("Рядок %d – монотонно зростаючий\n", j);
        } else if (is_decreasing) {
            printf("Рядок %d – монотонно спадний\n", j);
        } else {
            printf("Рядок %d – немонотонний\n", j);
        }
    }
}

void check_monotonous_pm25(double pm25[][MEAS], int ActualSensor, int ActualMeas) {
    for (int j = 0; j < ActualSensor; j++) {
        int is_increasing = 1;
        int is_decreasing = 1;

        for (int i = 0; i < ActualMeas - 1; i++) {
            if (pm25[j][i] < pm25[j][i + 1]) {
                is_decreasing = 0;
            }
            if (pm25[j][i] > pm25[j][i + 1]) {
                is_increasing = 0;
            }
        }
        if (is_increasing) {
            printf("Рядок %d – монотонно зростаючий\n", j);
        } else if (is_decreasing) {
            printf("Рядок %d – монотонно спадний\n", j);
        } else {
            printf("Рядок %d – немонотонний\n", j);
        }
    }
}

void check_column_local_max(double pm10[][MEAS], double pm25[][MEAS], int ActualSensor, int ActualMeas) {
    int arr, N = 0;
    printf("Масив для аналізу дисперсії (1 - PM25, 2 - PM10): ");
    scanf("%d", &arr);

    switch (arr) {
        case 1: {
            for (int j = 0; j < ActualMeas; j++) {
                N = 0;
                for (int i = 1; i < ActualSensor - 1; i++) {
                    if (pm10[i][j] > pm10[i - 1][j] && pm10[i][j] > pm10[i + 1][j]) {
                        N++;
                    }
                }
                printf("Стовпець %d, максимумів: %d\n", j, N);
            }
        } break;
        case 2: {
            for (int j = 0; j < ActualMeas; j++) {
                N = 0;
                for (int i = 1; i < ActualSensor - 1; i++) {
                    if (pm25[i][j] > pm25[i - 1][j] && pm25[i][j] > pm25[i + 1][j]) {
                        N++;
                    }
                }
                printf("Стовпець %d, максимумів: %d\n", j, N);
            }
        } break;
    }
}

void check_column_dispersion(double pm10[][MEAS], double pm25[][MEAS], int ActualSensor, int ActualMeas) {
    int choice;
    double sum, mu, diff, sum_diff2, dispersion;
    printf("Масив для аналізу дисперсії (1 - PM25, 2 - PM10): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("\n--- Дисперсія (PM25) ---\n");
            for (int j = 0; j < ActualMeas; j++) {
                sum = 0;
                for (int i = 0; i < ActualSensor; i++) {
                    sum += pm25[i][j];
                }
                mu = sum / ActualSensor;

                sum_diff2 = 0;
                for (int i = 0; i < ActualSensor; i++) {
                    diff = pm25[i][j] - mu;
                    sum_diff2 += diff * diff;
                }

                dispersion = sum_diff2 / ActualSensor;
                printf("Стовпець %d – дисперсія: %.4f\n", j, dispersion);
            }
            break;

        case 2:

            printf("\n--- Дисперсія (PM10) ---\n");
            for (int j = 0; j < ActualMeas; j++) {
                sum = 0;
                for (int i = 0; i < ActualSensor; i++) {
                    sum += pm10[i][j];
                }
                mu = sum / ActualSensor;

                sum_diff2 = 0;
                for (int i = 0; i < ActualSensor; i++) {
                    diff = pm10[i][j] - mu;
                    sum_diff2 += diff * diff;
                }

                dispersion = sum_diff2 / ActualSensor;
                printf("Стовпець %d – дисперсія: %.4f\n", j, dispersion);
            }
            break;

        default:
            printf("Невірний вибір!\n");
            break;
    }
}
int is_pm25_filled() {
    if (!pm25Filled) {
        printf("Заповніть масив PM2.5!\n");
        return 0;
    };
    return 1;
}

int is_pm10_filled() {
    if (!pm10Filled) {
        printf("Заповніть масив PM10!\n");
        return 0;
    };
    return 1;
}

int main() {
    srand(time(NULL));
    do {
        printf("Фактична к-ть сенсорів (<= %d): ", SENSOR);
        scanf("%d", &ActualSensor);
        printf("Фактична к-ть вимірів (<= %d): ", MEAS);
        scanf("%d", &ActualMeas);
        if (ActualSensor > SENSOR || ActualMeas > MEAS || ActualMeas <= 0 || ActualSensor <= 0) {
            printf("Вихід за межі(кількості?)\n");
        };
    } while (ActualSensor > SENSOR || ActualMeas > MEAS || ActualMeas <= 0 || ActualSensor <= 0);
    do {
        MenuAndChoise();
        switch (menu) {
            case 1: {
                user_input();
                break;
            };
            case 2: {
                auto_fill();
                break;
            };
            case 3: {
                see_table();
                break;
            };
            case 4: {
                if (!pm25Filled || !pm10Filled) {
                    printf("Для статистики заповніть обидва масиви\n");
                    continue;
                };
                row_stats();
                break;
            };
            case 5: {
                if (is_pm25_filled() && is_pm10_filled()) {
                    column_stats();
                }
                // if (!pm25Filled || !pm10Filled) {
                //     printf("Для статистики заповніть обидва масиви!\n");
                //     continue;
                // };
                break;
            };
            case 6: {
                if (is_pm25_filled() && is_pm10_filled()) {
                    stats();
                }
                break;
            };
            case 7: {
                if (is_pm25_filled() && is_pm10_filled()) {
                    int arr;
                    printf("Введіть масив який хочете перевірити.\n 1 - pm25 \n 2 - pm10\n>>>");
                    scanf("%d", &arr);
                    switch (arr) {
                        case 1:
                            check_monotonous_pm25(pm25, ActualSensor, ActualMeas);
                            break;
                        case 2:
                            check_monotonous_pm10(pm10, ActualSensor, ActualMeas);
                            break;
                        default:
                            printf("Неправильний вибір!");
                            break;
                    }
                }

                break;
            }
            case 8:
                if (!pm25Filled || !pm10Filled) {
                    printf("Для статистики заповніть обидва масиви!\n");
                    continue;
                };
                check_column_local_max(pm10, pm25, ActualSensor, ActualMeas);
                break;
            case 9:
                if (!pm25Filled || !pm10Filled) {
                    printf("Для статистики заповніть обидва масиви!\n");
                    continue;
                };
                check_column_dispersion(pm10, pm25, ActualSensor, ActualMeas);
                break;
            case 0:
                break;
            default:
                printf("Не той пункт!\n");
                break;
        };
    } while (menu != 0);
    return 0;
}