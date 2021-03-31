#include <dlfcn.h>
#include "trivial/trivial.h"
#include "parallel/parallel.h"

struct smile_render {
    char smile[3];
};

void render_file() {
    srand(time(NULL));
    struct smile_render smile[3] = {":)", ":("};

    FILE* mf=fopen ("test.txt","w");

    for (int i = 0; i < FILESIZE/2; i++) {
        int num = rand() % 2;
        fputs(smile[num].smile, mf);
    }

    fclose(mf);
}

int main() {
    render_file();
    FILE * mf = fopen("test.txt","r");
    if (mf == NULL) {
        printf("No file");
        exit(0);
    }
    char * buffer = (char *) calloc(FILESIZE, sizeof(char));
    fgets(buffer, FILESIZE, mf);
    fclose(mf);

    // последовательная реализация
    int color_t, color_p;
    clock_t begin = clock();
    trivial_emotional_color(buffer, &color_t, FILESIZE);
    clock_t end = clock();
    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("Consistent algorithm time: %f\n", time_spent);

    // распараллеленная реализация c динамической библиотекой
    void * handle;
    handle = dlopen ("libDinlib_algo.so", RTLD_LAZY);
    if (!handle) {
        fputs(dlerror(), stderr);
        exit(EXIT_FAILURE);
    }

    void (*parallel)(void (*par) (), const char * buffer, int * emotional_color, int size);
    parallel = dlsym(handle, "parallel_emotional_color");

    begin = clock();
    parallel((void (*)) parallel_emotional_color, buffer, &color_p, FILESIZE);
    end = clock();
    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("Parallel algorithm time: %f\n", time_spent);


    if (color_t == color_p) printf("Emotional color %s\n", color_t == POSITIVE ? "positive" : (color_t == NEGATIVE  ? "negative" : "neutral"));
    else printf("The emotional coloring of algorithms is different");

    dlclose(handle);
    free(buffer);
    return 0;
}