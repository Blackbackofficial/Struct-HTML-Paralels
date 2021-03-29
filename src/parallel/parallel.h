#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#ifndef DZ1_P_H
#define DZ1_P_H

typedef struct {
    int ** fd;     //массив fd[2]
    size_t size;  //сколько процессов у нас есть
} pipes_t;


void parallel_emotional_color(const char * buffer, int * emotional_color);

#endif //DZ1_P_H