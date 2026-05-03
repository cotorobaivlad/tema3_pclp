#include "../src/task2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../src/task1.h"
#include "../src/task3.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Format: %s <input_database>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    secretariat *s = citeste_secretariat(argv[1]);

    cripteaza_studenti(s, "pclp1", 5, "aa", 2, "./output.txt");

    elibereaza_secretariat(&s);
    return 0;
}
