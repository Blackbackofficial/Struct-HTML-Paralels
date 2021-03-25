#include "trivial.h"

void trivial_emotional_color(const char * buffer, int * emotional_color) {
    int like = 0;
    int dislike = 0;
    for (int i = 0; i < FILESIZE && buffer[i] != '\0'; i++) {
        while (buffer[i] != ':' && buffer[i+1] != '\0')
            i++;
        if (buffer[i+1] == '(')
            dislike++;
        if (buffer[i+1] == ')')
            like++;
    }
    *emotional_color = like > dislike ? POSITIVE : (like < dislike ? NEGATIVE : NEUTRAL);
}