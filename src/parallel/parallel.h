#include <unistd.h>
#include "trivial.h"


#ifndef DZ1_P_H
#define DZ1_P_H

typedef struct {
    int ** fd;
} FD_P;

void count_smile(const char * buffer, size_t start, size_t end, int * sum);
void parallel_emotional_color(void (*) (), const char * buffer, int * emotional_color, int size);
FD_P * del_new_description(FD_P * pipes, int count);
FD_P * new_pipes(int process);

#endif //DZ1_P_H