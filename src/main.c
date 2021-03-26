/*
 * Вар:23 Сравните и выведите в консоль время работы последовательного и параллельного с использованием нескольких процессов
 * алгоритмов, каждый из которых выделяет в динамической памяти символьный массив размером 100 Мб и, рассматривая его
 * содержимое как абстрактную переписку, определяет эмоциональную окраску последней. Переписка считается оптимистичной,
 * если диграфов :) в ней больше, чем диграфов :(; в противном случае переписка признается пессимистичной.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "trivial/trivial.h"

struct smile_render {
    char smile[3];
};

void render_file() {
    srand(time(NULL));
    struct smile_render smile[3] = {":)", ":("};

    FILE* mf=fopen ("test.txt","w");

    for (int i = 0; i < FILESIZE/2; i++) {
        int num = rand() % 2;
        fputs(smile[num].smile, mf);
    }

    fclose(mf);
}

int main() {
    render_file();
    FILE* mf = fopen("test.txt","r");
    if (mf == NULL) {
        printf("No file");
        exit(0);
    }
    char * buffer = (char *) calloc(FILESIZE, sizeof(char));
    fgets(buffer, FILESIZE, mf);
    fclose(mf);

    int emotional_color;
    clock_t begin = clock();
    trivial_emotional_color(buffer, &emotional_color);
    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Эмоциональная окраска %s\n", emotional_color == POSITIVE ? "позитивная" : (emotional_color == NEGATIVE  ? "негативная" : "нейтральная"));
    printf("Время последовательного алгоритма: %f\n", time_spent);

    free(buffer);
    return 0;
}