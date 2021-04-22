#ifndef DZ1_MAIN_H
#define DZ1_MAIN_H

#define SIZE 32
#define SIZE_VALUE 512

typedef struct html_tag {
    char name[SIZE];
    char value[SIZE_VALUE];

} html;

int correct_name(const char * string, int count);
html * html_decoder(const char * string, int * size);

#endif //DZ1_MAIN_H

