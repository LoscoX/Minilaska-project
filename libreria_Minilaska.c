//
// Created by mfard on 09/01/2021.
//

#include <stdio.h>
#include <stdlib.h>

/*SPAZIO VALORI COSTANTI*/

/*valore celle vuote e inutilizzabili*/
char const VUOTO = 'f';
/*valore per le pedine del giocatore 1*/
char const GIOCATORE1 = 'a';
/*valore per le pedine del giocatore 2*/
char const GIOCATORE2 = 'b';
/*valore per le caselle del tabellone vuote */
char const NULLO = 'c';
/*valore di escape */
char const ESCAPE = 'd';
/*valore per il giocatore promosso*/
char const PROMOSSO = 'e';

/*SPAZIO DATA STRUCT*/

/* Data struct contenenti i valori del tabellone di gioco */
typedef struct tab{
    /* dimensione di un lato del tabellone quadrato */
    int dimensione;
    /*dimensione delle pedine nell'allocazione della memoria */
    int altezza_pedine;
    /*dimensione massima in gioco dell'altezza delle pedine */
    int altezza_pedine_max;
    /*tabellone di gioco */
    char* celle_tabellone;
} tab_t;

/* Data struct contenenti i valori delle impostazioni del menù di gioco */
typedef struct selezione_dati{
    /* dimensione del tabellone selezionata */
    int dimensione_selezionata;
    /* altezza del tabellone selezionata */
    int altezza_selezionata;
    /* profondità dellla cpu selezionata */
    int depth_cpu;
    /* selezione della modalità inversa */
    int tabellone_inverso;
} menu_d;
/*--------------------------------------------*/


/*SPAZIO FUNZIONI */



void free_celle_tabellone(tab_t tabellone){
    free(tabellone.celle_tabellone);
}


void f (int a){
    a = 7;
}

void f2 (int* a){
    a++;
    *a= 7;
}





void creazione_tabellone(tab_t* tabellone, int dim, int altezza){
    tabellone->dimensione = dim;
    tabellone->altezza_pedine = altezza + 2;
    tabellone->altezza_pedine_max = altezza;
    tabellone->celle_tabellone = (char*) malloc(sizeof(char)*(tabellone->altezza_pedine)*(tabellone->dimensione)*(tabellone->dimensione));
}

/*Funzione che restituisce l'indirizzo della cella voluta del tabellone date in input le sue coordinate. */
char* posizione(tab_t tabellone, int selezione_r, int selezione_c, int selezione_h){
    return &(tabellone.celle_tabellone[(tabellone.altezza_pedine) * (tabellone.dimensione) * selezione_r + tabellone.altezza_pedine * selezione_c + selezione_h]);
}

/*Funzione che restituisce l'indirizzo della cella voluta del tabellone date in input le sue coordinate e di quanto ci si vuole spostare da esse. */
char* posizione_shift(tab_t tabellone, int selezione_r, int selezione_c, int selezione_h, int shift_r, int shift_c, int shift_h){
    return &(tabellone.celle_tabellone[(tabellone.altezza_pedine) * (tabellone.dimensione) * (selezione_r + shift_r) + (tabellone.altezza_pedine) * (selezione_c + shift_c) + (selezione_h + shift_h)]);
}

/* Funzione per inizializzare tabellone.
il tabellone deve essere un quadrato.
tabellone.dimensione corrisponde alla dimensione delle righe che è pari a quella delle colonne. */
void inizializzazione_tabellone(tab_t tabellone) {
    int r, c, h;
    /*assegna i valori alle righe del'array */
    for (r = 0; r < tabellone.dimensione; r++) {
        /*assegna i valori alle colonne del'array */
        for (c = 0; c < tabellone.dimensione; c++) {
            /*assegna i valori alle caselle del tabellone */
            for (h = 0; h < tabellone.altezza_pedine; h++) {
                if (h != 0) {
                    if (r % 2 == 0) {
                        if (c % 2 == 0) {
                            *posizione(tabellone, r, c, h) = NULLO;
                        }else {
                            *posizione(tabellone, r, c, h) = VUOTO;
                        }
                    }else {
                        if (c % 2 != 0) {
                            *posizione(tabellone, r, c, h) = NULLO;
                        }else {
                            *posizione(tabellone, r ,c, h) = VUOTO;
                        }
                    }
                }else {
                    if (r % 2 == 0) {
                        if (c % 2 == 0) {
                            *posizione(tabellone, r, c, h) = ESCAPE;
                        }else {
                            *posizione(tabellone, r, c, h) = VUOTO;
                        }
                    }else {
                        if (c % 2 != 0) {
                            *posizione(tabellone, r, c, h) = ESCAPE;
                        }else {
                            *posizione(tabellone, r, c, h) = VUOTO;
                        }
                    }
                }
            }
        }
    }
}

/* Funzione per inizializzare le pedine. */
void inizializzazione_pedine(tab_t tabellone) {
    int r, c, h;
    /*assegna i valori alle righe del'array */
    for (r = 0; r < tabellone.dimensione; r++) {
        /*assegna i valori alle colonne del'array */
        for (c = 0; c < tabellone.dimensione; c++) {
            for (h = 0; h < tabellone.altezza_pedine; h++) {
                /*assegna le pedine al giocatore 2 */
                if (r < (tabellone.dimensione / 2)) {
                    if (r % 2 == 0) {
                        if (c % 2 == 0) {
                            *posizione(tabellone, r, c, (tabellone.altezza_pedine - 1)) = GIOCATORE2;
                        }
                    }else {
                        if (c % 2 != 0) {
                            *posizione(tabellone, r, c, (tabellone.altezza_pedine - 1)) = GIOCATORE2;
                        }
                    }
                    /* assegna le pedine al giocatore 1 */
                }else {
                    if (r >= ((tabellone.dimensione)-(tabellone.dimensione / 2))) {
                        if (r % 2 == 0) {
                            if (c % 2 == 0) {
                                *posizione(tabellone, r, c, (tabellone.altezza_pedine - 1)) = GIOCATORE1;
                            }
                        }else {
                            if (c % 2 != 0) {
                                *posizione(tabellone, r, c, (tabellone.altezza_pedine - 1)) = GIOCATORE1;
                            }
                        }
                    }
                }
            }
        }
    }
}


/* Funzione che stampa il tabellone. */
void print_tab(tab_t tabellone) {
    int colonna = 0;
    int r, c, h;
    /* stampa le righe del tabellone */
    for (r = 0; r < tabellone.dimensione; r++) {
        printf("%d ", colonna);
        ++colonna;
        /*stampa le colonne del tabelonne */
        for (h = 1; h < tabellone.altezza_pedine; h++) {
            for (c = 0; c < tabellone.dimensione; c++) {
                int casella = *posizione(tabellone, r, c, h);
                if (casella == VUOTO) {
                    printf("         ");
                }else {
                    if (casella == GIOCATORE1) {
                        printf("xxxxxxxxx");
                    }
                    if (casella == GIOCATORE2) {
                        printf("ooooooooo");
                    }
                    if (casella == NULLO) {
                        printf("=========");
                    }
                    if (casella== PROMOSSO){
                        printf("@=@=@=@=@");
                    }
                }

            }
            if (h != (tabellone.altezza_pedine - 1)) {
                printf("\n");
            }
            printf("  ");
        }
        printf("\n");
    }
int riga;
    printf("  ");
    for (riga = 0; riga < tabellone.dimensione; riga++){
    printf("    %d    ", riga);
    }
    printf("\n");
}

/* Funzione per determinare a che giocatore appartiene la pedina. */
int scorrimento(tab_t tabellone, int selezione_r, int selezione_c){
    char* adress;
    adress = posizione(tabellone, selezione_r, selezione_c, 0);

    int aux;
    for (int i=0; ((i<tabellone.altezza_pedine)&&(adress[i]!=GIOCATORE1)&&(adress[i]!=GIOCATORE2)); i++){
        aux= i;
    }
    ++aux;
    return adress[aux];
}

/* Funzione per determinare se una pedina è promossa */
int verify_promotion(tab_t tabellone, int selezione_r, int selezione_c){
    char* adress;
    adress = posizione(tabellone, selezione_r, selezione_c, 0);

    for (int i=0; i<tabellone.altezza_pedine; i++){
        if (adress[i]==PROMOSSO){
            return 1;
        }
    }
    return 0;
}

/* Funzione per determinare se una determinata casella non contiene pedine. */
int verify_nullo(tab_t tabellone, int selezione_r, int selezione_c){
    char* adress;
    adress = posizione(tabellone, selezione_r, selezione_c, 0);

    for (int i=1; ((i<tabellone.altezza_pedine)); i++) {
        if (adress[i] != NULLO) {
            return 0;
        }
    }
    return 1;
}

/* Funzione per determinare se una determinata casella non è utilizzabile. */
int verify_vuoto(tab_t tabellone, int selezione_r, int selezione_c){
    char* adress;
    adress = posizione(tabellone, selezione_r, selezione_c, 0);

    for (int i=1; ((i<tabellone.altezza_pedine)); i++) {
        if (adress[i] != VUOTO) {
            return 0;
        }
    }
    return 1;
}

/* Funzione che determinia il giocatore opposto. */
char find_opposite(char giocatore){
    if (giocatore == GIOCATORE1){
        return GIOCATORE2;
    }else{
        return GIOCATORE1;
    }
}

/* Funzione per determinare se la pedina selezionata dal giocatore abbia mosse legali disponibili. */
int verifica_mosse_pedina(tab_t tabellone, char giocatore, int selezione_r, int selezione_c){
    char giocatore_opposto = find_opposite(giocatore);
/* verifica per pedine promosse */
    /* verifica caselle libere circostanti alla pedina */
    if (verify_promotion(tabellone, selezione_r, selezione_c)){
        if (selezione_r < tabellone.dimensione - 1) {
            if (selezione_c < tabellone.dimensione - 1) {
                if (verify_nullo(tabellone, (selezione_r + 1), (selezione_c + 1))){
                    return 1;
                }
            }
            if (selezione_c > 0){
                if (verify_nullo(tabellone, (selezione_r + 1), (selezione_c - 1))){
                    return 1;
                }
            }
        }

        if (selezione_r > 0) {
            if (selezione_c < tabellone.dimensione-1) {
                if (verify_nullo(tabellone, (selezione_r - 1), (selezione_c + 1))){
                    return 1;
                }
            }
            if (selezione_c > 0){
                if (verify_nullo(tabellone, (selezione_r - 1), (selezione_c - 1))){
                    return 1;
                }
            }
        }

        /*verifica caselle libere tramite conquista */
        if (selezione_r < tabellone.dimensione - 2) {
            if (selezione_c < tabellone.dimensione - 2) {
                if (scorrimento(tabellone, (selezione_r + 1), (selezione_c + 1))==giocatore_opposto) {
                    if (verify_nullo(tabellone, (selezione_r + 2), (selezione_c + 2))){
                        return 1;
                    }
                }
            }
            if (selezione_c > 1){
                if (scorrimento(tabellone, (selezione_r + 1), (selezione_c - 1))==giocatore_opposto) {
                    if (verify_nullo(tabellone, (selezione_r + 2), (selezione_c - 2))){
                        return 1;
                    }
                }
            }
        }

        if (selezione_r > 1) {
            if (selezione_c < tabellone.dimensione-2) {
                if (scorrimento(tabellone, (selezione_r - 1), (selezione_c + 1))==giocatore_opposto) {
                    if (verify_nullo(tabellone, (selezione_r - 2), (selezione_c + 2))){
                        return 1;
                    }
                }
            }
            if (selezione_c > 1){
                if (scorrimento(tabellone, (selezione_r - 1), (selezione_c - 1))==giocatore_opposto) {
                    if (verify_nullo(tabellone, (selezione_r - 2), (selezione_c - 2))){
                        return 1;
                    }
                }
            }
        }

/*verifica per pedine non promosse */
    }else{
        /* pedina appartenete al giocatore 2 */
        if (scorrimento(tabellone, selezione_r, selezione_c)==GIOCATORE2){
            /* verifica caselle libere circostanti alla pedina */
            if (selezione_r < tabellone.dimensione-1) {
                if (selezione_c < tabellone.dimensione-1) {
                    if (verify_nullo(tabellone, (selezione_r + 1), (selezione_c + 1))){
                        return 1;
                    }
                }
                if (selezione_c > 0){
                    if (verify_nullo(tabellone, (selezione_r + 1), (selezione_c - 1))){
                        return 1;
                    }
                }
            }
            /*verifica caselle libere tramite conquista */
            if (selezione_r < tabellone.dimensione-2) {
                if (selezione_c < tabellone.dimensione-2) {
                    if (scorrimento(tabellone, (selezione_r + 1), (selezione_c + 1))==giocatore_opposto) {
                        if (verify_nullo(tabellone, (selezione_r + 2), (selezione_c + 2))){
                            return 1;
                        }
                    }
                }
                if (selezione_c > 1){
                    if (scorrimento(tabellone, (selezione_r + 1), (selezione_c - 1))==giocatore_opposto) {
                        if (verify_nullo(tabellone, (selezione_r + 2), (selezione_c - 2))){
                            return 1;
                        }
                    }
                }
            }

            /* pedina appartenete al giocatore 1 */
        }else{
            /* verifica caselle libere circostanti alla pedina */
            if (selezione_r > 0) {
                if (selezione_c < tabellone.dimensione-1) {
                    if (verify_nullo(tabellone, (selezione_r - 1), (selezione_c + 1))){
                        return 1;
                    }
                }
                if (selezione_c > 0){
                    if (verify_nullo(tabellone, (selezione_r - 1), (selezione_c - 1))){
                        return 1;
                    }
                }
            }
            /*verifica caselle libere tramite conquista */
            if (selezione_r > 1) {
                if (selezione_c < tabellone.dimensione-2) {
                    if (scorrimento(tabellone, (selezione_r - 1), (selezione_c + 1))==giocatore_opposto) {
                        if (verify_nullo(tabellone, (selezione_r - 2), (selezione_c + 2))){
                            return 1;
                        }
                    }
                }
                if (selezione_c > 1){
                    if (scorrimento(tabellone, (selezione_r - 1), (selezione_c - 1))==giocatore_opposto) {
                        if (verify_nullo(tabellone, (selezione_r - 2), (selezione_c - 2))){
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

/* Funzione per verificare se il giocatore disponga di pedine aventi mosse legali disponibili. */
int verifica_mosse_legali(tab_t tabellone, char giocatore){
    for (int r = 0; r < tabellone.dimensione; r++) {
        for (int c = 0; c < tabellone.dimensione; c++) {
            if (scorrimento(tabellone, r, c)== giocatore){
                if (verifica_mosse_pedina(tabellone, giocatore, r, c)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

/* Funzione per calcolare l'altezza di una determinata torre. */
int altezza_counter(tab_t tabellone, int selezione_r, int selezione_c){
    char* adress;
    adress = posizione(tabellone, selezione_r, selezione_c, 0);

    int i=0;
    while ((adress[i]!=(GIOCATORE1))&&(adress[i]!=(GIOCATORE2))&&(i < tabellone.altezza_pedine)){
        ++i;
    }
    return (tabellone.altezza_pedine - i);
}

/* Funzione per promuovere le pedine. */
void promotion(tab_t tabellone, int coordinata_r, int coordinata_c){
    int altezza_giocatore = altezza_counter(tabellone, coordinata_r, coordinata_c);
    *posizione(tabellone, coordinata_r, coordinata_c, (tabellone.altezza_pedine - altezza_giocatore - 1)) = PROMOSSO;
}

/* Funzione per promuovere una pedina quando raggiunge un estremo del tabellone. */
void promotion_ext(tab_t tabellone, int mossa_r, int mossa_c, char giocatore) {
    if (giocatore == GIOCATORE1) {
        if (mossa_r == 0) {
            promotion(tabellone, mossa_r, mossa_c);
        }
    } else {
        if (mossa_r == (tabellone.dimensione - 1)) {
            promotion(tabellone, mossa_r, mossa_c);
        }
    }
}

/* Funzione per selezione le coordinate di una pedina. */
int selezione_coordinate_partenza(tab_t tabellone, char giocatore, int* coordinate_selezione){

    coordinate_selezione[0] = tabellone.dimensione;
    coordinate_selezione[1] = tabellone.dimensione;

    /* selezione della riga */
    while ((coordinate_selezione[0] >= tabellone.dimensione)||(coordinate_selezione[0] < 0)) {
        printf("Selezionare la riga della pedina da muovere:\n");
        scanf("%d", coordinate_selezione);
        if ((coordinate_selezione[0] >= tabellone.dimensione)||(coordinate_selezione[0] < 0)) {
            printf("\nErrore, riga non disponibile.\n\n");
        }
    }

    /* selezione della colonna */
    while ((coordinate_selezione[1] >= tabellone.dimensione)||(coordinate_selezione[1] < 0)) {
        printf("Selezionare la colonna della pedina da muovere:\n");
        scanf("%d", (coordinate_selezione + 1));
        if ((coordinate_selezione[1] >= tabellone.dimensione)||(coordinate_selezione[1] < 0)) {
            printf("\nErrore, colonna non disponibile.\n\n");
        }
    }

    /* conferma selezione */
    if (scorrimento(tabellone, coordinate_selezione[0], coordinate_selezione[1]) == giocatore) {
        if (verifica_mosse_pedina(tabellone, giocatore, coordinate_selezione[0], coordinate_selezione[1])) {
            printf("\nPedina selezionata correttamente.\n\n");
            return 1;
        }else{
            printf("\nErrore, pedina non avente mosse legali disponibili.\n\n");
            return 0;
        }
    } else {
        printf("\nErrore, casella non contenente una pedina appartenete al giocatore.\n\n");
        return 0;
    }
}

/* Funzione per determinare se una mossa selezionata sia legale. */
int move_is_legit(tab_t tabellone, int* coordinate_selezione, int* coordinate_mossa){

    int selezione_r = coordinate_selezione[0];
    int selezione_c = coordinate_selezione[1];
    int mossa_r = coordinate_mossa[0];
    int mossa_c = coordinate_mossa[1];

    char giocatore;
    char giocatore_opposto;

    if ((mossa_r >= tabellone.dimensione)||(mossa_r < 0)||(mossa_c >= tabellone.dimensione)||(mossa_c < 0)){
        return 0;
    }

    if(verify_vuoto(tabellone, mossa_r, mossa_c)){
        printf("\nErrore, mossa non consentita. \nQuella casella non e, e non sarai mai utilizzabile. ");
        return 0;
    }

    if (!(verify_nullo(tabellone, mossa_r, mossa_c))){
        printf("\nErrore, mossa non consentita. \nNon puoi selezionare caselle non vuote. ");
        return 0;
    }


    if (scorrimento(tabellone, selezione_r, selezione_c) == GIOCATORE1){
        giocatore = GIOCATORE1;
        giocatore_opposto = find_opposite(giocatore);
    } else{
        giocatore = GIOCATORE2;
        giocatore_opposto = find_opposite(giocatore);
    }

    if ((selezione_c == mossa_c)&&(selezione_r == mossa_r)) {
        printf("\nErrore, mossa non consentita. \nChe ti aspetti, che ti lasciassi saltare il turno standotene là fermo?! \n\n");
        return 0;
    }

    if (verify_vuoto(tabellone, mossa_r, mossa_c)){
        printf("\nErrore, mossa non consentita.\nEvita di selezionare caselle non utilizzabili la prossima volta. \n\n");
        return 0;
    }

    if (verify_promotion(tabellone, selezione_r, selezione_c)){
        if (!(((mossa_r == selezione_r + 1)&&(mossa_c == selezione_c + 1)) || ((mossa_r == selezione_r + 1)&&(mossa_c == selezione_c - 1)) || ((mossa_r == selezione_r - 1)&&(mossa_c == selezione_c + 1)) || ((mossa_r == selezione_r - 1)&&(mossa_c == selezione_c - 1)) || ((mossa_r == selezione_r + 2)&&(mossa_c == selezione_c + 2)) || ((mossa_r == selezione_r + 2)&&(mossa_c == selezione_c -2 )) || ((mossa_r == selezione_r - 2)&&(mossa_c == selezione_c + 2)) || ((mossa_r == selezione_r - 2)&&(mossa_c == selezione_c - 2)))){
            printf("\nErrore, mossa non consentita.\nSeleziona una casella consona alle regole del gioco. \n\n");
            return 0;
        }

        if (mossa_r == selezione_r + 2) {
            if (mossa_c == selezione_c + 2) {
                if (scorrimento(tabellone, (selezione_r + 1), (selezione_c + 1)) != giocatore_opposto) {
                    printf("\nErrore, mossa non consentita.\nPuoi spostarti di 2 caselle solo quando conquisti una pedina avversaria. \n\n");
                    return 0;
                }
            }
            if (mossa_c == selezione_c - 2) {
                if (scorrimento(tabellone, (selezione_r + 1), (selezione_c - 1)) != giocatore_opposto) {
                    printf("\nErrore, mossa non consentita.\nPuoi spostarti di 2 caselle solo quando conquisti una pedina avversaria. \n\n");
                    return 0;
                }
            }
        }
        if (mossa_r == selezione_r - 2){
            if (mossa_c == selezione_c + 2){
                if (scorrimento(tabellone, (selezione_r - 1), (selezione_c + 1)) != giocatore_opposto){
                    printf("\nErrore, mossa non consentita.\nPuoi spostarti di 2 caselle solo quando conquisti una pedina avversaria. \n\n");
                    return 0;
                }
            }
            if (mossa_c == selezione_c - 2){
                if (scorrimento(tabellone, (selezione_r - 1), (selezione_c - 1)) != giocatore_opposto){
                    printf("\nErrore, mossa non consentita.\nPuoi spostarti di 2 caselle solo quando conquisti una pedina avversaria. \n\n");
                    return 0;
                }
            }
        }
    } else {
        if (giocatore == GIOCATORE1){

            if (mossa_r > selezione_r){
                printf("\nErrore, mossa non consentita.\nPer spostare la pedina all'indietro, e necessario prima promuoverla. \n\n");
                return 0;
            }

            if (!( ((mossa_r == selezione_r - 1)&&(mossa_c == selezione_c + 1)) || ((mossa_r == selezione_r - 1)&&(mossa_c == selezione_c - 1)) || ((mossa_r == selezione_r - 2)&&(mossa_c == selezione_c + 2)) || ((mossa_r == selezione_r - 2)&&(mossa_c == selezione_c -2 )) )){
                printf("\nErrore, mossa non consentita.\nSeleziona una casella consona alle regole del gioco. \n\n");
                return 0;
            }

            if (mossa_r == selezione_r - 2) {
                if (mossa_c == selezione_c + 2) {
                    if (scorrimento(tabellone, (selezione_r - 1), (selezione_c + 1)) != giocatore_opposto) {
                        printf("\nErrore, mossa non consentita.\nPuoi spostarti di 2 caselle solo quando conquisti una pedina avversaria. \n\n");
                        return 0;
                    }
                }
                if (mossa_c == selezione_c - 2) {
                    if (scorrimento(tabellone, (selezione_r - 1), (selezione_c - 1)) != giocatore_opposto) {
                        printf("\nErrore, mossa non consentita.\nPuoi spostarti di 2 caselle solo quando conquisti una pedina avversaria. \n\n");
                        return 0;
                    }
                }
            }
        }else{

            if (mossa_r < selezione_r){
                printf("\nErrore, mossa non consentita.\nPer spostare la pedina all'indietro, e necessario prima promuoverla. \n\n");
                return 0;
            }

            if (!( ((mossa_r == selezione_r + 1)&&(mossa_c == selezione_c + 1)) || ((mossa_r == selezione_r + 1)&&(mossa_c == selezione_c - 1)) || ((mossa_r == selezione_r + 2)&&(mossa_c == selezione_c + 2)) || ((mossa_r == selezione_r + 2)&&(mossa_c == selezione_c -2 )) )){
                printf("\nErrore, mossa non consentita.\nSeleziona una casella consona alle regole del gioco. \n\n");
                return 0;
            }

            if (mossa_r == selezione_r + 2) {
                if (mossa_c == selezione_c + 2) {
                    if (scorrimento(tabellone, (selezione_r + 1), (selezione_c + 1)) != giocatore_opposto) {
                        printf("\nErrore, mossa non consentita.\nPuoi spostarti di 2 caselle solo quando conquisti una pedina avversaria. \n\n");
                        return 0;
                    }
                }
                if (mossa_c == selezione_c - 2) {
                    if (scorrimento(tabellone, (selezione_r + 1), (selezione_c - 1)) != giocatore_opposto) {
                        printf("\nErrore, mossa non consentita.\nPuoi spostarti di 2 caselle solo quando conquisti una pedina avversaria. \n\n");
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

/* Versione di move_is_legit senza testo in output né array. */
int move_is_legit_no_text(tab_t tabellone, int selezione_r, int selezione_c, int mossa_r, int mossa_c){
    char giocatore;
    char giocatore_opposto;

    if ((mossa_r >= tabellone.dimensione)||(mossa_r < 0)||(mossa_c >= tabellone.dimensione)||(mossa_c < 0)){
        return 0;
    }

    if(verify_vuoto(tabellone, mossa_r, mossa_c)){
        return 0;
    }

    if (!(verify_nullo(tabellone, mossa_r, mossa_c))){
        return 0;
    }

    if (scorrimento(tabellone, selezione_r, selezione_c) == GIOCATORE1){
        giocatore = GIOCATORE1;
        giocatore_opposto = find_opposite(giocatore);
    } else{
        giocatore = GIOCATORE2;
        giocatore_opposto = find_opposite(giocatore);
    }

    if ((selezione_c == mossa_c)&&(selezione_r == mossa_r)) {
        return 0;
    }

    if (verify_vuoto(tabellone, mossa_r, mossa_c)){
        return 0;
    }

    if (verify_promotion(tabellone, selezione_r, selezione_c)){
        if (!(((mossa_r == selezione_r + 1)&&(mossa_c == selezione_c + 1)) || ((mossa_r == selezione_r + 1)&&(mossa_c == selezione_c - 1)) || ((mossa_r == selezione_r - 1)&&(mossa_c == selezione_c + 1)) || ((mossa_r == selezione_r - 1)&&(mossa_c == selezione_c - 1)) || ((mossa_r == selezione_r + 2)&&(mossa_c == selezione_c + 2)) || ((mossa_r == selezione_r + 2)&&(mossa_c == selezione_c -2 )) || ((mossa_r == selezione_r - 2)&&(mossa_c == selezione_c + 2)) || ((mossa_r == selezione_r - 2)&&(mossa_c == selezione_c - 2)))){
            return 0;
        }

        if (mossa_r == selezione_r + 2) {
            if (mossa_c == selezione_c + 2) {
                if (scorrimento(tabellone, (selezione_r + 1), (selezione_c + 1)) != giocatore_opposto) {
                    return 0;
                }
            }
            if (mossa_c == selezione_c - 2) {
                if (scorrimento(tabellone, (selezione_r + 1), (selezione_c - 1)) != giocatore_opposto) {
                    return 0;
                }
            }
        }
        if (mossa_r == selezione_r - 2){
            if (mossa_c == selezione_c + 2){
                if (scorrimento(tabellone, (selezione_r - 1), (selezione_c + 1)) != giocatore_opposto){
                    return 0;
                }
            }
            if (mossa_c == selezione_c - 2){
                if (scorrimento(tabellone, (selezione_r - 1), (selezione_c - 1)) != giocatore_opposto){
                    return 0;
                }
            }
        }
    } else {
        if (giocatore == GIOCATORE1){

            if (mossa_r > selezione_r){
                return 0;
            }

            if (!( ((mossa_r == selezione_r - 1)&&(mossa_c == selezione_c + 1)) || ((mossa_r == selezione_r - 1)&&(mossa_c == selezione_c - 1)) || ((mossa_r == selezione_r - 2)&&(mossa_c == selezione_c + 2)) || ((mossa_r == selezione_r - 2)&&(mossa_c == selezione_c -2 )) )){
                return 0;
            }

            if (mossa_r == selezione_r - 2) {
                if (mossa_c == selezione_c + 2) {
                    if (scorrimento(tabellone, (selezione_r - 1), (selezione_c + 1)) != giocatore_opposto) {
                        return 0;
                    }
                }
                if (mossa_c == selezione_c - 2) {
                    if (scorrimento(tabellone, (selezione_r - 1), (selezione_c - 1)) != giocatore_opposto) {
                        return 0;
                    }
                }
            }
        }else{

            if (mossa_r < selezione_r){
                return 0;
            }

            if (!( ((mossa_r == selezione_r + 1)&&(mossa_c == selezione_c + 1)) || ((mossa_r == selezione_r + 1)&&(mossa_c == selezione_c - 1)) || ((mossa_r == selezione_r + 2)&&(mossa_c == selezione_c + 2)) || ((mossa_r == selezione_r + 2)&&(mossa_c == selezione_c -2 )) )){
                return 0;
            }

            if (mossa_r == selezione_r + 2) {
                if (mossa_c == selezione_c + 2) {
                    if (scorrimento(tabellone, (selezione_r + 1), (selezione_c + 1)) != giocatore_opposto) {
                        return 0;
                    }
                }
                if (mossa_c == selezione_c - 2) {
                    if (scorrimento(tabellone, (selezione_r + 1), (selezione_c - 1)) != giocatore_opposto) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

/* Funzione per selezionare la destinazione di una pedina. */
int selezione_coordinate_arrivo(tab_t tabellone, int* coordinate_selezione, int* coordinate_mossa){

        coordinate_mossa[0] = tabellone.dimensione;
        coordinate_mossa[1] = tabellone.dimensione;

        /* selezione della riga */
        while ((coordinate_mossa[0] >= tabellone.dimensione)||(coordinate_mossa[0] < 0)) {
            printf("Selezionare la riga della destinazione della pedina:\n");
            scanf("%d", coordinate_mossa);
            if ((coordinate_mossa[0] >= tabellone.dimensione)||(coordinate_mossa[0] < 0)) {
                printf("\nErrore, riga non disponibile.\n\n");
            }
        }

        /* selezione della colonna */
        while ((coordinate_mossa[1] >= tabellone.dimensione)||(coordinate_mossa[1] < 0)) {
            printf("Selezionare la colonna della destinazione della pedina:\n");
            scanf("%d", (coordinate_mossa + 1));
            if ((coordinate_mossa[1] >= tabellone.dimensione)||(coordinate_mossa[1] < 0)) {
                printf("\nErrore, colonna non disponibile.\n\n");
            }
        }

        /* conferma selezione */
        if (move_is_legit(tabellone, coordinate_selezione, coordinate_mossa)) {
            printf("\nCasella selezionata correttamente.\n\n");
            return 1;
        }else{
            int ciclo = 1;
            printf("Vuoi scegliere una altra pedina? Y/N\n");
            while (ciclo) {
                char selezione;
                scanf("%c", &selezione);
                if (selezione == 'N'){
                    ciclo = 0;
                    printf("\n");
                }
                if (selezione == 'Y'){
                    ciclo = 0;
                    return 0;
                }
            }
        }
}

/*funzione per scegliere le coordinate di una pedina */
void coordinate(tab_t tabellone, int* coordinate_selezione, int* coordinate_mossa, char giocatore){

    int verify = 0;

    while (!verify){
        verify = selezione_coordinate_partenza(tabellone, giocatore, coordinate_selezione);
        if (verify) {
            verify = selezione_coordinate_arrivo(tabellone, coordinate_selezione, coordinate_mossa);
            if (!verify){
                printf("\n");
                print_tab(tabellone);
                printf("\n");
            }
        } else {
            printf("\n");
            print_tab(tabellone);
            printf("\n");
        }
    }
}

/* Funzione per spostare una pedina senza conquista. */
void spostamento_semplice(tab_t tabellone, int selezione_r, int selezione_c, int mossa_r, int mossa_c){

    for (int i = 0; i < tabellone.altezza_pedine; i++) {
        *posizione(tabellone, mossa_r, mossa_c, i) = *posizione(tabellone, selezione_r, selezione_c, i);
        if (i != 0) {
            *posizione(tabellone, selezione_r, selezione_c, i) = NULLO;
        } else {
            *posizione(tabellone, selezione_r, selezione_c, i) = ESCAPE;
        }
    }
}

/* Funzione per rimuovere una pedina conquistata. Le coordinate fanno riferimento alla pedina selezionata per compiere la conquista. */
void rimozione_pedina(tab_t tabellone, int selezione_r, int selezione_c, int mossa_r, int mossa_c){
    int shift_r, shift_c;
    if (mossa_r > selezione_r){
        shift_r = mossa_r - selezione_r - 1;
    }else{
        shift_r = mossa_r - selezione_r + 1;
    }

    if (mossa_c > selezione_c){
        shift_c = mossa_c - selezione_c - 1;
    }else{
        shift_c = mossa_c - selezione_c + 1;
    }

    int altezza_giocatore_opposto = altezza_counter(tabellone, (selezione_r + shift_r), (selezione_c + shift_c));

    if (verify_promotion(tabellone, (selezione_r + shift_r), (selezione_c + shift_c))){
        *posizione_shift(tabellone, selezione_r, selezione_c, tabellone.altezza_pedine, shift_r, shift_c, (- altezza_giocatore_opposto))= PROMOSSO;
        if (*posizione_shift(tabellone, selezione_r, selezione_c, tabellone.altezza_pedine, shift_r, shift_c, (- (altezza_giocatore_opposto + 1)))!= ESCAPE){
            *posizione_shift(tabellone, selezione_r, selezione_c, tabellone.altezza_pedine, shift_r, shift_c, (-(altezza_giocatore_opposto + 1)))= NULLO;
        }
    }else{
        *posizione_shift(tabellone, selezione_r, selezione_c, tabellone.altezza_pedine, shift_r, shift_c, (- (altezza_giocatore_opposto)))= NULLO;
    }
}

/*Funzione per spostare una pedina alta meno del massimo consentito con conquista */
void spostamento_conquista(tab_t tabellone, int selezione_r, int selezione_c, int mossa_r, int mossa_c){
    char giocatore_opposto;

    if (scorrimento(tabellone, selezione_r, selezione_c) == GIOCATORE1){
        giocatore_opposto = GIOCATORE2;
    } else{
        giocatore_opposto = GIOCATORE1;
    }

    for (int i = 0; i < tabellone.altezza_pedine; i++) {
        if (i > 1) {
            *posizione_shift(tabellone, mossa_r, mossa_c, i, 0, 0, -1)= *posizione(tabellone, selezione_r, selezione_c, i);
        } else {
            *posizione(tabellone, mossa_r, mossa_c, i)= *posizione(tabellone, selezione_r, selezione_c, i);
        }
        if (i != 0) {
            *posizione(tabellone, selezione_r, selezione_c, i)= NULLO;
        } else {
            *posizione(tabellone, selezione_r, selezione_c, i)= ESCAPE;
        }
        *posizione_shift(tabellone, mossa_r, mossa_c, tabellone.altezza_pedine, 0, 0, -1) = giocatore_opposto;
    }

    rimozione_pedina(tabellone, selezione_r, selezione_c, mossa_r, mossa_c);
}

/*Funzione per spostare una pedina alta pari al massimo consentito con conquista */
void spostamento_conquista_max(tab_t tabellone, int selezione_r, int selezione_c, int mossa_r, int  mossa_c){

    for (int i = 0; i < tabellone.altezza_pedine; i++) {

        *posizione(tabellone, mossa_r, mossa_c, i)= *posizione(tabellone, selezione_r, selezione_c, i);

        if (i != 0) {
            *posizione(tabellone, selezione_r, selezione_c, i) = NULLO;
        } else {
            *posizione(tabellone, selezione_r, selezione_c, i) = ESCAPE;
        }
    }

    rimozione_pedina(tabellone, selezione_r, selezione_c, mossa_r, mossa_c);
}

/*funzione che muove le pedine */
void spostamento_pedina(tab_t tabellone, int selezione_r, int selezione_c, int mossa_r, int mossa_c){

    if (((mossa_r - selezione_r)< 2)&&((mossa_r - selezione_r)> -2)){
        spostamento_semplice(tabellone, selezione_r, selezione_c, mossa_r, mossa_c);
    }else{
        if (altezza_counter(tabellone, selezione_r, selezione_c) < tabellone.altezza_pedine_max){
            spostamento_conquista(tabellone, selezione_r, selezione_c, mossa_r, mossa_c);
        }else{
            spostamento_conquista_max(tabellone, selezione_r, selezione_c, mossa_r, mossa_c);
        }
    }
}

/* Funzione che esegue una determinata mossa */
void mossa(tab_t tabellone, char giocatore, int selezione_r, int selezione_c, int mossa_r, int mossa_c){
        spostamento_pedina(tabellone, selezione_r, selezione_c, mossa_r, mossa_c);
        promotion_ext(tabellone, mossa_r, mossa_c, giocatore);
}

/* Funzione per far eseguire una mossa a un determinato giocatore */
void interazione_mossa(tab_t tabellone, char giocatore){
    int coordinate_selezione[2];
    int coordinate_mossa[2];
    coordinate(tabellone, coordinate_selezione, coordinate_mossa, giocatore);
    int selezione_r = coordinate_selezione[0];
    int selezione_c = coordinate_selezione[1];
    int mossa_r = coordinate_mossa[0];
    int mossa_c = coordinate_mossa[1];

    mossa(tabellone, giocatore, selezione_r, selezione_c, mossa_r, mossa_c);
}

/* funzione ricorsiva che determina i turni dei giocatori e fa terminare il gioco non appena uno vince */
int turno(tab_t tabellone, char giocatore) {
    if (!(verifica_mosse_legali(tabellone, giocatore))){
        if (giocatore == GIOCATORE1) {
            printf("\n\nIl giocatore 2 ha vinto!\n\n Premi 1 per tornare al menù\n");
            int a = 0;
            while (a!=1){
                scanf("%d", &a);
            }
            return 1;
        } else {
            printf("\n\nIl giocatore 1 ha vinto!\n\nPremi 1 per tornare al menù\n");
            int a = 0;
            while (a!=1){
                scanf("%d", &a);
            }
            return 1;
        }
    } else{
        if (giocatore == GIOCATORE1){
            printf("\nE il turno del Giocatore 1\n");
        } else{
            printf("\nE il turno del Giocatore 2\n");
        }
        print_tab(tabellone);
        interazione_mossa(tabellone, giocatore);
        if (giocatore == GIOCATORE1){
            return turno(tabellone, GIOCATORE2);
        }else{
            return turno(tabellone, GIOCATORE1);
        }
    }
}

/* -------------MODALITÀ VS CPU------------- */

/* Funzione che calcola il numero di pedine appartenenti al giocatore. */
int counter_pedine_giocatore(tab_t tabellone, char giocatore){
    int counter = 0;

    for (int r = 0; r < tabellone.dimensione; r++) {
        for (int c = 0; c < tabellone.dimensione; c++) {
            if (scorrimento(tabellone, r, c)== giocatore){
                ++counter;
            }
        }
    }
    return counter;
}

/* Funzione che calcola il numero di pedine promosse del giocatore. */
int counter_pedine_promosse(tab_t tabellone, char giocatore){
    int counter = 0;

    for (int r = 0; r < tabellone.dimensione; r++) {
        for (int c = 0; c < tabellone.dimensione; c++) {
            if (scorrimento(tabellone, r, c)== giocatore){
                if (verify_promotion(tabellone, r, c)){
                    ++counter;
                }
            }
        }
    }
    return counter;
}

/* Funzione che trova la pedina più alta del giocatore. */
int* pedina_max_player(tab_t tabellone, char giocatore){
    int* coordinate;
    coordinate =(int*) malloc(sizeof(int)*2);
    int altezza_max;

    if (giocatore == GIOCATORE1){
        altezza_max = altezza_counter(tabellone, (tabellone.dimensione - 1), (tabellone.dimensione - 1));
    } else{
        altezza_max = altezza_counter(tabellone, 0, 0);
    }

    for (int r = 0; r < tabellone.dimensione; r++) {
        for (int c = 0; c < tabellone.dimensione; c++) {
            if (scorrimento(tabellone, r, c) == giocatore){
                int altezza_pedina = altezza_counter(tabellone, r, c);
                if (altezza_pedina > altezza_max){
                    altezza_max = altezza_pedina;
                    coordinate[0] = r;
                    coordinate[1] = c;
                }
            }
        }
    }
    return coordinate;

}

/* Funzione che calcola il valore della pedina più alta del giocatore. */
int pedina_max_value(tab_t tabellone, char giocatore){
    int* adress = pedina_max_player(tabellone, giocatore);
    int a = *adress;
    int b = *(adress +1);
    free(adress);
    return altezza_counter(tabellone, a, b);
}

/* Funzione che calcola il numero di pedine appartenenti al giocatore aventi una altezza >= alla pedina più alta dell'avversario. */
int counter_pedine_maggiori_max(tab_t tabellone, char giocatore){
    char giocatore_opposto = find_opposite(giocatore);

    int counter = 0;

    for (int r = 0; r < tabellone.dimensione; r++) {
        for (int c = 0; c < tabellone.dimensione; c++) {
            if (scorrimento(tabellone, r, c)== giocatore){
                if (altezza_counter(tabellone, r, c) > pedina_max_value(tabellone, giocatore_opposto)){
                    ++counter;
                }
            }
        }
    }
    return counter;
}

/* Funzione che assegna uno score una mossa dell'intelligenza artificiale. */
int score_ai(tab_t tabellone, char giocatore){
    char giocatore_opposto = find_opposite(giocatore);

    if (!(verifica_mosse_legali(tabellone, giocatore))){
        return -5;
    }
    if (!(verifica_mosse_legali(tabellone, giocatore_opposto))){
        return 5;
    }

    if (counter_pedine_giocatore(tabellone, giocatore) == counter_pedine_giocatore(tabellone, giocatore_opposto)){
        if (counter_pedine_maggiori_max(tabellone, giocatore) > counter_pedine_maggiori_max(tabellone, giocatore_opposto)){
            return 2;
        } else if (counter_pedine_maggiori_max(tabellone, giocatore) < counter_pedine_maggiori_max(tabellone, giocatore_opposto)){
            return -2;
        }
        if (counter_pedine_promosse(tabellone, giocatore) > counter_pedine_promosse(tabellone, giocatore_opposto)){
            return 1;
        } else if (counter_pedine_promosse(tabellone, giocatore) < counter_pedine_promosse(tabellone, giocatore_opposto)){
            return -1;
        }
        return 0;
    } else{
        if (counter_pedine_giocatore(tabellone, giocatore) > counter_pedine_giocatore(tabellone, giocatore_opposto)){
            if (counter_pedine_promosse(tabellone, giocatore) > counter_pedine_promosse(tabellone, giocatore_opposto)) {
                return 4;
            }
            return 3;
        } else{
            if (counter_pedine_promosse(tabellone, giocatore) < counter_pedine_promosse(tabellone, giocatore_opposto)){
                return -4;
            }
            return -3;
        }
    }
}




/* Funzione che dato un tabellone ne genera una sua copia. */
tab_t tab_copy(tab_t tabellone){
    tab_t copia;
    copia.dimensione = tabellone.dimensione;
    copia.altezza_pedine = tabellone.altezza_pedine;
    copia.altezza_pedine_max = tabellone.altezza_pedine_max;
    copia.celle_tabellone =(char*) malloc(sizeof(char)*(tabellone.dimensione)*(tabellone.dimensione)*(tabellone.altezza_pedine));
    int i;
    for (i = 0; (i <(tabellone.dimensione)*(tabellone.dimensione)*(tabellone.altezza_pedine)); i++){
        copia.celle_tabellone[i] = tabellone.celle_tabellone[i];
    }
    return copia;
}

/* Funzione ricorsiva che restituisce il tabellone con effettuata la prima mossa disponibile di una pedina specifica del giocatore. */
tab_t first_move_avaible(tab_t tabellone, char giocatore,int selezione_r, int selezione_c, int mossa_r, int mossa_c){
    if ((selezione_r == mossa_r)&&(selezione_c == mossa_c)) {
        return tabellone;
    }
    if (move_is_legit_no_text(tabellone, selezione_r, selezione_c, mossa_r, mossa_c)){
        tab_t tabellone_copia = tab_copy(tabellone);
        mossa(tabellone_copia, giocatore, selezione_r, selezione_c, mossa_r, mossa_c);
        return tabellone_copia;
    }
    if ((selezione_r +2 == mossa_r)&&(selezione_c +2 == mossa_c)){
        return first_move_avaible(tabellone, giocatore, selezione_r, selezione_c, (selezione_r +2), (selezione_c -2));
    }
    if ((selezione_r +2 == mossa_r)&&(selezione_c -2 == mossa_c)){
        return first_move_avaible(tabellone, giocatore, selezione_r, selezione_c, (selezione_r +1), (selezione_c +1));
    }
    if ((selezione_r +1 == mossa_r)&&(selezione_c +1 == mossa_c)){
        return first_move_avaible(tabellone, giocatore, selezione_r, selezione_c, (selezione_r +1), (selezione_c -1));
    }
    if ((selezione_r +1 == mossa_r)&&(selezione_c -1 == mossa_c)){
        return first_move_avaible(tabellone, giocatore, selezione_r, selezione_c, (selezione_r -2), (selezione_c +2));
    }
    if ((selezione_r - 2 == mossa_r)&&(selezione_c +2 == mossa_c)){
        return first_move_avaible(tabellone, giocatore, selezione_r, selezione_c, (selezione_r -2), (selezione_c -2));
    }
    if ((selezione_r - 2 == mossa_r)&&(selezione_c -2 == mossa_c)){
        return first_move_avaible(tabellone, giocatore, selezione_r, selezione_c, (selezione_r -1), (selezione_c +1));
    }
    if ((selezione_r - 1 == mossa_r)&&(selezione_c + 1 == mossa_c)){
        return first_move_avaible(tabellone, giocatore, selezione_r, selezione_c, (selezione_r -1), (selezione_c -1));
    }
    if ((selezione_r - 1 == mossa_r)&&(selezione_c - 1 == mossa_c)){
        return first_move_avaible(tabellone, giocatore, selezione_r, selezione_c, selezione_r, selezione_c);
    }
    return tabellone;
}


/* Funzione che calcola il numero totale di mosse disponibili per una pedina */
int numero_mosse_disponibili_pedina(tab_t tabellone, int selezione_r, int selezione_c){
    int counter = 0;
    int r,c;

    for (r = 2; r > -3; r--){
        for (c = 2; c > -3; c--){
            if ((r == c)||(r + c == 0)){
                if (move_is_legit_no_text(tabellone, selezione_r, selezione_c, r, c)){
                    ++counter;
                }
            }
        }
    }
    return counter;
}

/* Funzione che calcola il numero totale di mosse disponibili per il giocatore in un turno */
int numero_mosse_disponibili_giocatore(tab_t tabellone, char giocatore){
    int counter = 0;
    int r,c;

    for (r = 0; r < tabellone.dimensione; r++){
        for (c = 0; c < tabellone.dimensione; c++){
            if (scorrimento(tabellone, r, c) == giocatore) {
                if (verifica_mosse_pedina(tabellone, giocatore, r, c)) {
                    counter += numero_mosse_disponibili_pedina(tabellone, r, c);
                }
            }
        }
    }
    return counter;
}

/* Funzione che assegna uno score ad possibile mossa di ogni possibile pedina che può essere effettuata dalla cpu */
int cpu_play_minmax(tab_t tabellone, int selezione_r, int selezione_c, char cpu_player, char turno, int mossa_r, int mossa_c, int depth){

    tab_t reset;
    reset = tab_copy(tabellone);
    int best_score = 0;
    /* no more recursion */
    if (depth==0) return score_ai(tabellone, cpu_player);

    /* fai la mossa */
    if (scorrimento(tabellone, selezione_r, selezione_c) == turno) {
        if (verifica_mosse_pedina(tabellone, turno, selezione_r, selezione_c)) {
            if ((mossa_r - selezione_r == mossa_c - selezione_c) || (mossa_r - selezione_r + mossa_c - selezione_c == 0)) {
                if (move_is_legit_no_text(tabellone, selezione_r, selezione_c, mossa_r, mossa_c)) {
                    tabellone = first_move_avaible(tabellone, turno, selezione_r, selezione_c, mossa_r, mossa_c);
                    if (!(verifica_mosse_legali(tabellone, turno))) {
                        if (cpu_player == turno) {
                            best_score = -5;
                        } else {
                            best_score = 5;
                        }
                    } else {
                        /* ricorsione */
                        int nuova_selezione_c;
                        int nuova_selezione_r;
                        int nuova_mossa_r;
                        int nuova_mossa_c;
                        char prox_turno = find_opposite(turno);
                        int *scores = (int *) malloc(
                                numero_mosse_disponibili_giocatore(tabellone, turno) * sizeof(int));
                        int s, num_scores = 0;
                        for (nuova_selezione_r = 0; nuova_selezione_r < tabellone.dimensione; nuova_selezione_r++) {
                            for (nuova_selezione_c = 0; nuova_selezione_c < tabellone.dimensione; nuova_selezione_c++) {
                                if (scorrimento(tabellone, nuova_selezione_r, nuova_selezione_c) == turno) {
                                    if (verifica_mosse_pedina(tabellone, turno, nuova_selezione_r, nuova_selezione_c)) {
                                        for (nuova_mossa_r = selezione_r + 2;
                                             nuova_mossa_r > nuova_selezione_r - 3; nuova_mossa_r--) {
                                            for (nuova_mossa_c = selezione_c + 2;
                                                 nuova_mossa_c > nuova_selezione_c - 3; nuova_mossa_c--) {
                                                if ((nuova_mossa_r - nuova_selezione_r == nuova_mossa_c - nuova_selezione_c) || (nuova_mossa_r - nuova_selezione_r + nuova_mossa_c - nuova_selezione_c == 0)) {
                                                    if (move_is_legit_no_text(tabellone, nuova_selezione_r,
                                                                              nuova_selezione_c, nuova_mossa_r,
                                                                              nuova_mossa_c)) {
                                                        scores[num_scores++] = cpu_play_minmax(tabellone, nuova_selezione_r,
                                                                                               nuova_selezione_c,
                                                                                               cpu_player, prox_turno,
                                                                                               nuova_mossa_r,
                                                                                               nuova_mossa_c,
                                                                                               (depth - 1));
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        best_score = scores[0];
                        for (s = 1; s < num_scores; s++) {
                            if (cpu_player == prox_turno) { /* maximize */
                                if (scores[s] > best_score) best_score = scores[s];
                            } else { /* minimize */
                                if (scores[s] < best_score) best_score = scores[s];
                            }
                        }
                        free(scores);
                    }
                    /* undo della mossa */
                    tabellone = reset;
                    free_celle_tabellone(reset);
                    return best_score;
                } else {
                    if (selezione_c >= tabellone.dimensione - 1) {
                        if (selezione_r >= tabellone.dimensione - 1) {
                            return -5;
                        } else {
                            return cpu_play_minmax(tabellone, (selezione_r + 1), 0, cpu_player, turno, selezione_r + 2,
                                                   selezione_c + 2, depth);
                        }
                    } else {
                        return cpu_play_minmax(tabellone, selezione_r, (selezione_c + 1), cpu_player, turno,
                                               selezione_r + 2, selezione_c + 2, depth);
                    }
                }
            } else {
                if (selezione_c >= tabellone.dimensione - 1) {
                    if (selezione_r >= tabellone.dimensione - 1) {
                        return -5;
                    } else {
                        return cpu_play_minmax(tabellone, (selezione_r + 1), 0, cpu_player, turno, selezione_r + 2,
                                               selezione_c + 2, depth);
                    }
                } else {
                    return cpu_play_minmax(tabellone, selezione_r, (selezione_c + 1), cpu_player, turno,
                                           selezione_r + 2, selezione_c + 2, depth );
                }
            }
        } else {
            if (selezione_c >= tabellone.dimensione - 1) {
                if (selezione_r >= tabellone.dimensione - 1) {
                    return -5;
                } else {
                    return cpu_play_minmax(tabellone, (selezione_r + 1), 0, cpu_player, turno, selezione_r + 2,
                                           selezione_c + 2, depth );
                }
            } else {
                return cpu_play_minmax(tabellone, selezione_r, (selezione_c + 1), cpu_player, turno, selezione_r + 2,
                                       selezione_c + 2, depth);
            }
        }
    } else{
        if (selezione_c >= tabellone.dimensione - 1) {
            if (selezione_r >= tabellone.dimensione - 1) {
                return -5;
            } else {
                return cpu_play_minmax(tabellone, (selezione_r + 1), 0, cpu_player, turno, selezione_r + 2,
                                       selezione_c + 2, depth );
            }
        } else {
            return cpu_play_minmax(tabellone, selezione_r, (selezione_c + 1), cpu_player, turno, selezione_r + 2,
                                   selezione_c + 2, depth);
        }
    }
}


/* Funzione che fa scegliere alla cpu quale pedina muovere e in quale casella */
int* cpu_strategy(tab_t tabellone, char cpu_player, int depth) {
    int best_score = -5;
    int* best_move =(int*) malloc(sizeof(int)*4);
    int selezione_r, selezione_c, mossa_r, mossa_c;

    for(selezione_r = 0; selezione_r < tabellone.dimensione; selezione_r++){
        for (selezione_c = 0; selezione_c < tabellone.dimensione; selezione_c++){
            if (scorrimento(tabellone, selezione_r, selezione_c) == cpu_player){
                if (verifica_mosse_pedina(tabellone, cpu_player, selezione_r, selezione_c)){
                    for (mossa_r = selezione_r+2; mossa_r > selezione_r -3; mossa_r--) {
                        for (mossa_c = selezione_c + 2; mossa_c > selezione_c -3; mossa_c--) {
                            if ((mossa_r - selezione_r == mossa_c - selezione_c) || (mossa_r - selezione_r + mossa_c - selezione_c == 0)) {
                                if (move_is_legit_no_text(tabellone, selezione_r, selezione_c, mossa_r, mossa_c)) {
                                    int score = cpu_play_minmax(tabellone, selezione_r, selezione_c, cpu_player, cpu_player, mossa_r, mossa_c, depth);
                                    if (score >= best_score){
                                        best_move[0] = selezione_r;
                                        best_move[1] = selezione_c;
                                        best_move[2] = mossa_r;
                                        best_move[3] = mossa_c;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return best_move;
}

/* Funzione per far eseguire una mossa alla cpu */
void mossa_cpu(tab_t tabellone, char giocatore, int depth){
    int* coordinate =cpu_strategy(tabellone, giocatore, depth);
    int selezione_r = coordinate[0];
    int selezione_c = coordinate[1];
    int mossa_r = coordinate[2];
    int mossa_c = coordinate[3];
    free(coordinate);
    printf("\nMossa CPU selezione_r:%d selezione_c:%d mossa_r:%d mossa_c:%d\n\n", selezione_r, selezione_c, mossa_r, mossa_c);
    mossa(tabellone, giocatore, selezione_r, selezione_c, mossa_r, mossa_c);
}

/* Funzione che gestisce i turni nella modalità vs cpu */
int turno_vs_cpu(tab_t tabellone, char giocatore, int inverso, int depth) {
    if (!(verifica_mosse_legali(tabellone, giocatore))) {
        if (giocatore == GIOCATORE1) {
            printf("\n\nPurtroppo stato sconfitto dal PC DI BILL. Andrà meglio la prossima volta.\n\n Premi 1 per tornare al menù\n");
            int a = 0;
            while (a!=1){
                scanf("%d", &a);
            }
            return 1;
        } else {
            printf("\n\nIl giocatore 1 ha vinto!\n\nPremi 1 per tornare al menù\n");
            int a = 0;
            while (a!=1){
                scanf("%d", &a);
            }
            return 1;
        }
    } else {
        if (inverso) {
            if (giocatore == GIOCATORE1) {
                 printf("\nE il turno del PC DI BILL\n");
                mossa_cpu(tabellone, giocatore, depth);
                return turno_vs_cpu(tabellone, GIOCATORE2, inverso, depth);
            } else {
                 printf("\nE il tuo turno\n");
                print_tab(tabellone);
                interazione_mossa(tabellone, giocatore);
                return turno_vs_cpu(tabellone, GIOCATORE1, inverso, depth);
            }
        } else {
            if (giocatore == GIOCATORE1) {
                 printf("\nE il tuo turno\n");
                print_tab(tabellone);
                interazione_mossa(tabellone, giocatore);
                return turno_vs_cpu(tabellone, GIOCATORE2, inverso, depth);
            } else {
                printf("\nE il turno del PC DI BILL\n");
                mossa_cpu(tabellone, giocatore, depth);
                return turno_vs_cpu(tabellone, GIOCATORE1, inverso, depth);
            }
        }
    }
}

/* --------- MENÙ -------- */

/* Funzione che prende una struct selezione_dati e restituisce i dati con i valori inseriti */
void creazione_dati(menu_d* menu_dati, int dim, int altezza, int depth_cpu, int inverso){
    menu_dati->dimensione_selezionata = dim;
    menu_dati -> altezza_selezionata = altezza;
    menu_dati ->depth_cpu = depth_cpu;
    menu_dati ->tabellone_inverso =inverso;
}

/*Funzione che permette di navigare nel menù di gioco. */
int selezione_menu(menu_d dati_menu) {
    int selezione;
    tab_t tabellone;
    int dimensione_tabellone, altezza_tabellone;
    printf("\n\n\n                                      MINILASKA                                      \n\nBenvenuto in Minilaska!\nPer navigare nel menu, digita il numero associato alla sezione desiderata.\n\n----------------------------------------GIOCA-----------------------------------------\n\n1 - Modalita PVP\n2 - Modalita VS CPU\n\n------------------------------------IMPOSTAZIONI--------------------------------------\n\n3 - Inverti il tabellone\n4 - Cambia la difficolta della CPU\n5 - Modifica le dimensioni del tabellone\n\n----------------------------------------ALTRO-----------------------------------------\n\n6 - Regole del gioco\n7 - Credits\n8 - Chiudi il gioco\n\n\n");
    scanf("%d", &selezione);
    if (selezione == 1) {
        printf("\n\n\n\n");
        if (dati_menu.tabellone_inverso) {
            creazione_tabellone(&tabellone, dati_menu.dimensione_selezionata, dati_menu.altezza_selezionata);
            inizializzazione_tabellone(tabellone);
            inizializzazione_pedine(tabellone);
            turno(tabellone, GIOCATORE2);
            free_celle_tabellone(tabellone);
            selezione_menu(dati_menu);
        } else {
            creazione_tabellone(&tabellone, dati_menu.dimensione_selezionata, dati_menu.altezza_selezionata);
            inizializzazione_tabellone(tabellone);
            inizializzazione_pedine(tabellone);
            turno(tabellone, GIOCATORE1);
            free_celle_tabellone(tabellone);
            selezione_menu(dati_menu);
        }
    }
    if (selezione == 2) {
        creazione_tabellone(&tabellone, dati_menu.dimensione_selezionata, dati_menu.altezza_selezionata);
        inizializzazione_tabellone(tabellone);
        inizializzazione_pedine(tabellone);
        if (dati_menu.tabellone_inverso){
            turno_vs_cpu(tabellone, GIOCATORE2, dati_menu.tabellone_inverso, dati_menu.depth_cpu);
        }else{
            turno_vs_cpu(tabellone, GIOCATORE1, dati_menu.tabellone_inverso, dati_menu.depth_cpu);
        }
        free_celle_tabellone(tabellone);
        selezione_menu(dati_menu);
    }
    if (selezione == 3) {
        if (dati_menu.tabellone_inverso) {
            int ciclo = 1;
            printf("Vuoi ritornare alla versione originale? Y/N\n");
            while (ciclo) {
                char inverso;
                scanf("%c", &inverso);
                if (inverso == 'N') {
                    ciclo = 0;
                    selezione_menu(dati_menu);
                }
                if (inverso == 'Y') {
                    dati_menu.tabellone_inverso = 0;
                    ciclo = 0;
                    selezione_menu(dati_menu);
                }
            }
        } else {
            int ciclo = 1;
            printf("Vuoi invertire il tabellone? Y/N\n");
            while (ciclo) {
                char inverso;
                scanf("%c", &inverso);
                if (inverso == 'N') {
                    ciclo = 0;
                    selezione_menu(dati_menu);
                }
                if (inverso == 'Y') {
                    dati_menu.tabellone_inverso = 1;
                    ciclo = 0;
                    selezione_menu(dati_menu);
                }
            }
        }
    }
    if (selezione == 4) {
        printf("\nSeleziona la diffocolta di gioco digitando un numero maggiore o uguale a 1 (maggiore sarà il numero e maggiore sarà la difficoltà, di default la diffcolta e settata a 8).\n\n");
        int a = -1;
        while (a < 1) {
            scanf("%d", &a);
        }
        dati_menu.depth_cpu = a;
        selezione_menu(dati_menu);
    }
    if (selezione == 5) {
        printf("\nSeleziona le dimensioni del tabellone digitando un numero dispari maggiore o uguale a 3 (di default la grandezza e settata a 7).\n\n");
        int a;
        int ciclo;
        do{
            scanf("%d", &a);
        }while ((a < 3)&&(a%2==0));
        dati_menu.dimensione_selezionata = a;
        printf("\nSeleziona l'altezza delle pedine digitando un numero maggiore o uguale a 1 (di default l'altezza e settata a 3).\n\n");
        int b;
        do{
            scanf("%d", &b);
        }while (b < 1);
        dati_menu.altezza_selezionata = b;
        selezione_menu(dati_menu);
    }
    if (selezione == 6) {
        printf("\n\nMinlaska e una variante della dama.\nLo scopo del gioco e vincere non facendo avere piu mosse disponibili all'aversario.\nIl gioco si alterna in turni tra 2 giocatori dove si e obbligati a muovere una propria torre sul tabellone.\nOgni torre e formata da una pila di pedine, la quale piu alta ne indica il giocatore di appartenenza della torre\nOgni torre puo soltato muoversi in diagonale di 1 casella.\nLe torri fin quando non vengono promosse, raggiungendo l'estremo del tabellone, possono soltanto muoversi in avanti.\n\nConquista\n\nE possibile conquistare le torri avversarie solamente se siano in prossimita diagonale di una casella, muovendo la torre nella stessa diagonale di 2 caselle qualora la casella di destinazione sia vuota.\nLa conquista assegna la pedina maggiormente soprastante della torre conquistata alla parte piu sottostante della torre conquistatrice.\nSe la torre conquistatriche ha gia raggiunto il limite massimo di altezza delle torri, la pedina soprastante della torre conquistata invece scomparira dal tabellone.");
        printf("\n\nPremi 1 per tornare al menu\n");
        int a = 0;
        while (a != 1) {
            scanf("%d", &a);
        }
        selezione_menu(dati_menu);
    }
    if (selezione == 7) {
        printf("\nCreato da Massimiliano Fardo. 2021");
        printf("\n\nPremi 1 per tornare al menu\n");
        int a = 0;
        while (a != 1) {
            scanf("%d", &a);
        }
        selezione_menu(dati_menu);
    }
    if (selezione == 8) {
        return 1;
    }
    if ((selezione > 8) || (selezione < 1)) {
        return selezione_menu(dati_menu);
    }
}

/* Menù di gioco */
void menu(void){
    menu_d menu;
    creazione_dati(&menu, 7, 3, 8, 0);
    selezione_menu(menu);
}
