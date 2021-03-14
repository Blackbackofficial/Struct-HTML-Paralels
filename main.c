/*
 * Создать структуру для хранения информации об HTML-теге: его имени, признаке ?открывающий/закрывающий? и
 * атрибутах тега. Составить с ее использованием программу, включающую в себя функцию, принимающую на вход
 * текстовую строку с одним тегом. На выход функция должна возвращать указатель на инициализированную структуру.
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

#define SIZE 1034
#define SIZE_VALUE 1024

typedef struct html_tag {
    char name[SIZE];
    char value[SIZE_VALUE];
} html;

void correct_name(const char * string, int count) {
    if (string[count] != ' ') {
        for (int i = 0; string[count] != ' ' && string[count] != '=' && string[count] != '>'; ++i) {
            if (!isalpha(string[count])) {
                printf("Incorrect name tag or name attribute\n");
                exit(0);
            }
            count++;
        }
    } else {
        printf("Incorrect name tag\n");
        exit(0);
    }
}

html * html_decoder(const char * str_tag) {
    int size_tag = 1;
    int str_ptr = 0;
    html * tag_ptr = calloc(size_tag, sizeof(html));
    char data[SIZE] = {'\0'};
    char value[SIZE_VALUE] = {'\0'};

    while (str_tag[str_ptr] == ' ')
        str_ptr++;

    if (str_tag[str_ptr] !='<') {
        printf("String is null or incorrect\n");
        exit(0);
    }
    if (str_tag[str_ptr+1] != '/')
        correct_name(str_tag, str_ptr+1);
    else
        correct_name(str_tag, str_ptr+2);

    for (int j = 0, flag = 0; str_tag[str_ptr] != ' ' && str_tag[str_ptr] != '>' && str_tag[str_ptr] != '\0'; ++str_ptr) {
        if (str_tag[str_ptr] == '<' && !flag) {
            flag = 1;
            if (str_tag[str_ptr+1] == '/') {
                strcpy(value, "close"); str_ptr++;
            } else
                strcpy(value, "open");
            continue;
        }
        if (flag)
            data[j++] = str_tag[str_ptr];
    }

    strcpy(tag_ptr->name, data);
    strcpy(tag_ptr->value, value);

    if (tag_ptr[0].value[0] == 'c' || str_tag[str_ptr] == '>' || tag_ptr[0].value[0] == '\0')
        return tag_ptr;

    while (str_tag[str_ptr] != '>') {
        if (str_tag[SIZE_VALUE-2] != '\0'){
            printf("Incorrect string format or crowded > SIZE_VALUE\n");
            exit(0);
        }

        memset(data, '\0', SIZE);
        memset(value, '\0', SIZE_VALUE);

        html *new_tag = calloc(++size_tag, sizeof(html));
        for (int j = 0; j < size_tag; ++j)
            new_tag[j] = tag_ptr[j];

        while (str_tag[str_ptr] == ' ')
            str_ptr++;

        correct_name(str_tag, str_ptr);
        for (int w = 0; (str_tag[str_ptr] != ' ') && (str_tag[str_ptr] != '=' && str_tag[str_ptr] != '>'); ++w)
            data[w] = str_tag[str_ptr++];

        while (str_tag[str_ptr] == ' ')
            str_ptr++;

        if (str_tag[str_ptr] == '=' || str_tag[str_ptr] == '/') {
            while (str_tag[str_ptr+1] == ' ')
                str_ptr++;

            if (str_tag[++str_ptr] == '/') {
                for (int r = 0; str_tag[str_ptr] != ' '; ++r) {
                    value[r] = str_tag[str_ptr++];
                } // проверка в случае action=/search
            } else {
                str_ptr++;
                for (int w = 0; str_tag[str_ptr] != '\"'; ++w)
                    value[w] = str_tag[str_ptr++];
            }
            str_ptr++;
        }
        strcpy(new_tag[size_tag-1].name, data);
        strcpy(new_tag[size_tag-1].value, value);
        tag_ptr  = new_tag;
    }
    return tag_ptr;
}

int main() {
    char str[SIZE_VALUE];
    fgets(str, SIZE_VALUE, stdin);
    fflush(stdin);
    html * i;
    i = html_decoder(str);
    for (int j = 0; j < 8; j++) { // укажем какое-то коллличество
        printf("%s\n", "-------------");
        printf("%s\n",i[j].name);
        printf("%s\n",i[j].value);
    }
    return 0;
}