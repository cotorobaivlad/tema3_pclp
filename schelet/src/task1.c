#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "task1.h"
#define DECIMAL_PRECISION 100.0f  // Precizia utilizată pentru rotunjirea mediilor
#define MAX_LINE_CHAR 256
#define MAX_NAME 40
#define MAX_ANTET 20
#define EPSILON 0.55555f
  // Funcția citește datele despre studenți, materii și înrolări dintr-un fișier
secretariat *citeste_secretariat(const char *nume_fisier) {
    FILE *file = fopen(nume_fisier, "r");  // Deschide fișierul pentru citire
    secretariat *s = (secretariat *)malloc(sizeof(secretariat));
    s->studenti = NULL;
    s->nr_studenti = 0;
    s->materii = NULL;
    s->nr_materii = 0;
    s->inrolari = NULL;
    s->nr_inrolari = 0;
    char linie[MAX_LINE_CHAR], antet[MAX_ANTET] = "";
    while (fgets(linie, sizeof(linie), file)) {  // Citește fiecare linie din fișier
        if (linie[0] == '[') {  // Dacă linia începe cu '[', este un antet de secțiune
            sscanf(linie, "[%[^]]", antet);  // Extrage numele secțiunii
        } else if (strcmp(antet, "STUDENTI") == 0) {  // Secțiunea STUDENTI
             // Realocă lista de studenți pentru a adăuga un nou element
            s->studenti = realloc(s->studenti, (s->nr_studenti + 1) * sizeof(student));
            student *stud = &s->studenti[s->nr_studenti++];
            sscanf(linie, "%d, %[^,], %d, %c", &stud->id, stud->nume, &stud->an_studiu, &stud->statut);
            stud->medie_generala = 0.0f;  // Inițializează media generală
        } else if (strcmp(antet, "MATERII") == 0) {  // Secțiunea MATERII
              // Realocă lista de materii pentru a adăuga un nou element
            s->materii = realloc(s->materii, (s->nr_materii + 1) * sizeof(materie));
            materie *mat = &s->materii[s->nr_materii++];
            mat->nume = malloc(MAX_NAME);
            mat->nume_titular = malloc(MAX_NAME);
            sscanf(linie, "%d, %[^,], %[^\n]", &mat->id, mat->nume, mat->nume_titular);
        } else if (strcmp(antet, "INROLARI") == 0) {  // Secțiunea INROLARI
             // Realocă lista de înrolări pentru a adăuga un nou element
            s->inrolari = realloc(s->inrolari, (s->nr_inrolari + 1) * sizeof(inrolare));
            inrolare *inr = &s->inrolari[s->nr_inrolari++];
            sscanf(linie, "%d, %d, %f %f %f", &inr->id_student,
            &inr->id_materie, &inr->note[0], &inr->note[1], &inr->note[2]);
        }
    }

     // Calculează media generală pentru fiecare student
    for (int i = 0; i < s->nr_studenti; i++) {
        float suma = 0.0f;  // Suma notelor
        int nr_mat = 0;  // Numărul de materii
        for (int j = 0; j < s->nr_inrolari; j++) {  // Parcurge toate înrolările
            if (s->inrolari[j].id_student == s->studenti[i].id) {  //  Dacă înrolarea aparține studentului curent
                suma += s->inrolari[j].note[0] + s->inrolari[j].note[1] + s->inrolari[j].note[2];
                nr_mat++;
            }
        }
        float medie_mat = suma / (float)nr_mat;  // Calculează media
        int rond = (int)(medie_mat * DECIMAL_PRECISION + EPSILON);  // Rotunjire
        s->studenti[i].medie_generala = ((float)rond / DECIMAL_PRECISION);  // Salvează media generală
    }

    fclose(file);
    return s;
}
  // Funcția adaugă un nou student în structura secretariat
void adauga_student(secretariat *s, int id, char *nume, int an_studiu, char statut, float medie_generala) {
    s->nr_studenti++;
    s->studenti = realloc(s->studenti, s->nr_studenti * sizeof(student));
    student stud;
    stud.id = id;
    strncpy(stud.nume, nume, MAX_NAME);
    stud.an_studiu = an_studiu;
    stud.statut = statut;
    stud.medie_generala = medie_generala;
    s->studenti[s->nr_studenti - 1] = stud;
}
  // Funcția eliberează memoria alocată pentru structura secretariat
void elibereaza_secretariat(secretariat **s) {
    if (!s || !*s) return;  // Verifică dacă structura este validă

     // Eliberează memoria pentru fiecare materie
    for (int i = 0; i < (*s)->nr_materii; i++) {
        free((*s)->materii[i].nume);
        free((*s)->materii[i].nume_titular);
    }
    free((*s)->studenti);
    free((*s)->materii);
    free((*s)->inrolari);
    free(*s);
    *s = NULL;
}
