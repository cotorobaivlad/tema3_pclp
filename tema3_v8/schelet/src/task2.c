#include "task2.h"
#include <math.h>
#define DECIMAL_PRECISION 100.0f
#define MAX_LINE 100
#define MAX_CAMP 10
#define MAX_CAMP_FILTRU 20
#define MAX_VALORI_FILTRU 20
#define MAX_OPERATOR 3
#define MAX_VALOARE 20
#define EPSILON 0.555555f
void interogare_simpla(secretariat *s, char *campuri, char *tabel) {  // funcite cu select fara conditii
    char *campuri_copie = malloc((strlen(campuri) + 1) * sizeof(char));
    snprintf(campuri_copie, strlen(campuri) + 1, "%s", campuri);  // salvez campurile in campuri_copie
    char **camp = malloc(MAX_CAMP * sizeof(char *));
    int nr_campuri = 0;
    char *token = strtok(campuri_copie, ", ");
    while (token != NULL) {
        camp[nr_campuri++] = strdup(token);
        if (!camp[nr_campuri - 1]) {
            perror("Memory allocation failed");
            for (int i = 0; i < nr_campuri - 1; i++) {
                free(camp[i]);
            }
            free(camp);
            free(campuri_copie);
            return;
        }
        token = strtok(NULL, ", ");
    }
    // verific in care tabel sunt
    if (strstr(tabel, "studenti")) {
        for (int i = 0; i < s->nr_studenti; i++) {
            for (int j = 0; j < nr_campuri; j++) {
                // verific campurile
                if (strcmp(camp[j], "id") == 0) {
                    printf("%d", s->studenti[i].id);
                }
                if (strcmp(camp[j], "nume") == 0) {
                    printf("%s", s->studenti[i].nume);
                }
                if (strcmp(camp[j], "an_studiu") == 0) {
                    printf("%d", s->studenti[i].an_studiu);
                }
                if (strcmp(camp[j], "statut") == 0) {
                    printf("%c", s->studenti[i].statut);
                }
                if (strcmp(camp[j], "medie_generala") == 0) {
                    printf("%.2f", s->studenti[i].medie_generala);
                }
                if (strcmp(camp[j], "*") == 0) {
                    printf("%d %s %d %c %.2f", s->studenti[i].id, s->studenti[i].nume, s->studenti[i].an_studiu,
                    s->studenti[i].statut, s->studenti[i].medie_generala);
                }
                if (nr_campuri > j+1) {
                    printf(" ");
                }
            }
            printf("\n");
        }
    } else if (strcmp(tabel, "materii") == 0) {  // verific daca tabelul este materii
        for (int i = 0; i < s->nr_materii; i++) {
            for (int j = 0; j < nr_campuri; j++) {
                  // verific campurile
                if (strcmp(camp[j], "id") == 0) printf("%d", s->materii[i].id);
                if (strcmp(camp[j], "nume") == 0) printf("%s", s->materii[i].nume);
                if (strcmp(camp[j], "nume_titular") == 0) printf("%s", s->materii[i].nume_titular);
                if (strcmp(camp[j], "*") == 0) {
                    printf("%d %s %s", s->materii[i].id, s->materii[i].nume, s->materii[i].nume_titular);
                }
                if (nr_campuri > j+1) {
                    printf(" ");
                }
            }
            printf("\n");
        }
    } else if (strcmp(tabel, "inrolari") == 0) {
        for (int i = 0; i < s->nr_inrolari; i++) {
            for (int j = 0; j < nr_campuri; j++) {
                  // verific campurile
                if (strcmp(camp[j], "id_student") == 0) printf("%d", s->inrolari[i].id_student);
                if (strcmp(camp[j], "id_materie") == 0) printf("%d", s->inrolari[i].id_materie);
                if (strcmp(camp[j], "note") == 0) {
                    for (int k = 0; k < NUMBER_OF_GRADES; k++) {
                        printf("%.2f", s->inrolari[i].note[k]);
                        if (k < NUMBER_OF_GRADES - 1) {
                            printf(" ");
                        }
                    }
                }
                if (strcmp(camp[j], "*") == 0) {  // afiseaza toate campurile
                    printf("%d %d ", s->inrolari[i].id_student, s->inrolari[i].id_materie);
                    for (int k = 0; k < NUMBER_OF_GRADES; k++) {
                        printf("%.2f", s->inrolari[i].note[k]);
                        if (k < NUMBER_OF_GRADES - 1) {
                            printf(" ");
                        }
                    }
                }
                if (nr_campuri > j+1) {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }
    free(campuri_copie);
    for (int i = 0; i < nr_campuri; i++) {
        free(camp[i]);
    }
    free(camp);
}
  // functie cu select cu o conditie
void interogare_filtrare(secretariat *s, const char *campuri,
const char *tabel, const char *filtru) {
    char *campuri_copie = strdup(campuri);
    char **camp = malloc(MAX_CAMP_FILTRU * sizeof(char *));
    int nr_campuri = 0;
    char *token = strtok(campuri_copie, ",");
    while (token != NULL) {
        camp[nr_campuri++] = strdup(token);
        token = strtok(NULL, ",");
    }
    char *camp_filtru = malloc(MAX_LINE * sizeof(char));
    char *valoare_filtru = malloc(MAX_VALORI_FILTRU * sizeof(char));
    char *operator_filtru = malloc(MAX_OPERATOR * sizeof(char));
    sscanf(filtru, "%s %s %s", camp_filtru, operator_filtru, valoare_filtru);
      // verific in care tabel sunt
    if (strstr(tabel, "studenti") != NULL) {
        for (int i = 0; i < s->nr_studenti; i++) {
            int conditie_ok = 0;
            if (strstr(camp_filtru, "an_studiu") != NULL) {  // verific daca campul este an_studiu
                int valoare_int = atoi(valoare_filtru);
                  // verific daca operatorul este corect
                if ((strcmp(operator_filtru, ">") == 0 && s->studenti[i].an_studiu > valoare_int) ||
                    (strcmp(operator_filtru, "<") == 0 && s->studenti[i].an_studiu < valoare_int) ||
                    (strcmp(operator_filtru, "=") == 0 && s->studenti[i].an_studiu == valoare_int)) {
                    conditie_ok = 1;
                }
            } else if (strcmp(camp_filtru, "medie_generala") == 0) {  // verific daca campul este medie_generala
                float valoare_float = (float)atof(valoare_filtru);  // convertez valoarea filtrului in float
                if ((strcmp(operator_filtru, ">") == 0 && s->studenti[i].medie_generala > valoare_float) ||
                    (strcmp(operator_filtru, "<") == 0 && s->studenti[i].medie_generala < valoare_float) ||
                    (strcmp(operator_filtru, "=") == 0 && s->studenti[i].medie_generala == valoare_float)) {
                    conditie_ok = 1;
                }
            } else if (strcmp(camp_filtru, "statut") == 0) {
                if ((strcmp(operator_filtru, "=") == 0 && strcmp(s->studenti[i].statut, valoare_filtru) == 0)) {
                    conditie_ok = 1;
                }
            } else if (strcmp(camp_filtru, "nume") == 0) {
                if ((strcmp(operator_filtru, "=") == 0 && strcmp(s->studenti[i].nume, valoare_filtru) == 0) ||
                    (strcmp(operator_filtru, "!=") == 0 && strcmp(s->studenti[i].nume, valoare_filtru) != 0)) {
                    conditie_ok = 1;
                }
            } else if (strcmp(camp_filtru, "id") == 0) {
                int valoare_int = atoi(valoare_filtru);  // convertez valoarea filtrului in int
                if ((strcmp(operator_filtru, "=") == 0 && s->studenti[i].id == valoare_int) ||
                (strcmp(operator_filtru, ">") == 0 && s->studenti[i].id > valoare_int)||
                (strcmp(operator_filtru, "<") == 0 && s->studenti[i].id < valoare_int)||
                (strcmp(operator_filtru, ">=") == 0 && s->studenti[i].id >= valoare_int)||
                (strcmp(operator_filtru, "<=") == 0 && s->studenti[i].id <= valoare_int)) {
                    conditie_ok = 1;
                }
            }
              // afisez campurile daca conditia este indeplinita
            if (conditie_ok) {  // afisez campurile daca conditia este indeplinita
                for (int j = 0; j < nr_campuri; j++) {
                    if (strstr(camp[j], "id") != NULL) {
                        printf("%d", s->studenti[i].id);
                    }
                    if (strstr(camp[j], "nume") != NULL) {
                        printf("%s", s->studenti[i].nume);
                    }
                    if (strstr(camp[j], "an_studiu") != NULL) {
                        printf("%d", s->studenti[i].an_studiu);
                    }
                    if (strstr(camp[j], "statut") != NULL) {
                        printf("%c", s->studenti[i].statut);
                    }
                    if (strstr(camp[j], "medie_generala") != NULL) {
                        printf("%.2f", s->studenti[i].medie_generala);
                    }
                    if (strstr(camp[j], "*") != NULL) {
                        printf("%d %s %d %c %.2f", s->studenti[i].id, s->studenti[i].nume,
                        s->studenti[i].an_studiu, s->studenti[i].statut, s->studenti[i].medie_generala);
                    }
                    if (nr_campuri > j+1) {
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }
    } else if (strstr(tabel, "materii") != NULL) {  // verific daca tabelul este materii
        for (int i = 0; i < s->nr_materii; i++) {
            int conditie_ok = 0;
            if (strstr(camp_filtru, "id") != NULL) {
                int valoare_int = atoi(valoare_filtru);
                if ((strstr(operator_filtru, "=") != NULL && s->materii[i].id == valoare_int)) {
                    conditie_ok = 1;
                }
            } else if (strstr(camp_filtru, "nume") != NULL) {
                if ((strcmp(operator_filtru, "=") != 0 && strcmp(s->materii[i].nume, valoare_filtru) == 0)) {
                    conditie_ok = 1;
                }
            }
            if (conditie_ok) {
                for (int j = 0; j < nr_campuri; j++) {
                    if (strstr(camp[j], "id") != NULL) {
                        printf("%d", s->materii[i].id);
                    }
                    if (strcmp(camp[j], "nume") ==0) {
                        printf("%s", s->materii[i].nume);
                    }
                    if (strstr(camp[j], "nume_titular") != NULL) {
                        printf("%s", s->materii[i].nume_titular);
                    }
                    if (strstr(camp[j], "*") != NULL) {
                        printf("%d %s %s", s->materii[i].id, s->materii[i].nume, s->materii[i].nume_titular);
                    }
                    if (strstr(camp[j], "*") != NULL) {
                        printf("%d %s %s", s->materii[i].id, s->materii[i].nume, s->materii[i].nume_titular);
                    }
                    if (nr_campuri > j+1) {
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }
    }     else if (strstr(tabel, "inrolari") != NULL) {  // verific daca tabelul este inrolari
        for (int i = 0; i < s->nr_inrolari; i++) {
            int conditie_ok = 0;
            if (strstr(camp_filtru, "id_student") != NULL) {
                int valoare_int = atoi(valoare_filtru);
                if ((strcmp(operator_filtru, "=") == 0 && s->inrolari[i].id_student == valoare_int)) {
                    conditie_ok = 1;
                }
            } else if (strstr(camp_filtru, "id_materie") != NULL) {
                int valoare_int = atoi(valoare_filtru);
                if ((strcmp(operator_filtru, "=") == 0 && s->inrolari[i].id_materie == valoare_int)) {
                    conditie_ok = 1;
                }
            }
            if (conditie_ok) {  // afisez campurile daca conditia este indeplinita
                for (int j = 0; j < nr_campuri; j++) {
                    if (strstr(camp[j], "id_student") != NULL) {
                        printf("%d", s->inrolari[i].id_student);
                    }
                    if (strstr(camp[j], "id_materie") != NULL) {
                        printf("%d", s->inrolari[i].id_materie);
                    }
                    if (strstr(camp[j], "note") != NULL) {
                        for (int k = 0; k < NUMBER_OF_GRADES; k++) {
                            printf("%.2f", s->inrolari[i].note[k]);
                            if (k < NUMBER_OF_GRADES - 1) {
                                printf(" ");
                            }
                        }
                    }
                    if (strstr(camp[j], "*") != NULL) {
                        printf("%d %d", s->inrolari[i].id_student, s->inrolari[i].id_materie);
                        for (int k = 0; k < NUMBER_OF_GRADES; k++) {
                            printf("%.2f", s->inrolari[i].note[k]);
                            if (k < NUMBER_OF_GRADES - 1) {
                                printf(" ");
                            }
                        }
                    }
                    if (nr_campuri > j+1) {
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }
    }
    for (int i = 0; i < nr_campuri; i++) {
        free(camp[i]);
    }
      // eliberez memoria alocata
    free(camp);
    free(campuri_copie);
    free(camp_filtru);
    free(valoare_filtru);
    free(operator_filtru);
}
  // functia de filtrare cu doua conditii
void filtrare_complexa(secretariat *s, const char *campuri,
const char *tabel, const char *filtru, const char *conditie) {
    char *campuri_copie = strdup(campuri);
    char **camp = malloc(MAX_CAMP_FILTRU * sizeof(char *));
    int nr_campuri = 0;
    char *token = strtok(campuri_copie, ",");
    while (token != NULL) {
        camp[nr_campuri++] = strdup(token);  // aloc memorie pentru campurile filtrate
        token = strtok(NULL, ",");
    }
    char *camp_filtru1 = malloc(MAX_CAMP_FILTRU * sizeof(char));
    char *operator_filtru1 = malloc(MAX_CAMP_FILTRU * sizeof(char));
    char *valoare_filtru1 = malloc(MAX_VALORI_FILTRU * sizeof(char));
    char *camp_filtru2 = malloc(MAX_CAMP_FILTRU * sizeof(char));
    char *operator_filtru2 = malloc(MAX_OPERATOR * sizeof(char));
    char *valoare_filtru2 = malloc(MAX_VALORI_FILTRU * sizeof(char));
      // citesc campul, operatorul si valoarea din conditie
    sscanf(filtru, "%s %s %s", camp_filtru1, operator_filtru1, valoare_filtru1);
    sscanf(conditie, "%s %s %s ", camp_filtru2, operator_filtru2, valoare_filtru2);
    if (strstr(tabel, "studenti") != NULL) {
        for (int i = 0; i < s->nr_studenti; i++) {
            int conditie_ok1 = 0, conditie_ok2 = 0;
              // parcurg fiecare student si verific daca indeplinesc conditiile
            if (strstr(camp_filtru1, "an_studiu") != NULL) {
                int valoare_int = atoi(valoare_filtru1);
                if ((strstr(operator_filtru1, ">") != NULL && s->studenti[i].an_studiu > valoare_int) ||
                    (strstr(operator_filtru1, "<") != NULL && s->studenti[i].an_studiu < valoare_int) ||
                    (strstr(operator_filtru1, "=") != NULL && s->studenti[i].an_studiu == valoare_int)) {
                    conditie_ok1 = 1;
                }
            }
            if (strstr(camp_filtru1, "medie_generala") != NULL) {
                float valoare_float = (float)atof(valoare_filtru1);
                if ((strstr(operator_filtru1, ">") != NULL && s->studenti[i].medie_generala > valoare_float) ||
                    (strstr(operator_filtru1, "<") != NULL && s->studenti[i].medie_generala < valoare_float) ||
                    (strstr(operator_filtru1, "=") != NULL && s->studenti[i].medie_generala == valoare_float)) {
                    conditie_ok1 = 1;
                }
            }
            if (strstr(camp_filtru1, "statut") != NULL) {
                if (strstr(operator_filtru1, "=") != NULL && s->studenti[i].statut == valoare_filtru1[0]) {
                    conditie_ok1 = 1;
                }
            }
            if (strstr(camp_filtru1, "id") != NULL) {
                int valoare_int = atoi(valoare_filtru1);
                if ((strstr(operator_filtru1, "=") != NULL && s->studenti[i].id == valoare_int) ||
                (strstr(operator_filtru1, "<") != NULL && s->studenti[i].id < valoare_int)
                || (strstr(operator_filtru1, ">") != NULL && s->studenti[i].id > valoare_int)) {
                    conditie_ok1 = 1;
                }
            }
            if (strstr(camp_filtru1, "nume") != NULL) {
                if (strstr(operator_filtru1, "=") != NULL && strcmp(s->studenti[i].nume, valoare_filtru1) == 0) {
                    conditie_ok1 = 1;
                }
            }
            if (strstr(camp_filtru1, "an_studiu") != NULL) {
                int valoare_int = atoi(valoare_filtru1);
                if ((strstr(operator_filtru1, ">") != NULL && s->studenti[i].an_studiu > valoare_int) ||
                (strstr(operator_filtru1, "<") != NULL && s->studenti[i].an_studiu < valoare_int) ||
                (strstr(operator_filtru1, "=") != NULL && s->studenti[i].an_studiu == valoare_int)) {
                    conditie_ok1 = 1;
                }
            }
            if (strstr(camp_filtru2, "an_studiu") != NULL) {
                int valoare_int = atoi(valoare_filtru2);
                if ((strstr(operator_filtru2, ">") != NULL && s->studenti[i].an_studiu > valoare_int) ||
                    (strstr(operator_filtru2, "<") != NULL && s->studenti[i].an_studiu < valoare_int) ||
                    (strstr(operator_filtru2, "=") != NULL && s->studenti[i].an_studiu == valoare_int)) {
                    conditie_ok2 = 1;
                }
            }
            if (strstr(camp_filtru2, "medie_generala") != NULL) {
                float valoare_float = (float)atof(valoare_filtru2);
                if ((strstr(operator_filtru2, ">") != NULL && s->studenti[i].medie_generala > valoare_float) ||
                    (strstr(operator_filtru2, "<") != NULL && s->studenti[i].medie_generala < valoare_float) ||
                    (strstr(operator_filtru2, "=") != NULL && s->studenti[i].medie_generala == valoare_float)) {
                    conditie_ok2 = 1;
                }
            }
            if (strstr(camp_filtru2, "statut") != NULL) {
                if (strstr(operator_filtru2, "=") != NULL && s->studenti[i].statut == valoare_filtru2[0]) {
                    conditie_ok2 = 1;
                }
            }
            if (strstr(camp_filtru2, "id") != NULL) {
                int valoare_int = atoi(valoare_filtru2);
                if ((strstr(operator_filtru2, "=") != NULL && s->studenti[i].id == valoare_int) ||
                (strstr(operator_filtru2, "<") != NULL && s->studenti[i].id < valoare_int)
                || (strstr(operator_filtru2, ">") != NULL && s->studenti[i].id > valoare_int)) {
                    conditie_ok2 = 1;
                }
            }
            if (strstr(camp_filtru2, "nume") != NULL) {
                if (strstr(operator_filtru2, "=") != NULL && strcmp(s->studenti[i].nume, valoare_filtru2) == 0) {
                    conditie_ok2 = 1;
                }
            }
            if (strstr(camp_filtru2, "an_studiu") != NULL) {
                int valoare_int = atoi(valoare_filtru2);
                if ((strstr(operator_filtru2, ">") != NULL && s->studenti[i].an_studiu > valoare_int) ||
                (strstr(operator_filtru2, "<") != NULL && s->studenti[i].an_studiu < valoare_int) ||
                (strstr(operator_filtru2, "=") != NULL && s->studenti[i].an_studiu == valoare_int)) {
                    conditie_ok2 = 1;
                }
            }
              // Daca ambele conditii sunt indeplinite, afisez campul dorit din student
            if (conditie_ok1 && conditie_ok2) {
                for (int j = 0; j < nr_campuri; j++) {
                    if (strstr(camp[j], "id") != NULL) printf("%d", s->studenti[i].id);
                    if (strstr(camp[j], "nume") != NULL) printf("%s", s->studenti[i].nume);
                    if (strstr(camp[j], "an_studiu") != NULL) printf("%d", s->studenti[i].an_studiu);
                    if (strstr(camp[j], "statut") != NULL) printf("%c", s->studenti[i].statut);
                    if (strstr(camp[j], "medie_generala") != NULL) printf("%.2f", s->studenti[i].medie_generala);
                    if (strstr(camp[j], "*") != NULL) {
                        printf("%d %s %d %c %.2f", s->studenti[i].id, s->studenti[i].nume,
                        s->studenti[i].an_studiu, s->studenti[i].statut, s->studenti[i].medie_generala);
                    }
                    if (nr_campuri > j+1) {  // Daca nu suntem la ultimul camp, afisez un spatiu dupa el
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }
    } else if (strstr(tabel, "materii") != NULL) {
        for (int i = 0; i < s->nr_materii; i++) {
            int conditie_ok1 = 0, conditie_ok2 = 0;

            if (strstr(camp_filtru1, "id") != NULL) {
                int valoare_int = atoi(valoare_filtru1);
                if ((strstr(operator_filtru1, "=") != NULL && s->materii[i].id == valoare_int)) {
                    conditie_ok1 = 1;
                }
            }
            if (strstr(camp_filtru2, "nume_titular") != NULL) {
                if ((strstr(operator_filtru2, "=") != NULL &&
                strcmp(s->materii[i].nume_titular, valoare_filtru2) == 0)) {
                    conditie_ok2 = 1;
                }
            }

            if (conditie_ok1 && conditie_ok2) {
                for (int j = 0; j < nr_campuri; j++) {
                    if (strstr(camp[j], "id") != NULL) printf("%d", s->materii[i].id);
                    if (strstr(camp[j], "nume") != NULL) printf("%s", s->materii[i].nume);
                    if (strstr(camp[j], "nume_titular") != NULL) printf("%s", s->materii[i].nume_titular);
                    if (strstr(camp[j], "*") != NULL) {
                        printf("%d %s %s", s->materii[i].id, s->materii[i].nume, s->materii[i].nume_titular);
                    }
                    if (nr_campuri > j+1) {
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }
    } else if (strstr(tabel, "inrolari") != NULL) {
        for (int i = 0; i < s->nr_inrolari; i++) {
            int conditie_ok1 = 0, conditie_ok2 = 0;

            if (strstr(camp_filtru1, "id_student") != NULL) {
                int valoare_int = atoi(valoare_filtru1);
                if ((strstr(operator_filtru1, "=") != NULL && s->inrolari[i].id_student == valoare_int)) {
                    conditie_ok1 = 1;
                }
            }
            if (strstr(camp_filtru2, "id_materie") != NULL) {
                int valoare_int = atoi(valoare_filtru2);
                if ((strstr(operator_filtru2, "=") != NULL && s->inrolari[i].id_materie == valoare_int)) {
                    conditie_ok2 = 1;
                }
            }
            if (strstr(camp_filtru2, "id_student") != NULL) {
                int valoare_int = atoi(valoare_filtru1);
                if ((strstr(operator_filtru1, "=") != NULL && s->inrolari[i].id_student == valoare_int)) {
                    conditie_ok2 = 1;
                }
            }
            if (strstr(camp_filtru1, "id_materie") != NULL) {
                int valoare_int = atoi(valoare_filtru2);
                if ((strstr(operator_filtru2, "=") != NULL && s->inrolari[i].id_materie == valoare_int)) {
                    conditie_ok1 = 1;
                }
            }
            if (conditie_ok1 && conditie_ok2) {
                for (int j = 0; j < nr_campuri; j++) {
                    if (strstr(camp[j], "id_student") != NULL) printf("%d ", s->inrolari[i].id_student);
                    if (strstr(camp[j], "id_materie") != NULL) printf("%d ", s->inrolari[i].id_materie);
                    if (strstr(camp[j], "note") != NULL) {
                        for (int k = 0; k < NUMBER_OF_GRADES; k++) {
                            printf("%.2f", s->inrolari[i].note[k]);
                            if (k < NUMBER_OF_GRADES - 1) {
                                printf(" ");
                            }
                        }
                    }
                    if (strstr(camp[j], "*") != NULL) {  // Afisez toate campurile
                        printf("%d %d ", s->inrolari[i].id_student, s->inrolari[i].id_materie);
                        for (int k = 0; k < NUMBER_OF_GRADES; k++) {
                            printf("%.2f", s->inrolari[i].note[k]);
                            if (k < NUMBER_OF_GRADES - 1) {
                                printf(" ");
                            }
                        }
                    }
                    if (nr_campuri > j + 1) {  // Daca nu suntem la ultimul camp, afisez un spatiu dupa el
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }
    }

    for (int i = 0; i < nr_campuri; i++) {
        free(camp[i]);
    }
      // Eliberez memoria alocata
    free(camp);
    free(campuri_copie);
    free(camp_filtru1);
    free(camp_filtru2);
    free(operator_filtru1);
    free(operator_filtru2);
    free(valoare_filtru1);
    free(valoare_filtru2);
}
  // Functia de update cu o singura conditie
void update_function(secretariat *s, const char *tabel, const char *camp, const char *conditie) {
    char *camp_set = malloc(MAX_LINE * sizeof(char));
    char *op_set = malloc(MAX_OPERATOR * sizeof(char));
    char *valoare_set = malloc(MAX_VALOARE * sizeof(char));
    char *camp_cond = malloc(MAX_CAMP_FILTRU * sizeof(char));
    char *op_cond = malloc(MAX_OPERATOR * sizeof(char));
    char *valoare_cond = malloc(MAX_VALOARE * sizeof(char));
    float *note1 = malloc(NUMBER_OF_GRADES * sizeof(float));
    if (strstr(camp, "nume") != NULL) {
          // daca se include nume citesc direct in string
        sscanf(camp, "%s %s  \"%[^\"]\"", camp_set, op_set, valoare_set);
    } else if (strstr(camp, "note") != NULL) {
          // daca se include note citesc direct in float fiecare nota
        sscanf(camp, "%s %s %f %f %f", camp_set, op_set, &note1[0], &note1[1], &note1[2]);
    } else {
        sscanf(camp, "%s %s %s", camp_set, op_set, valoare_set);
    }
    sscanf(conditie, "%s %s %s", camp_cond, op_cond, valoare_cond);
    if (strstr(tabel, "studenti")) {
        for (int i = 0; i < s->nr_studenti; i++) {
            int conditie_ok = 0;

            if (strcmp(camp_cond, "id") == 0) {
                int id_conditie = atoi(valoare_cond);
                if ((strcmp(op_cond, "=") == 0 && s->studenti[i].id == id_conditie) ||
                    (strcmp(op_cond, "<") == 0 && s->studenti[i].id < id_conditie) ||
                    (strcmp(op_cond, ">") == 0 && s->studenti[i].id > id_conditie) ||
                    (strcmp(op_cond, "<=") == 0 && s->studenti[i].id <= id_conditie) ||
                    (strcmp(op_cond, ">=") == 0 && s->studenti[i].id >= id_conditie)) {
                    conditie_ok = 1;
                }
            } else if (strcmp(camp_cond, "an_studiu") == 0) {
                int an_studiu_conditie = atoi(valoare_cond);
                if ((strcmp(op_cond, "=") == 0 && s->studenti[i].an_studiu == an_studiu_conditie) ||
                    (strcmp(op_cond, "<") == 0 && s->studenti[i].an_studiu < an_studiu_conditie) ||
                    (strcmp(op_cond, ">") == 0 && s->studenti[i].an_studiu > an_studiu_conditie) ||
                    (strcmp(op_cond, "<=") == 0 && s->studenti[i].an_studiu <= an_studiu_conditie) ||
                    (strcmp(op_cond, ">=") == 0 && s->studenti[i].an_studiu >= an_studiu_conditie)) {
                    conditie_ok = 1;
                }
            } else if (strcmp(camp_cond, "medie_generala") == 0) {
                float medie_conditie = (float)atof(valoare_cond);
                if ((strcmp(op_cond, "=") == 0 && s->studenti[i].medie_generala == medie_conditie) ||
                    (strcmp(op_cond, "<") == 0 && s->studenti[i].medie_generala < medie_conditie) ||
                    (strcmp(op_cond, ">") == 0 && s->studenti[i].medie_generala > medie_conditie) ||
                    (strcmp(op_cond, "<=") == 0 && s->studenti[i].medie_generala <= medie_conditie) ||
                    (strcmp(op_cond, ">=") == 0 && s->studenti[i].medie_generala >= medie_conditie)) {
                    conditie_ok = 1;
                }
            } else if (strcmp(camp_cond, "statut") == 0) {
                char statut_conditie = valoare_cond[0];
                if (strcmp(op_cond, "=") == 0 && s->studenti[i].statut == statut_conditie) {
                    conditie_ok = 1;
                }
            } else if (strcmp(camp_cond, "nume") == 0) {
                if (strcmp(op_cond, "=") == 0 && strstr(s->studenti[i].nume, valoare_cond) != NULL) {
                    conditie_ok = 1;
                }
            }
            if (conditie_ok) {
                if (strcmp(camp_set, "id") == 0 && strcmp(op_set, "=") == 0) {
                    s->studenti[i].id = atoi(valoare_set);
                } else if (strcmp(camp_set, "medie_generala") == 0 && strcmp(op_set, "=") == 0) {
                    s->studenti[i].medie_generala = (float)atof(valoare_set);
                } else if (strcmp(camp_set, "statut") == 0 && strcmp(op_set, "=") == 0) {
                    s->studenti[i].statut = valoare_set[0];
                } else if (strcmp(camp_set, "an_studiu") == 0 && strcmp(op_set, "=") == 0) {
                    s->studenti[i].an_studiu = atoi(valoare_set);
                } else if (strcmp(camp_set, "nume") == 0 && strcmp(op_set, "=") == 0) {
                    snprintf(s->studenti[i].nume, MAX_LINE, "%s", valoare_set);
                }
            }
        }
    } else if (strstr(tabel, "materii")) {
        for (int i = 0; i < s->nr_materii; i++) {
            int conditie_ok = 0;
            if (strcmp(camp_cond, "id") == 0) {
                int id_conditie = atoi(valoare_cond);
                if ((strcmp(op_cond, "=") == 0 && s->materii[i].id == id_conditie) ||
                    (strcmp(op_cond, "<") == 0 && s->materii[i].id < id_conditie) ||
                    (strcmp(op_cond, ">") == 0 && s->materii[i].id > id_conditie) ||
                    (strcmp(op_cond, "<=") == 0 && s->materii[i].id <= id_conditie) ||
                    (strcmp(op_cond, ">=") == 0 && s->materii[i].id >= id_conditie)) {
                    conditie_ok = 1;
                }
            }
            if (conditie_ok) {
                if (strcmp(camp_set, "id") == 0 && strcmp(op_set, "=") == 0) {
                    s->materii[i].id = atoi(valoare_set);
                } else if (strcmp(camp_set, "nume") == 0 && strcmp(op_set, "=") == 0) {
                    free(s->materii[i].nume);
                    s->materii[i].nume = strdup(valoare_set);
                } else if (strcmp(camp_set, "nume_titular") == 0 && strcmp(op_set, "=") == 0) {
                    free(s->materii[i].nume_titular);
                    s->materii[i].nume_titular = strdup(valoare_set);
                }
            }
        }
    } else if (strstr(tabel, "inrolari")) {
        for (int i = 0; i < s->nr_inrolari; i++) {
            int conditie_ok = 0;
            if (strcmp(camp_cond, "id_student") == 0) {
                int id_student_conditie = atoi(valoare_cond);
                if ((strcmp(op_cond, "=") == 0 && s->inrolari[i].id_student == id_student_conditie) ||
                    (strcmp(op_cond, "<") == 0 && s->inrolari[i].id_student < id_student_conditie) ||
                    (strcmp(op_cond, ">") == 0 && s->inrolari[i].id_student > id_student_conditie) ||
                    (strcmp(op_cond, "<=") == 0 && s->inrolari[i].id_student <= id_student_conditie) ||
                    (strcmp(op_cond, ">=") == 0 && s->inrolari[i].id_student >= id_student_conditie)) {
                    conditie_ok = 1;
                }
            }
            if (strcmp(camp_cond, "id_materie") == 0) {
                int id_materie_conditie = atoi(valoare_cond);
                if ((strcmp(op_cond, "=") == 0 && s->inrolari[i].id_materie == id_materie_conditie) ||
                    (strcmp(op_cond, "<") == 0 && s->inrolari[i].id_materie < id_materie_conditie) ||
                    (strcmp(op_cond, ">") == 0 && s->inrolari[i].id_materie > id_materie_conditie) ||
                    (strcmp(op_cond, "<=") == 0 && s->inrolari[i].id_materie <= id_materie_conditie) ||
                    (strcmp(op_cond, ">=") == 0 && s->inrolari[i].id_materie >= id_materie_conditie)) {
                    conditie_ok = 1;
                }
            }
            if (conditie_ok) {
                if (strcmp(camp_set, "id_student") == 0 && strcmp(op_set, "=") == 0) {
                    s->inrolari[i].id_student = atoi(valoare_set);
                } else if (strcmp(camp_set, "id_materie") == 0 && strcmp(op_set, "=") == 0) {
                    s->inrolari[i].id_materie = atoi(valoare_set);
                } else if (strcmp(camp_set, "note") == 0 && strcmp(op_set, "=") == 0) {  // schimb notele cerute
                    s->inrolari[i].note[0] = note1[0];
                    s->inrolari[i].note[1] = note1[1];
                    s->inrolari[i].note[2] = note1[2];
                    for (int k = 0; k < s->nr_studenti; k++) {  // calculez media generala
                        float suma = 0.0f;
                        int nr_mat = 0;
                        for (int j = 0; j < s->nr_inrolari; j++) {
                            if (s->inrolari[j].id_student == s->studenti[k].id) {
                                suma += s->inrolari[j].note[0] + s->inrolari[j].note[1] + s->inrolari[j].note[2];
                                nr_mat++;
                            }
                        }
                        if (nr_mat > 0) {
                            int rond = (int)((suma / (float)nr_mat) * DECIMAL_PRECISION + EPSILON);
                            s->studenti[k].medie_generala = ((float)rond / DECIMAL_PRECISION);
                        } else {
                            s->studenti[k].medie_generala = 0.0f;
                        }
                    }
                }
            }
        }
    }
    free(camp_set);
    free(op_set);
    free(valoare_set);
    free(camp_cond);
    free(op_cond);
    free(valoare_cond);
    free(note1);
}
  // functie de update cu 2 conditii
void update_function1(secretariat *s, const char *tabel, const char *camp,
const char *conditie1, const char *conditie2) {
    char *camp_set = malloc(MAX_CAMP_FILTRU * sizeof(char));
    char *op_set = malloc(MAX_OPERATOR * sizeof(char));
    char *valoare_set = malloc(MAX_VALOARE * sizeof(char));
    char *camp_cond1 = malloc(MAX_CAMP_FILTRU * sizeof(char));
    char *op_cond1 = malloc(MAX_OPERATOR * sizeof(char));
    char *valoare_cond1 = malloc(MAX_VALOARE * sizeof(char));
    char *camp_cond2 = malloc(MAX_CAMP_FILTRU * sizeof(char));
    char *op_cond2 = malloc(MAX_OPERATOR * sizeof(char));
    char *valoare_cond2 = malloc(MAX_VALORI_FILTRU * sizeof(char));
    float *note1 = calloc(NUMBER_OF_GRADES, sizeof(float));
    if (strstr(camp, "nume") != NULL) {
          // citesc numele direct cum am nevoie
        sscanf(camp, "%s %s  \"%[^\"]\"", camp_set, op_set, valoare_set);
    } else if (strstr(camp, "note") != NULL) {
          // citesc notele direct cum am nevoie
        sscanf(camp, "%s %s %f %f %f", camp_set, op_set, &note1[0], &note1[1], &note1[2]);
    } else {
        sscanf(camp, "%s %s %s", camp_set, op_set, valoare_set);
    }
    sscanf(conditie1, "%s %s %s", camp_cond1, op_cond1, valoare_cond1);  // citesc conditia 1
    sscanf(conditie2, "%s %s %s", camp_cond2, op_cond2, valoare_cond2);  // citesc conditia 2
    if (strstr(tabel, "studenti")) {  // daca tabelul este studenti
        for (int i = 0; i < s->nr_studenti; i++) {
            int conditie_ok1 = 0;
            int conditie_ok2 = 0;
            if (strstr(camp_cond1, "id")) {
                int id_conditie = atoi(valoare_cond1);
                if ((strcmp(op_cond1, "=") == 0 && s->studenti[i].id == id_conditie) ||
                    (strcmp(op_cond1, "<") == 0 && s->studenti[i].id < id_conditie) ||
                    (strcmp(op_cond1, ">") == 0 && s->studenti[i].id > id_conditie) ||
                    (strcmp(op_cond1, "<=") == 0 && s->studenti[i].id <= id_conditie) ||
                    (strcmp(op_cond1, ">=") == 0 && s->studenti[i].id >= id_conditie)) {
                    conditie_ok1 = 1;
                }
            } else if (strstr(camp_cond1, "an_studiu")) {  // daca conditia 1 este an_studiu
                int an_studiu_conditie = atoi(valoare_cond1);  // convertesc valoarea conditiei 1 in int
                if ((strcmp(op_cond1, "=") == 0 && s->studenti[i].an_studiu == an_studiu_conditie) ||
                    (strcmp(op_cond1, "<") == 0 && s->studenti[i].an_studiu < an_studiu_conditie) ||
                    (strcmp(op_cond1, ">") == 0 && s->studenti[i].an_studiu > an_studiu_conditie) ||
                    (strcmp(op_cond1, "<=") == 0 && s->studenti[i].an_studiu <= an_studiu_conditie) ||
                    (strcmp(op_cond1, ">=") == 0 && s->studenti[i].an_studiu >= an_studiu_conditie)) {
                    conditie_ok1 = 1;
                }
            } else if (strstr(camp_cond1, "medie_generala")) {
                float medie_conditie = (float)atof(valoare_cond1);  // convertesc valoarea conditiei 1 la float
                if ((strcmp(op_cond1, "=") == 0 && s->studenti[i].medie_generala == medie_conditie) ||
                    (strcmp(op_cond1, "<") == 0 && s->studenti[i].medie_generala < medie_conditie) ||
                    (strcmp(op_cond1, ">") == 0 && s->studenti[i].medie_generala > medie_conditie) ||
                    (strcmp(op_cond1, "<=") == 0 && s->studenti[i].medie_generala <= medie_conditie) ||
                    (strcmp(op_cond1, ">=") == 0 && s->studenti[i].medie_generala >= medie_conditie)) {
                    conditie_ok1 = 1;
                }
            } else if (strstr(camp_cond1, "statut")) {
                char statut_conditie = valoare_cond1[0];
                if (strcmp(op_cond1, "=") == 0 && s->studenti[i].statut == statut_conditie) {
                    conditie_ok1 = 1;
                }
            }
            if (strstr(camp_cond2, "id")) {
                int id_conditie = atoi(valoare_cond2);  // convertesc valoarea conditiei 2 in int
                if ((strcmp(op_cond2, "=") == 0 && s->studenti[i].id == id_conditie) ||
                    (strcmp(op_cond2, "<") == 0 && s->studenti[i].id < id_conditie) ||
                    (strcmp(op_cond2, ">") == 0 && s->studenti[i].id > id_conditie) ||
                    (strcmp(op_cond2, "<=") == 0 && s->studenti[i].id <= id_conditie) ||
                    (strcmp(op_cond2, ">=") == 0 && s->studenti[i].id >= id_conditie)) {
                    conditie_ok2 = 1;
                }
            } else if (strstr(camp_cond2, "an_studiu")) {  // daca conditia 2 este an_studiu
                int an_studiu_conditie = atoi(valoare_cond2);
                if ((strcmp(op_cond2, "=") == 0 && s->studenti[i].an_studiu == an_studiu_conditie) ||
                    (strcmp(op_cond2, "<") == 0 && s->studenti[i].an_studiu < an_studiu_conditie) ||
                    (strcmp(op_cond2, ">") == 0 && s->studenti[i].an_studiu > an_studiu_conditie) ||
                    (strcmp(op_cond2, "<=") == 0 && s->studenti[i].an_studiu <= an_studiu_conditie) ||
                    (strcmp(op_cond2, ">=") == 0 && s->studenti[i].an_studiu >= an_studiu_conditie)) {
                    conditie_ok2 = 1;
                }
            } else if (strstr(camp_cond2, "medie_generala")) {
                float medie_conditie = (float)atof(valoare_cond2);  // convertesc valoarea conditiei 2 la float
                if ((strcmp(op_cond2, "=") == 0 && s->studenti[i].medie_generala == medie_conditie) ||
                    (strcmp(op_cond2, "<") == 0 && s->studenti[i].medie_generala < medie_conditie) ||
                    (strcmp(op_cond2, ">") == 0 && s->studenti[i].medie_generala > medie_conditie) ||
                    (strcmp(op_cond2, "<=") == 0 && s->studenti[i].medie_generala <= medie_conditie) ||
                    (strcmp(op_cond2, ">=") == 0 && s->studenti[i].medie_generala >= medie_conditie)) {
                    conditie_ok2 = 1;
                }
            } else if (strstr(camp_cond2, "statut")) {
                char statut_conditie = valoare_cond2[0];
                if (strcmp(op_cond2, "=") == 0 && s->studenti[i].statut == statut_conditie) {
                    conditie_ok2 = 1;
                }
            }
            if (conditie_ok1 && conditie_ok2) {  // daca ambele conditii sunt satisfacute schimb datele cerute
                if (strstr(camp_set, "medie_generala") && strcmp(op_set, "=") == 0) {
                    s->studenti[i].medie_generala = (float)atof(valoare_set);
                } else if (strstr(camp_set, "statut") && strcmp(op_set, "=") == 0) {
                    s->studenti[i].statut = valoare_set[0];
                } else if (strstr(camp_set, "an_studiu") && strcmp(op_set, "=") == 0) {
                    s->studenti[i].an_studiu = atoi(valoare_set);
                } else if (strstr(camp_set, "id") && strcmp(op_set, "=") == 0) {
                    s->studenti[i].id = atoi(valoare_set);
                }
            }
        }
    }
    if (strstr(tabel, "materii") == 0) {  // daca tabelul este materii
        for (int i = 0; i < s->nr_materii; i++) {
            int conditie_ok1 = 0;
            int conditie_ok2 = 0;
            if (strstr(camp_cond1, "id")) {
                int id_conditie = atoi(valoare_cond1);
                if ((strcmp(op_cond1, "=") == 0 && s->materii[i].id == id_conditie) ||
                    (strcmp(op_cond1, "<") == 0 && s->materii[i].id < id_conditie) ||
                    (strcmp(op_cond1, ">") == 0 && s->materii[i].id > id_conditie) ||
                    (strcmp(op_cond1, "<=") == 0 && s->materii[i].id <= id_conditie) ||
                    (strcmp(op_cond1, ">=") == 0 && s->materii[i].id >= id_conditie)) {
                    conditie_ok1 = 1;
                }
            }
            if (strstr(camp_cond2, "id")) {
                int id_conditie = atoi(valoare_cond2);
                if ((strcmp(op_cond2, "=") == 0 && s->materii[i].id == id_conditie) ||
                    (strcmp(op_cond2, "<") == 0 && s->materii[i].id < id_conditie) ||
                    (strcmp(op_cond2, ">") == 0 && s->materii[i].id > id_conditie) ||
                    (strcmp(op_cond2, "<=") == 0 && s->materii[i].id <= id_conditie) ||
                    (strcmp(op_cond2, ">=") == 0 && s->materii[i].id >= id_conditie)) {
                    conditie_ok2 = 1;
                }
            }
            if (conditie_ok1 && conditie_ok2) {
                if (strcmp(camp_set, "nume") == 0 && strcmp(op_set, "=") == 0) {
                    free(s->materii[i].nume);
                    s->materii[i].nume = strdup(valoare_set);
                } else if (strcmp(camp_set, "nume_titular") == 0 && strcmp(op_set, "=") == 0) {
                    free(s->materii[i].nume_titular);
                    s->materii[i].nume_titular = strdup(valoare_set);
                }
            }
        }
    }
    if (strstr(tabel, "inrolari")) {  // daca tabelul este inrolari
        for (int i = 0; i < s->nr_inrolari; i++) {
            int conditie_ok1 = 0;
            int conditie_ok2 = 0;
            if (strstr(camp_cond1, "id_student")) {
                int id_student_conditie = atoi(valoare_cond1);
                if ((strcmp(op_cond1, "=") == 0 && s->inrolari[i].id_student == id_student_conditie) ||
                    (strcmp(op_cond1, "<") == 0 && s->inrolari[i].id_student < id_student_conditie) ||
                    (strcmp(op_cond1, ">") == 0 && s->inrolari[i].id_student > id_student_conditie) ||
                    (strcmp(op_cond1, "<=") == 0 && s->inrolari[i].id_student <= id_student_conditie) ||
                    (strcmp(op_cond1, ">=") == 0 && s->inrolari[i].id_student >= id_student_conditie)) {
                    conditie_ok1 = 1;
                }
                }
            if (strstr(camp_cond2, "id_student")) {
                int id_student_conditie = atoi(valoare_cond2);
                if ((strcmp(op_cond2, "=") == 0 && s->inrolari[i].id_student == id_student_conditie) ||
                    (strcmp(op_cond2, "<") == 0 && s->inrolari[i].id_student < id_student_conditie) ||
                    (strcmp(op_cond2, ">") == 0 && s->inrolari[i].id_student > id_student_conditie) ||
                    (strcmp(op_cond2, "<=") == 0 && s->inrolari[i].id_student <= id_student_conditie) ||
                    (strcmp(op_cond2, ">=") == 0 && s->inrolari[i].id_student >= id_student_conditie)) {
                    conditie_ok2 = 1;
                }
            }
            if (strstr(camp_cond1, "id_materie")) {
                int id_materie_conditie = atoi(valoare_cond1);
                if ((strcmp(op_cond1, "=") == 0 && s->inrolari[i].id_materie == id_materie_conditie) ||
                    (strcmp(op_cond1, "<") == 0 && s->inrolari[i].id_materie < id_materie_conditie) ||
                    (strcmp(op_cond1, ">") == 0 && s->inrolari[i].id_materie > id_materie_conditie) ||
                    (strcmp(op_cond1, "<=") == 0 && s->inrolari[i].id_materie <= id_materie_conditie) ||
                    (strcmp(op_cond1, ">=") == 0 && s->inrolari[i].id_materie >= id_materie_conditie)) {
                    conditie_ok1 = 1;
                }
            }
            if (strstr(camp_cond2, "id_materie")) {
                int id_materie_conditie = atoi(valoare_cond2);
                if ((strcmp(op_cond2, "=") == 0 && s->inrolari[i].id_materie == id_materie_conditie) ||
                    (strcmp(op_cond2, "<") == 0 && s->inrolari[i].id_materie < id_materie_conditie) ||
                    (strcmp(op_cond2, ">") == 0 && s->inrolari[i].id_materie > id_materie_conditie) ||
                    (strcmp(op_cond2, "<=") == 0 && s->inrolari[i].id_materie <= id_materie_conditie) ||
                    (strcmp(op_cond2, ">=") == 0 && s->inrolari[i].id_materie >= id_materie_conditie)) {
                    conditie_ok2 = 1;
                }
            }
            if (conditie_ok1 && conditie_ok2) {  // daca conditiile sunt indeplinite
                if (strstr(camp_set, "note") && strcmp(op_set, "=") == 0) {
                    s->inrolari[i].note[0] = note1[0];
                    s->inrolari[i].note[1] = note1[1];
                    s->inrolari[i].note[2] = note1[2];
                    for (int k = 0; k < s->nr_studenti; k++) {  // actualizam media generala pentru student
                        float suma = 0.0f;
                        int nr_mat = 0;
                        for (int j = 0; j < s->nr_inrolari; j++) {
                            if (s->inrolari[j].id_student == s->studenti[k].id) {
                                suma += s->inrolari[j].note[0] + s->inrolari[j].note[1] + s->inrolari[j].note[2];
                                nr_mat++;
                            }
                        }
                        if (nr_mat > 0) {
                            int rond = (int)((suma / (float)nr_mat) * DECIMAL_PRECISION + EPSILON);
                            s->studenti[k].medie_generala = ((float)rond / DECIMAL_PRECISION);
                        } else {
                            s->studenti[k].medie_generala = 0.0f;
                        }
                    }
                }
                if (strstr(camp_set, "id_student") && strcmp(op_set, "=") == 0) {
                    s->inrolari[i].id_student = atoi(valoare_set);
                }
                if (strstr(camp_set, "id_materie") && strcmp(op_set, "=") == 0) {
                    s->inrolari[i].id_materie = atoi(valoare_set);
                }
            }
        }
    }
    free(camp_set);
    free(op_set);
    free(valoare_set);
    free(camp_cond1);
    free(op_cond1);
    free(valoare_cond1);
    free(camp_cond2);
    free(op_cond2);
    free(valoare_cond2);
    free(note1);
}
  // functia de delete cu o singura conditie
void delete_function(secretariat *s, const char *tabel, const char *conditie) {
    char *camp_cond = malloc(MAX_CAMP_FILTRU * sizeof(char));
    char *op_cond = malloc(MAX_OPERATOR * sizeof(char));
    char *valoare_cond = malloc(MAX_VALOARE * sizeof(char));
      // citim campul, operatorul si valoarea conditiei
    sscanf(conditie, "%s %s %s", camp_cond, op_cond, valoare_cond);
    if (strstr(tabel, "studenti")) {
        for (int i = 0; i < s->nr_studenti; i++) {
            int conditie_ok = 0;
            if (strcmp(camp_cond, "id") == 0) {
                int id_cond = atoi(valoare_cond);  // convertim valoarea conditiei in int
                if ((strcmp(op_cond, "=") == 0 && s->studenti[i].id == id_cond) ||
                    (strcmp(op_cond, "<") == 0 && s->studenti[i].id < id_cond) ||
                    (strcmp(op_cond, ">") == 0 && s->studenti[i].id > id_cond) ||
                    (strcmp(op_cond, "<=") == 0 && s->studenti[i].id <= id_cond) ||
                    (strcmp(op_cond, ">=") == 0 && s->studenti[i].id >= id_cond)) {
                    conditie_ok = 1;
                }
            } else if (strcmp(camp_cond, "nume") == 0) {
                if (strcmp(op_cond, "=") == 0 && strcmp(s->studenti[i].nume, valoare_cond) == 0) {
                    conditie_ok = 1;
                }
            } else if (strcmp(camp_cond, "statut") == 0) {  // verificam daca campul este statut
                if (strcmp(op_cond, "=") == 0 && s->studenti[i].statut == valoare_cond[0]) {
                    conditie_ok = 1;
                }
            }
            if (conditie_ok) {
                for (int j = i; j < s->nr_studenti - 1; j++) {
                    s->studenti[j] = s->studenti[j + 1];
                }
                s->nr_studenti--;  // scadem numarul de studenti
                  // realocam memoria pentru studenti
                s->studenti = realloc(s->studenti, s->nr_studenti * sizeof(student));
                i--;
            }
        }
    } else if (strstr(tabel, "materii")) {  // verificam daca tabelul este materii
        for (int i = 0; i < s->nr_materii; i++) {
            int conditie_ok = 0;
            if (strcmp(camp_cond, "id") == 0) {
                int id_cond = atoi(valoare_cond);
                if ((strcmp(op_cond, "=") == 0 && s->materii[i].id == id_cond) ||
                    (strcmp(op_cond, "<") == 0 && s->materii[i].id < id_cond) ||
                    (strcmp(op_cond, ">") == 0 && s->materii[i].id > id_cond) ||
                    (strcmp(op_cond, "<=") == 0 && s->materii[i].id <= id_cond) ||
                    (strcmp(op_cond, ">=") == 0 && s->materii[i].id >= id_cond)) {
                    conditie_ok = 1;
                }
            } else if (strcmp(camp_cond, "nume") == 0) {
                if (strcmp(op_cond, "=") == 0 && strcmp(s->materii[i].nume, valoare_cond) == 0) {
                    conditie_ok = 1;
                }
            }
            if (conditie_ok) {
                free(s->materii[i].nume);
                free(s->materii[i].nume_titular);
                for (int j = i; j < s->nr_materii - 1; j++) {
                    s->materii[j] = s->materii[j + 1];
                }
                s->nr_materii--;
                s->materii = realloc(s->materii, s->nr_materii * sizeof(materie));
                i--;
            }
        }
    } else if (strstr(tabel, "inrolari")) {  // verificam daca tabelul este inrolari
        for (int i = 0; i < s->nr_inrolari; i++) {
            int conditie_ok = 0;
            if (strcmp(camp_cond, "id_student") == 0) {
                int id_student_cond = atoi(valoare_cond);
                if ((strcmp(op_cond, "=") == 0 && s->inrolari[i].id_student == id_student_cond) ||
                    (strcmp(op_cond, "<") == 0 && s->inrolari[i].id_student < id_student_cond) ||
                    (strcmp(op_cond, ">") == 0 && s->inrolari[i].id_student > id_student_cond) ||
                    (strcmp(op_cond, "<=") == 0 && s->inrolari[i].id_student <= id_student_cond) ||
                    (strcmp(op_cond, ">=") == 0 && s->inrolari[i].id_student >= id_student_cond)) {
                    conditie_ok = 1;
                }
            }
            if (strcmp(camp_cond, "id_materie") == 0) {
                int id_materie_cond = atoi(valoare_cond);
                if ((strcmp(op_cond, "=") == 0 && s->inrolari[i].id_materie == id_materie_cond) ||
                    (strcmp(op_cond, "<") == 0 && s->inrolari[i].id_materie < id_materie_cond) ||
                    (strcmp(op_cond, ">") == 0 && s->inrolari[i].id_materie > id_materie_cond) ||
                    (strcmp(op_cond, "<=") == 0 && s->inrolari[i].id_materie <= id_materie_cond) ||
                    (strcmp(op_cond, ">=") == 0 && s->inrolari[i].id_materie >= id_materie_cond)) {
                    conditie_ok = 1;
                }
            }
            if (conditie_ok) {
                for (int j = i; j < s->nr_inrolari - 1; j++) {
                    s->inrolari[j] = s->inrolari[j + 1];
                }
                s->nr_inrolari--;
                  // realocam memoria pentru inrolari
                s->inrolari = realloc(s->inrolari, s->nr_inrolari * sizeof(inrolare));
                i--;
            }
        }
    }
    for (int i = 0; i < s->nr_studenti; i++) {  // calculam media generala pentru fiecare student
        float suma = 0.0f;
        int nr_mat = 0;
        for (int j = 0; j < s->nr_inrolari; j++) {
            if (s->inrolari[j].id_student == s->studenti[i].id) {
                suma += s->inrolari[j].note[0] + s->inrolari[j].note[1] + s->inrolari[j].note[2];
                nr_mat++;
            }
        }
        if (nr_mat > 0) {
            int rond = (int)((suma / (float)nr_mat) * DECIMAL_PRECISION + EPSILON);
            s->studenti[i].medie_generala = ((float)rond / DECIMAL_PRECISION);
        } else {
            s->studenti[i].medie_generala = 0.0f;
        }
    }

    free(camp_cond);
    free(op_cond);
    free(valoare_cond);
}
  // functia de stergere cu doua conditii
void delete_function1(secretariat *s, const char *tabel, const char *conditie1, const char *conditie2) {
    char *camp_cond1 = malloc(MAX_CAMP_FILTRU * sizeof(char));
    char *op_cond1 = malloc(MAX_OPERATOR * sizeof(char));
    char *valoare_cond1 = malloc(MAX_VALORI_FILTRU * sizeof(char));
    char *camp_cond2 = malloc(MAX_CAMP_FILTRU * sizeof(char));
    char *op_cond2 = malloc(MAX_OPERATOR * sizeof(char));
    char *valoare_cond2 = malloc(MAX_VALORI_FILTRU * sizeof(char));
    sscanf(conditie1, "%s %s %s", camp_cond1, op_cond1, valoare_cond1);  // scaneaza conditia 1
    sscanf(conditie2, "%s %s %s", camp_cond2, op_cond2, valoare_cond2);  // scaneaza conditia 2
    if (strstr(tabel, "studenti")) {
        for (int i = 0; i < s->nr_studenti; i++) {
            int conditie_ok1 = 0;
            int conditie_ok2 = 0;
            if (strcmp(camp_cond1, "id") == 0) {
                int id_cond = atoi(valoare_cond1);
                if ((strcmp(op_cond1, "=") == 0 && s->studenti[i].id == id_cond) ||
                    (strcmp(op_cond1, "<") == 0 && s->studenti[i].id < id_cond) ||
                    (strcmp(op_cond1, ">") == 0 && s->studenti[i].id > id_cond) ||
                    (strcmp(op_cond1, "<=") == 0 && s->studenti[i].id <= id_cond) ||
                    (strcmp(op_cond1, ">=") == 0 && s->studenti[i].id >= id_cond)) {
                    conditie_ok1 = 1;
                }
            } else if (strcmp(camp_cond1, "nume") == 0) {
                if (strcmp(op_cond1, "=") == 0 && strcmp(s->studenti[i].nume, valoare_cond1) == 0) {
                    conditie_ok1 = 1;
                }
            } else if (strcmp(camp_cond1, "statut") == 0) {
                if (strcmp(op_cond1, "=") == 0 && s->studenti[i].statut == valoare_cond1[0]) {
                    conditie_ok1 = 1;
                }
            } else if (strcmp(camp_cond1, "an_studiu") == 0) {
                int an_studiu_cond = atoi(valoare_cond1);
                if ((strcmp(op_cond1, "=") == 0 && s->studenti[i].an_studiu == an_studiu_cond) ||
                    (strcmp(op_cond1, "<") == 0 && s->studenti[i].an_studiu < an_studiu_cond) ||
                    (strcmp(op_cond1, ">") == 0 && s->studenti[i].an_studiu > an_studiu_cond) ||
                    (strcmp(op_cond1, "<=") == 0 && s->studenti[i].an_studiu <= an_studiu_cond) ||
                    (strcmp(op_cond1, ">=") == 0 && s->studenti[i].an_studiu >= an_studiu_cond)) {
                    conditie_ok1 = 1;
                }
            } else if (strcmp(camp_cond1, "medie_generala") == 0) {
                float medie_generala_cond = (float)atof(valoare_cond1);
                if ((strcmp(op_cond1, "=") == 0 && s->studenti[i].medie_generala == medie_generala_cond) ||
                    (strcmp(op_cond1, "<") == 0 && s->studenti[i].medie_generala < medie_generala_cond) ||
                    (strcmp(op_cond1, ">") == 0 && s->studenti[i].medie_generala > medie_generala_cond) ||
                    (strcmp(op_cond1, "<=") == 0 && s->studenti[i].medie_generala <= medie_generala_cond) ||
                    (strcmp(op_cond1, ">=") == 0 && s->studenti[i].medie_generala >= medie_generala_cond)) {
                    conditie_ok1 = 1;
                }
            }
            if (strcmp(camp_cond1, "id") == 0) {
                int id_cond = atoi(valoare_cond2);
                if ((strcmp(op_cond2, "=") == 0 && s->studenti[i].id == id_cond) ||
                    (strcmp(op_cond2, "<") == 0 && s->studenti[i].id < id_cond) ||
                    (strcmp(op_cond2, ">") == 0 && s->studenti[i].id > id_cond) ||
                    (strcmp(op_cond2, "<=") == 0 && s->studenti[i].id <= id_cond) ||
                    (strcmp(op_cond2, ">=") == 0 && s->studenti[i].id >= id_cond)) {
                    conditie_ok2 = 1;
                }
            } else if (strcmp(camp_cond2, "nume") == 0) {
                if (strcmp(op_cond2, "=") == 0 && strcmp(s->studenti[i].nume, valoare_cond2) == 0) {
                    conditie_ok2 = 1;
                }
            } else if (strcmp(camp_cond2, "statut") == 0) {
                if (strcmp(op_cond2, "=") == 0 && s->studenti[i].statut == valoare_cond2[0]) {
                    conditie_ok2 = 1;
                }
            } else if (strcmp(camp_cond2, "an_studiu") == 0) {
                int an_studiu_cond = atoi(valoare_cond2);
                if ((strcmp(op_cond2, "=") == 0 && s->studenti[i].an_studiu == an_studiu_cond) ||
                    (strcmp(op_cond2, "<") == 0 && s->studenti[i].an_studiu < an_studiu_cond) ||
                    (strcmp(op_cond2, ">") == 0 && s->studenti[i].an_studiu > an_studiu_cond) ||
                    (strcmp(op_cond2, "<=") == 0 && s->studenti[i].an_studiu <= an_studiu_cond) ||
                    (strcmp(op_cond2, ">=") == 0 && s->studenti[i].an_studiu >= an_studiu_cond)) {
                    conditie_ok2 = 1;
                }
            } else if (strcmp(camp_cond2, "medie_generala") == 0) {
                float medie_generala_cond = (float)atof(valoare_cond2);
                if ((strcmp(op_cond2, "=") == 0 && s->studenti[i].medie_generala == medie_generala_cond) ||
                    (strcmp(op_cond2, "<") == 0 && s->studenti[i].medie_generala < medie_generala_cond) ||
                    (strcmp(op_cond2, ">") == 0 && s->studenti[i].medie_generala > medie_generala_cond) ||
                    (strcmp(op_cond2, "<=") == 0 && s->studenti[i].medie_generala <= medie_generala_cond) ||
                    (strcmp(op_cond2, ">=") == 0 && s->studenti[i].medie_generala >= medie_generala_cond)) {
                    conditie_ok2 = 1;
                }
            }
            if (conditie_ok1 && conditie_ok2) {
                  // Dacă ambele condiții sunt îndeplinite, stergem studentul
                for (int j = i; j < s->nr_studenti - 1; j++) {
                    s->studenti[j] = s->studenti[j + 1];
                }
                s->nr_studenti--;
                s->studenti = realloc(s->studenti, s->nr_studenti * sizeof(student));
                i--;
            }
        }
    } else if (strstr(tabel, "materii")) {
        for (int i = 0; i < s->nr_materii; i++) {
            int conditie_ok1 = 0;
            int conditie_ok2 = 0;
            if (strcmp(camp_cond1, "id") == 0) {
                int id_cond = atoi(valoare_cond1);
                if ((strcmp(op_cond1, "=") == 0 && s->materii[i].id == id_cond) ||
                    (strcmp(op_cond1, "<") == 0 && s->materii[i].id < id_cond) ||
                    (strcmp(op_cond1, ">") == 0 && s->materii[i].id > id_cond) ||
                    (strcmp(op_cond1, "<=") == 0 && s->materii[i].id <= id_cond) ||
                    (strcmp(op_cond1, ">=") == 0 && s->materii[i].id >= id_cond)) {
                    conditie_ok1 = 1;
                }
            } else if (strcmp(camp_cond1, "nume") == 0) {
                if (strcmp(op_cond1, "=") == 0 && strcmp(s->materii[i].nume, valoare_cond1) == 0) {
                    conditie_ok1 = 1;
                }
            }
            if (strcmp(camp_cond2, "id") == 0) {
                int id_cond = atoi(valoare_cond1);
                if ((strcmp(op_cond2, "=") == 0 && s->materii[i].id == id_cond) ||
                    (strcmp(op_cond2, "<") == 0 && s->materii[i].id < id_cond) ||
                    (strcmp(op_cond2, ">") == 0 && s->materii[i].id > id_cond) ||
                    (strcmp(op_cond2, "<=") == 0 && s->materii[i].id <= id_cond) ||
                    (strcmp(op_cond2, ">=") == 0 && s->materii[i].id >= id_cond)) {
                    conditie_ok2 = 1;
                }
            } else if (strcmp(camp_cond2, "nume") == 0) {
                if (strcmp(op_cond2, "=") == 0 && strcmp(s->materii[i].nume, valoare_cond2) == 0) {
                    conditie_ok2 = 1;
                }
            }
            if (conditie_ok1 && conditie_ok2) {
                  // Dacă ambele condiții sunt îndeplinite, stergem materia
                free(s->materii[i].nume);
                free(s->materii[i].nume_titular);
                for (int j = i; j < s->nr_materii - 1; j++) {
                    s->materii[j] = s->materii[j + 1];
                }
                s->nr_materii--;
                s->materii = realloc(s->materii, s->nr_materii * sizeof(materie));
                i--;
            }
        }
    } else if (strstr(tabel, "inrolari")) {
        for (int i = 0; i < s->nr_inrolari; i++) {
            int conditie_ok1 = 0;
            int conditie_ok2 = 0;
            if (strcmp(camp_cond1, "id_student") == 0) {
                int id_student_cond = atoi(valoare_cond1);
                if ((strcmp(op_cond1, "=") == 0 && s->inrolari[i].id_student == id_student_cond) ||
                    (strcmp(op_cond1, "<") == 0 && s->inrolari[i].id_student < id_student_cond) ||
                    (strcmp(op_cond1, ">") == 0 && s->inrolari[i].id_student > id_student_cond) ||
                    (strcmp(op_cond1, "<=") == 0 && s->inrolari[i].id_student <= id_student_cond) ||
                    (strcmp(op_cond1, ">=") == 0 && s->inrolari[i].id_student >= id_student_cond)) {
                    conditie_ok1 = 1;
                }
            }
            if (strcmp(camp_cond1, "id_materie") == 0) {
                int id_materie_cond = atoi(valoare_cond1);
                if ((strcmp(op_cond1, "=") == 0 && s->inrolari[i].id_materie == id_materie_cond) ||
                    (strcmp(op_cond1, "<") == 0 && s->inrolari[i].id_materie < id_materie_cond) ||
                    (strcmp(op_cond1, ">") == 0 && s->inrolari[i].id_materie > id_materie_cond) ||
                    (strcmp(op_cond1, "<=") == 0 && s->inrolari[i].id_materie <= id_materie_cond) ||
                    (strcmp(op_cond1, ">=") == 0 && s->inrolari[i].id_materie >= id_materie_cond)) {
                    conditie_ok1 = 1;
                }
            }
            if (strcmp(camp_cond2, "id_student") == 0) {
                int id_student_cond = atoi(valoare_cond2);
                if ((strcmp(op_cond2, "=") == 0 && s->inrolari[i].id_student == id_student_cond) ||
                    (strcmp(op_cond2, "<") == 0 && s->inrolari[i].id_student < id_student_cond) ||
                    (strcmp(op_cond2, ">") == 0 && s->inrolari[i].id_student > id_student_cond) ||
                    (strcmp(op_cond2, "<=") == 0 && s->inrolari[i].id_student <= id_student_cond) ||
                    (strcmp(op_cond2, ">=") == 0 && s->inrolari[i].id_student >= id_student_cond)) {
                    conditie_ok2 = 1;
                }
            }
            if (strcmp(camp_cond2, "id_materie") == 0) {
                int id_materie_cond = atoi(valoare_cond2);
                if ((strcmp(op_cond2, "=") == 0 && s->inrolari[i].id_materie == id_materie_cond) ||
                    (strcmp(op_cond2, "<") == 0 && s->inrolari[i].id_materie < id_materie_cond) ||
                    (strcmp(op_cond2, ">") == 0 && s->inrolari[i].id_materie > id_materie_cond) ||
                    (strcmp(op_cond2, "<=") == 0 && s->inrolari[i].id_materie <= id_materie_cond) ||
                    (strcmp(op_cond2, ">=") == 0 && s->inrolari[i].id_materie >= id_materie_cond)) {
                    conditie_ok2 = 1;
                }
            }
            if (conditie_ok1 && conditie_ok2) {
                  // Dacă ambele condiții sunt îndeplinite, stergem înrolarea
                for (int j = i; j < s->nr_inrolari - 1; j++) {
                    s->inrolari[j] = s->inrolari[j + 1];
                }
                s->nr_inrolari--;
                s->inrolari = realloc(s->inrolari, s->nr_inrolari * sizeof(inrolare));
                i--;
            }
        }
    }
    for (int i = 0; i < s->nr_studenti; i++) {
        float suma = 0.0f;
        int nr_mat = 0;
        for (int j = 0; j < s->nr_inrolari; j++) {
            if (s->inrolari[j].id_student == s->studenti[i].id) {
                suma += s->inrolari[j].note[0] + s->inrolari[j].note[1] + s->inrolari[j].note[2];
                nr_mat++;
            }
        }
        if (nr_mat > 0) {
            int rond = (int)((suma / (float)nr_mat) * DECIMAL_PRECISION + EPSILON);
            s->studenti[i].medie_generala = ((float)rond / DECIMAL_PRECISION);
        } else {
            s->studenti[i].medie_generala = 0.0f;
        }
    }
  // eliberam memoria
    free(camp_cond1);
    free(op_cond1);
    free(valoare_cond1);
    free(camp_cond2);
    free(op_cond2);
    free(valoare_cond2);
}
  // functie de procesare a unei linii
void procesare_linie(secretariat *s, char *linie) {
    char *campuri = malloc(MAX_LINE * sizeof(char));
    char *tabel = malloc(MAX_LINE *sizeof(char));
    char *conditie = malloc(MAX_LINE *sizeof(char));
    char *conditie1 = malloc(MAX_LINE *sizeof(char));
    char *conditie2 = malloc(MAX_LINE *sizeof(char));
      // procesez fiecare linie si veridic ce fel de comanda are
    if (strstr(linie, "SELECT") !=NULL) {
        if (strstr(linie, " AND ")) {  // daca are and insemnca ca sunt 2 conditii
            sscanf(linie, "SELECT %[^F] FROM %[^W] WHERE %[^A] AND %[^;]", campuri, tabel, conditie, conditie1);
              // citesc linia si salvez datele cum am nevoie
            filtrare_complexa(s, campuri, tabel, conditie, conditie1);
        } else if (strstr(linie, " WHERE ")) {
              // daca are where fara and inseamna ca are o singura conditie
            sscanf(linie, "SELECT %[^F] FROM %[^W] WHERE %[^;]", campuri, tabel, conditie);
            interogare_filtrare(s, campuri, tabel, conditie);
        } else {
            sscanf(linie, "SELECT %[^F] FROM %[^;]", campuri, tabel);
              // daca nu are nici and nici where inseamna ca nu are conditii
            interogare_simpla(s, campuri, tabel);
        }
    } else if (strstr(linie, "UPDATE")!= NULL) {
        if (strstr(linie, " AND ")) {  // daca are and insemnca ca sunt 2 conditii
            sscanf(linie, "UPDATE %[^S] SET %[^W] WHERE %[^A] AND %[^;]", tabel, conditie, conditie1, conditie2);
            update_function1(s, tabel, conditie, conditie1, conditie2);
        } else {
            sscanf(linie, "UPDATE %[^S] SET %[^W] WHERE %[^;]", tabel, conditie, conditie1);
            update_function(s, tabel, conditie, conditie1);
        }
    } else if (strstr(linie, "DELETE")!= NULL) {
        if (strstr(linie, " AND ")) {
            sscanf(linie, "DELETE FROM %[^W] WHERE %[^A] AND %[^;]", tabel, conditie, conditie1);
            delete_function1(s, tabel, conditie, conditie1);
        } else {
            sscanf(linie, "DELETE FROM %[^W] WHERE %[^;]", tabel, conditie);
            delete_function(s, tabel, conditie);
        }
    }
    free(campuri);
    free(tabel);
    free(conditie);
    free(conditie1);
    free(conditie2);
}
int main(int argc, char *argv[]) {
    secretariat *s = citeste_secretariat(argv[1]);  // citesc secretariat
    int numar_comenzi = 0;
    char *linie = calloc(MAX_LINE, sizeof(char));
    scanf("%d\n", &numar_comenzi);
    for (int i = 0; i < numar_comenzi; i++) {  // citesc comenzile si le procesez
        fgets(linie, MAX_LINE, stdin);
        procesare_linie(s, linie);
    }
    free(linie);
    elibereaza_secretariat(&s);
    return 0;
}
