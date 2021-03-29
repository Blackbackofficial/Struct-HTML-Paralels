#include "parallel.h"
#include "trivial/trivial.h"

void count_smile(const char * buffer, const size_t start, const size_t end, int * sum) {
    int like = 0;
    for (int i = start; i < FILESIZE-1 && i < end && buffer[i] != '\0'; i++) {
        if (buffer[i+1] == '(')
            like--;
        if (buffer[i+1] == ')')
            like++;
    }
    *sum = like;
}
int free_pipes(pipes_t *pipes) {
    if (NULL == pipes) {
        return -1;
    }
    for (size_t i = 0; i < pipes->size; ++i) {
        close(pipes->fd[i][0]);
        close(pipes->fd[i][1]);
        free(pipes->fd[i]);
    }
    free(pipes->fd);
    free(pipes);
    return 0;
}

pipes_t * create_pipes(size_t size) {
    if (size <= 0) {
        return NULL;
    }

    pipes_t *pipes = (pipes_t *)malloc(sizeof(pipes_t));
    if (pipes == NULL) {
        return NULL;
    }
    //передаем число процессов
    pipes->size = size;

    //память под дескрипторы
    pipes->fd = (int *) malloc(size * sizeof(int*));
    if (pipes->fd == NULL) {
        free(pipes);
        return NULL;
    }

    for (size_t i = 0; i < size; ++i) {
        //готовим массив
        pipes->fd[i] = (int *)malloc(2 * sizeof(int *));
        if (pipes->fd[i] == NULL) {
            //закрываем все что успели открыть
            for (size_t j = 0; j < i; ++j) {
                close(pipes->fd[i][0]);
                close(pipes->fd[i][1]);
                free(pipes->fd[i]);
            }
            free(pipes->fd);
            free(pipes);
            return NULL;
        }
        //пытаемся заполнить новыми дескрипторами
        if (pipe(pipes->fd[i]) != 0) {
            for (size_t j = 0; j < size; ++j) {
                close(pipes->fd[i][0]);
                close(pipes->fd[i][1]);
                free(pipes->fd[i]);
            }
            free(pipes->fd);
            free(pipes);
            return NULL;
        }
    }

    return pipes;
}

void parallel_emotional_color(const char * buffer, int * emotional_color) {
    size_t process = sysconf(_SC_NPROCESSORS_ONLN);
    if (process < 0) {
        printf("Забрал всю память");
        exit(0);
    }

    pipes_t * pipes = create_pipes(process);
    if (pipes == NULL) {
        printf("Не выделились pipes");
        exit(0);
    }
    size_t part = (size_t) (FILESIZE / process);

    for (int i = 0; i < process; i++) {
        size_t pid = fork();
        if (pid == -1){
            printf("Не выдидилился процесс");
            exit(0);
        }
        if (pid == 0) {
            size_t start = i * part;
            size_t end =  i < process - 1 ? (start + part) : FILESIZE;
            int sum = 0;
            count_smile(buffer, start, end, &sum);

            write(pipes->fd[i][1], &sum, sizeof(sum));
            exit(EXIT_SUCCESS);
        }
    }
    for (size_t j = 0; j < process; ++j) {
        wait(0);
    }
    int big_sum = 0;
    for (size_t i = 0; i < process; ++i) {
        int sum = 0;
        read(pipes->fd[i][0], &sum, sizeof(int));
        big_sum += sum;
    }

    if (free_pipes(pipes)) {
        printf("Не очистилось");
        exit(0);
    }
    *emotional_color = big_sum > 0 ? POSITIVE : (big_sum < 0 ? NEGATIVE : NEUTRAL);
}