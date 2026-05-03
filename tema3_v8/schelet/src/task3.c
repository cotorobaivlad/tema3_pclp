#include "task3.h"
#define NUM_BLOCK 4
void imparte_blocuri(uint8_t **blocuri, uint8_t *octeti_studenti, size_t num_blocks, size_t lungime_bloc) {
    for (size_t i = 0; i < num_blocks; i++) {
        for (size_t j = 0; j < lungime_bloc; j++) {
            if (octeti_studenti[i * lungime_bloc + j]) {
                blocuri[i][j] = octeti_studenti[i * lungime_bloc + j];
            } else {
                blocuri[i][j] = 0x00;
            }
        }
    }
}
void xor_blocks(uint8_t *block, uint8_t *key, size_t len_key, size_t len_block) {
    for (size_t i = 0; i < len_block; i++) {
        block[i] ^= key[i % len_key];
    }
}
void p_box(uint8_t *block, size_t len_block) {
    uint8_t *temp = malloc(sizeof(uint8_t) * len_block);
    for (size_t i = 0; i < len_block; i++) {
        temp[(i * (len_block - 1) + 2) % len_block] = block[i];
    }
    memcpy(block, temp, len_block);
    free(temp);
}
void cripteaza_studenti(secretariat *secretariat, void *key, size_t key_len,
    void *iv, size_t iv_len, char *cale_output) {
    uint8_t *octeti_studenti = (uint8_t*)secretariat->studenti;
    size_t lungime = sizeof(student) * secretariat->nr_studenti;

    uint8_t *octeti_IV = (uint8_t*)iv;
    uint8_t *octeti_cheie = (uint8_t *)key;

    size_t lungime_bloc = 0;
    while (lungime % NUM_BLOCK) {
        lungime++;
    }
    lungime_bloc = lungime / NUM_BLOCK;
    uint8_t **blocuri = malloc(sizeof(uint8_t *) * NUM_BLOCK);
    for (size_t i = 0; i < NUM_BLOCK; i++) {
        blocuri[i] = malloc(sizeof(uint8_t) * lungime_bloc);
    }
    imparte_blocuri(blocuri, octeti_studenti, NUM_BLOCK, lungime_bloc);
      // Efectuam operatiile aparte pentru primul bloc si apoi restul
      // Primul bloc
    xor_blocks(blocuri[0], octeti_IV, iv_len, lungime_bloc);
    xor_blocks(blocuri[0], octeti_cheie, key_len, lungime_bloc);
    p_box(blocuri[0], lungime_bloc);
      // Restul blocurilor
    for (size_t i = 1; i < NUM_BLOCK; i++) {
        xor_blocks(blocuri[i], blocuri[i - 1], lungime_bloc, lungime_bloc);
        xor_blocks(blocuri[i], octeti_cheie, key_len, lungime_bloc);
        p_box(blocuri[i], lungime_bloc);
    }
    FILE *output = fopen(cale_output, "wb");
    for (size_t i = 0; i < NUM_BLOCK; i++) {
        fwrite(blocuri[i], lungime_bloc, 1, output);
    }
    fclose(output);
    for (size_t i = 0; i < NUM_BLOCK; i++) {
        free(blocuri[i]);
    }
    free(blocuri);
}
