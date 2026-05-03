# Tema 3 - Procesarea Matricelor și Transformări de Hartă (PCLP)

## Descriere
Acest proiect implementează o serie de algoritmi pentru manipularea și transformarea unor structuri de date bidimensionale (matrice de caractere). Obiectivul principal a fost gestionarea eficientă a memoriei dinamice și implementarea unor algoritmi de parcurgere și modificare a datelor în funcție de cerințe specifice.

---

## Detalii Implementare

### TASK 1 - Inițializarea Hărții și Alocarea Memoriei
În acest task, am pus bazele infrastructurii proiectului:
- **Alocare Dinamică:** Am implementat o funcție care alocă memorie pentru o matrice de tip `char **` (pointer la pointer), asigurând spațiul necesar pentru un grid de dimensiuni variabile ($rows \times cols$).
- **Inițializare:** Matricea este populată cu datele inițiale, pregătind terenul pentru transformările ulterioare. 
- **Validare:** Am inclus verificări pentru a mă asigura că alocarea a reușit, evitând dereferențierea pointerilor NULL.

### TASK 2 - Transformări Geometrice și Logice
Task-ul 2 se concentrează pe modificarea structurii hărții. Din implementare, am urmărit:
- **Parcurgerea Eficientă:** Utilizarea buclelor imbricate pentru a accesa și modifica elementele matricei în funcție de indici.
- **Manipularea Valorilor:** Aplicarea unor măști sau schimbarea stării elementelor din hartă pentru a reflecta o nouă configurație (ex: filtrare sau mapare de caractere).

### TASK 3 - Extragerea Informațiilor și Analiza
Acest task vizează interpretarea datelor din matricea procesată la pașii anteriori:
- **Căutare și Identificare:** Algoritmi care caută tipare specifice în interiorul hărții.
- **Sinteza Datelor:** Rezultatele sunt extrase pentru a genera output-ul final al programului.
- **Gestiunea Pointerilor:** Utilizarea pointerilor pentru a transmite și prelucra datele între diferite secțiuni ale programului fără a copia inutil memoria.

---

## Gestiunea Memoriei
Un aspect critic al acestei teme a fost prevenirea scurgerilor de memorie (**memory leaks**).
- Fiecare `malloc` are un corespondent `free`.
- Memoria este eliberată în ordine inversă alocării: întâi fiecare rând al matricei, apoi vectorul de pointeri principal.

## Instrucțiuni de Utilizare

### Compilare
Proiectul utilizează un `Makefile` pentru automatizarea procesului de build. Rulează următoarea comandă în terminal:
```bash
make
