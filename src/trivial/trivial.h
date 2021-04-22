#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#ifndef DZ1_MAIN_H
#define DZ1_MAIN_H

#define FILESIZE 99929400
#define POSITIVE 0
#define NEGATIVE 1
#define NEUTRAL 2
#define AVERAGED_SIZE 50

void trivial_emotional_color(const char * buffer, int * emotional_color, int size);

#endif //DZ1_MAIN_H