#include "../src/task2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../src/task1.h"
#include "../include/structuri.h"
#define TEST_DB "tests/db/small.db"
#define MAX_LINE 100
// Tester

int main(int argc, char* argv[]) {
secretariat *s = citeste_secretariat(argv[1]);
FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }
int numar_comenzi = 0;
scanf("%d", &numar_comenzi);
for (int i = 0; i < numar_comenzi; i++) {
    char *linie = calloc(MAX_LINE, sizeof(char));
    fgets(linie, MAX_LINE, file);
    
    procesare_linie(s,*linie);
}
    elibereaza_secretariat(&s);
    return 0;
}
