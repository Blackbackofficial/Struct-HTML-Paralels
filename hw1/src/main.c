/*
 * Создать структуру для хранения информации об HTML-теге: его имени, признаке ?открывающий/закрывающий? и
 * атрибутах тега. Составить с ее использованием программу, включающую в себя функцию, принимающую на вход
 * текстовую строку с одним тегом. На выход функция должна возвращать указатель на инициализированную структуру.
 */

#include <stdio.h>
#include <stdlib.h>
#include "html.h"

int main() {
    char str[SIZE_VALUE]; // IN
    fgets(str, SIZE_VALUE, stdin);
    fflush(stdin);
    int size = 0;
    html * i = html_decoder(str, &size);
    for(int j = 0; j < size; j++) { // OUT
        printf("%s\n", "----------------------");
        printf("%s\n", i[size - (size-j)].name);
        printf("%s\n", i[size - (size-j)].value);
    }
    free(i);
    return 0;
}