#include "trivial.h"

void trivial_emotional_color(const char * buffer, int * emotional_color, int size) {
    int like = 0;
    for (int i = 0; i < size - 1 && buffer[i] != '\0'; i++) {
        while (buffer[i] != ':' && buffer[i+1] != '\0')
            i++;
        if (buffer[i+1] == '(')
            like--;
        if (buffer[i+1] == ')')
            like++;
    }
    *emotional_color = like > 0 ? POSITIVE : (like < 0 ? NEGATIVE : NEUTRAL);
}