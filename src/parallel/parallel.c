#include "parallel.h"

void count_smile(const char * buffer, size_t start, size_t end, int * sum) {
    for (int i = start; i < FILESIZE - 1 && i < end && buffer[i] != '\0'; i++) {
        while (buffer[i] != ':' && buffer[i+1] != '\0')
            i++;
        if (buffer[i+1] == '(')
            (*sum)--;
        if (buffer[i+1] == ')')
            (*sum)++;
    }
}

FD_P * del_new_description(FD_P * pipes, int count) {
    for (int i = 0; i < count; ++i) {
        close(*pipes->fd[i]);
        free(pipes->fd[i]);
    }
    if (pipes != NULL) free(pipes->fd);
    free(pipes);
    return NULL;
}

FD_P * new_pipes(int process) {
    if (process <= 0)
        return NULL;

    FD_P *pipes = (FD_P *) malloc(sizeof(FD_P));
    if (pipes == NULL)
        return NULL;

    pipes->fd = malloc(process * sizeof(int *));
    if (pipes->fd == NULL) {
        free(pipes);
        return NULL;
    }

    for (int i = 0; i < process; ++i) {
        int count = -1;
        pipes->fd[i] = (int *) malloc(2 * sizeof(int *));
        if (pipes->fd[i] == NULL)
            return NULL;

        count = pipes->fd[i] == NULL ? i : (pipe(pipes->fd[i]) != 0 ? process : count);
        if (pipes != NULL && count > 0) // если не создались
            return del_new_description(pipes, count);
    }
    return pipes;
}

void parallel_emotional_color(void (*par) (), const char * buffer, int * emotional_color, int size) {
    if (par == NULL || buffer == NULL)
        return;

    size_t process = sysconf(_SC_NPROCESSORS_ONLN);
    if (process < 0) {
        printf("Забрал всю память");
        exit(EXIT_FAILURE);
    }

    FD_P * pipes = new_pipes(process);
    if (pipes == NULL) {
        printf("Не выделились pipes");
        exit(EXIT_FAILURE);
    }
    size_t part = (size_t) (size / process);

    for (int i = 0; i < process; i++) {
        size_t pid = fork();
        if (pid == -1) {
            printf("Не выделился процесс");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            size_t start = i * part;
            size_t end =  i < process - 1 ? (start + part) : FILESIZE;
            int sum = 0;
            count_smile(buffer, start, end, &sum);

            write(pipes->fd[i][1], &sum, sizeof(sum));
            exit(EXIT_SUCCESS);
        }
    }

    for (int j = 0; j < process; ++j)
        wait(EXIT_SUCCESS);

    int big_sum = 0;
    for (int i = 0; i < process; ++i) {
        int sum = 0;
        read(pipes->fd[i][0], &sum, sizeof(int));
        big_sum += sum;
    }
    del_new_description(pipes, process);
    *emotional_color = big_sum > 0 ? POSITIVE : (big_sum < 0 ? NEGATIVE : NEUTRAL);
}