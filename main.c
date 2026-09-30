#include <stdio.h>

#if defined(_WIN32)
    #include <windows.h>
    #define SLEEP_MS(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP_MS(ms) usleep((ms) * 1000)
#endif


int main() {
#if defined(_WIN32)
    SetConsoleOutputCP(CP_UTF8);
#endif

    int ms = 200;
    int rows = 10, cols = 10, gens = 30;
    int field[rows][cols];
    int newField[rows][cols];
    int i, j, di, dj, gen;
    int neighbors;


    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            field[i][j] = 0;
        }
    }

    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("Ошибка: не удалось открыть файл\n");
        return 1;
    }

    int ch;
    int row = 0, col = 0;
    while ((ch = fgetc(f)) != EOF) {
        if (ch == '\n') {
            row++;
            col = 0;
        } else if (ch == '#' || ch == '.') {
            if (row < rows && col < cols) {
                if (ch == '#') {
                    field[row][col] = 1;
                } else {
                    field[row][col] = 0;
                }
            }
            col++;
        }
    }
    fclose(f);


    for (gen = 1; gen <= gens; gen++) {

        printf("\e[1;1H\e[2J");

        printf("Generation #%d\n", gen);

        printf("+");
        for (j = 0; j < cols; j++) {
            printf("-");
        }
        printf("+\n");

        for (i = 0; i < rows; i++) {
            printf("|");
            for (j = 0; j < cols; j++) {
                if (field[i][j] == 1) {
                    printf("\033[32m█\033[0m");   /* зелёный '#' */
                } else {
                    printf("·");
                }
            }
            printf("|\n");
        }

        printf("+");
        for (j = 0; j < cols; j++) {
            printf("-");
        }
        printf("+\n");
        printf("\n");

        fflush(stdout);

        SLEEP_MS(ms);

        for (i = 0; i < rows; i++) {
            for (j = 0; j < cols; j++) {
                neighbors = 0;

                for (di = -1; di <= 1; di++) {
                    for (dj = -1; dj <= 1; dj++) {
                        if (di == 0 && dj == 0) {
                            continue;
                        }
                        if (i + di >= 0 && i + di < rows && j + dj >= 0 && j + dj < cols) {
                            neighbors = neighbors + field[i + di][j + dj];
                        }
                    }
                }

                if (field[i][j] == 1) {
                    if (neighbors == 2 || neighbors == 3) {
                        newField[i][j] = 1;
                    } else {
                        newField[i][j] = 0;
                    }
                } else {
                    if (neighbors == 3) {
                        newField[i][j] = 1;
                    } else {
                        newField[i][j] = 0;
                    }
                }
            }
        }

        for (i = 0; i < rows; i++) {
            for (j = 0; j < cols; j++) {
                field[i][j] = newField[i][j];
            }
        }
    }

    return 0;
}