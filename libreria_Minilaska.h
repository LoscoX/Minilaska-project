/**
* @file libreria_Minilaska.h
* @author Massimiliano Fardo
* @brief Funzioni del gioco Minilaska
* @date 17/01/2021
*/

/**
 * Data struct contenenti i valori del tabellone di gioco.
 */
typedef struct tab tab_t;

/**
 * Data struct contenenti i valori delle impostazioni del menù di gioco.
 */
typedef struct selezione_dati menu_d;


/*--------------------------------------------*/

/**
 * Funzione per liberare la memoria dalle celle del tabellone.
 * @param tabellone
 */
 void free_celle_tabellone(tab_t tabellone);

/**
 * Funzione che prende una struct tab e restituisce il tabellone con i valori inseriti
 * @param tabellone
 * @param dim
 * @param altezza
 */
 void creazione_tabellone(tab_t* tabellone, int dim, int altezza);

/**
 * Funzione che restituisce l'indirizzo della cella voluta del tabellone date in input le sue coordinate.
 * @param tabellone
 * @param selezione_r
 * @param selezione_c
 * @param selezione_h
 * @return Indirizzo di memoria della cella dell'array del tabellone.
 */
char* posizione(tab_t tabellone, int selezione_r, int selezione_c, int selezione_h);

/**
 * Funzione che restituisce l'indirizzo della cella voluta del tabellone date in input le sue coordinate e di quanto ci si vuole spostare da esse.
 * @param tabellone
 * @param selezione_r
 * @param selezione_c
 * @param selezione_h
 * @param shift_r
 * @param shift_c
 * @param shift_h
 * @return Indirizzo di memoria della cella dell'array del tabellone.
 */
char* posizione_shift(tab_t tabellone, int selezione_r, int selezione_c, int selezione_h, int shift_r, int shift_c, int shift_h);


/**
 * Funzione per inizializzare tabellone.
 * @param tabellone
 */
void inizializzazione_tabellone(tab_t tabellone);

/*  */
/**
 * Funzione per inizializzare le pedine.
 * @param tabellone
 */
void inizializzazione_pedine(tab_t tabellone);

/*  */
/**
 * Funzione che stampa il tabellone.
 * @param tabellone
 */
void print_tab(tab_t tabellone);

/*  */
/**
 * Funzione per determinare a che giocatore appartiene la pedina.
 * @param tabellone
 * @param selezione_r
 * @param selezione_c
 * @return Giocatore 1 o Giocatore 2.
 */
int scorrimento(tab_t tabellone, int selezione_r, int selezione_c);

/*  */
/**
 * Funzione per determinare se una pedina è promossa.
 * @param tabellone
 * @param selezione_r
 * @param selezione_c
 * @return vero o falso (int 1 o 0).
 */
int verify_promotion(tab_t tabellone, int selezione_r, int selezione_c);

/*  */
/**
 * Funzione per determinare se una determinata casella non contiene pedine.
 * @param tabellone
 * @param selezione_r
 * @param selezione_c
 * @return vero o falso (int 1 o 0).
 */
int verify_nullo(tab_t tabellone, int selezione_r, int selezione_c);

/*  */
/**
 * Funzione per determinare se una determinata casella non è utilizzabile.
 * @param tabellone
 * @param selezione_r
 * @param selezione_c
 * @return vero o falso (int 1 o 0).
 */
int verify_vuoto(tab_t tabellone, int selezione_r, int selezione_c);

/*  */
/**
 * Funzione per determinare se la pedina selezionata dal giocatore abbia mosse legali disponibili.
 * @param tabellone
 * @param giocatore
 * @param selezione_r
 * @param selezione_c
 * @return vero o falso (int 1 o 0).
 */
int verifica_mosse_pedina(tab_t tabellone, char giocatore, int selezione_r, int selezione_c);

/*  */
/**
 * Funzione per verificare se il giocatore disponga di pedine aventi mosse legali disponibili.
 * @param tabellone
 * @param giocatore
 * @return vero o falso (int 1 o 0).
 */
int verifica_mosse_legali(tab_t tabellone, char giocatore);

/*  */
/**
 * Funzione per calcolare l'altezza di una determinata torre.
 * @param tabellone
 * @param selezione_r
 * @param selezione_c
 * @return Altezza della torre delle cordinate scelte.
 */
int altezza_counter(tab_t tabellone, int selezione_r, int selezione_c);

/*  */
/**
 * Funzione per promuovere le pedine.
 * @param tabellone
 * @param coordinata_r
 * @param coordinata_c
 */
void promotion(tab_t tabellone, int coordinata_r, int coordinata_c);

/*  */
/**
 * Funzione per promuovere una pedina quando raggiunge un estremo del tabellone.
 * @param tabellone
 * @param mossa_r
 * @param mossa_c
 * @param giocatore
 */
void promotion_ext(tab_t tabellone, int mossa_r, int mossa_c, char giocatore);

/*  */
/**
 * Funzione per selezione le coordinate di una pedina.
 * @param tabellone
 * @param giocatore
 * @param coordinate_selezione
 * @return Vero o Falso (1 o 0).
 */
int selezione_coordinate_partenza(tab_t tabellone, char giocatore, int* coordinate_selezione);

/*  */
/**
 * Funzione per determinare se una mossa selezionata sia legale.
 * @param tabellone
 * @param coordinate_selezione
 * @param coordinate_mossa
 * @return Vero o Falso (1 o 0).
 */
int move_is_legit(tab_t tabellone, int* coordinate_selezione, int* coordinate_mossa);

/*  */
/**
 * Funzione per selezionare la destinazione di una pedina.
 * @param tabellone
 * @param coordinate_selezione
 * @param coordinate_mossa
 * @return Vero o Falso (1 o 0).
 */
int selezione_coordinate_arrivo(tab_t tabellone, int* coordinate_selezione, int* coordinate_mossa);

/* */
/**
 * Funzione per scegliere le coordinate di una pedina.
 * @param tabellone
 * @param coordinate_selezione
 * @param coordinate_mossa
 * @param giocatore
 */
void coordinate(tab_t tabellone, int* coordinate_selezione, int* coordinate_mossa, char giocatore);

/*  */
/**
 * Funzione per spostare una pedina senza conquista.
 * @param tabellone
 * @param selezione_r
 * @param selezione_c
 * @param mossa_r
 * @param mossa_c
 */
void spostamento_semplice(tab_t tabellone, int selezione_r, int selezione_c, int mossa_r, int mossa_c);

/*  */
/**
 * Funzione per rimuovere una pedina conquistata. Le coordinate fanno riferimento alla pedina selezionata per compiere la conquista.
 * @param tabellone
 * @param selezione_r
 * @param selezione_c
 * @param mossa_r
 * @param mossa_c
 */
void rimozione_pedina(tab_t tabellone, int selezione_r, int selezione_c, int mossa_r, int mossa_c);

/* */
/**
 * Funzione per spostare una pedina alta meno del massimo consentito con conquista.
 * @param tabellone
 * @param selezione_r
 * @param selezione_c
 * @param mossa_r
 * @param mossa_c
 */
void spostamento_conquista(tab_t tabellone, int selezione_r, int selezione_c, int mossa_r, int mossa_c);

/* */
/**
 * Funzione per spostare una pedina alta pari al massimo consentito con conquista.
 * @param tabellone
 * @param selezione_r
 * @param selezione_c
 * @param mossa_r
 * @param mossa_c
 */
void spostamento_conquista_max(tab_t tabellone, int selezione_r, int selezione_c, int mossa_r, int mossa_c);

/* */
/**
 * Funzione che muove le pedine.
 * @param tabellone
 * @param selezione_r
 * @param selezione_c
 * @param mossa_r
 * @param mossa_c
 */
void spostamento_pedina(tab_t tabellone, int selezione_r, int selezione_c, int mossa_r, int mossa_c);

/*  */
/**
 * Funzione che esegue una determinata mossa.
 * @param tabellone
 * @param giocatore
 * @param selezione_r
 * @param selezione_c
 * @param mossa_r
 * @param mossa_c
 */
void mossa(tab_t tabellone, char giocatore, int selezione_r, int selezione_c, int mossa_r, int mossa_c);

/*  */
/**
 * Funzione per far eseguire una mossa a un determinato giocatore.
 * @param tabellone
 * @param giocatore
 */
void interazione_mossa(tab_t tabellone, char giocatore);

/*  */
/**
 * Funzione ricorsiva che determina i turni dei giocatori e fa terminare il gioco non appena uno vince.
 * @param tabellone
 * @param giocatore
 * @return 1, la funzione genera un int solamente per consentirne la ricorsione.
 */
int turno(tab_t tabellone, char giocatore);

/* -------------MODALITÀ VS CPU------------- */

/*  */
/**
 * Funzione che calcola il numero di torri appartenenti al giocatore.
 * @param tabellone
 * @param giocatore
 * @return Numero di torri appartenenti al giocatore.
 */
int counter_pedine_giocatore(tab_t tabellone, char giocatore);

/*  */
/**
 * Funzione che calcola il numero di torri promosse del giocatore.
 * @param tabellone
 * @param giocatore
 * @return Numero di torri promosse appartenenti al giocatore.
 */
int counter_pedine_promosse(tab_t tabellone, char giocatore);

/*  */
/**
 * Funzione che trova la pedina più alta del giocatore.
 * @param tabellone
 * @param giocatore
 * @return indirizzo di memoria dello hype contenente del valore un array di 2 int.
 */
int* pedina_max_player(tab_t tabellone, char giocatore);

/*  */
/**
 * Funzione che calcola il valore della pedina più alta del giocatore.
 * @param tabellone
 * @param giocatore
 * @return Altezza della pedina più alta del giocatore selezionato.
 */
int pedina_max_value(tab_t tabellone, char giocatore);

/*  */
/**
 * Funzione che calcola il numero di pedine appartenenti al giocatore aventi una altezza >= alla pedina più alta dell'avversario.
 * @param tabellone
 * @param giocatore
 * @return numero di pedine appartenenti al giocatore aventi una altezza >= alla pedina più alta dell'avversario.
 */
int counter_pedine_maggiori_max(tab_t tabellone, char giocatore);

/*  */
/**
 * Funzione che valuta il punteggio di una mossa dell'intelligenza artificiale.
 * @param tabellone
 * @param giocatore
 * @return punteggio di una mossa dell'intelligenza artificiale.
 */
int score_ai(tab_t tabellone, char giocatore);

/*  */
/**
 * Funzione che dato un tabellone ne genera una sua copia.
 * Attenzione: la copia occupa memoria aggiuntiva nello hype.
 * si prega di usare free_celle_tabellone, per liberarla, quando non se ne fa più uso.
 * @param tabellone
 * @return Copia del tabellone dato in input.
 */
tab_t tab_copy(tab_t tabellone);

/*  */
/**
 * Funzione ricorsiva che restituisce il tabellone con effettuata la prima mossa disponibile di una pedina specifica del giocatore.
 * Attenzione: la mossa occupa memoria aggiuntiva nello hype.
 * si prega di usare free_celle_tabellone, per liberarla, quando non se ne fa più uso.
 * @param tabellone
 * @param giocatore
 * @param selezione_r
 * @param selezione_c
 * @param mossa_r
 * @param mossa_c
 * @return Copia del tabellone dato in input con effettuata la mossa.
 */
tab_t first_move_avaible(tab_t tabellone, char giocatore,int selezione_r, int selezione_c, int mossa_r, int mossa_c);

/*  */
/**
 * Funzione che calcola il numero totale di mosse disponibili per una pedina.
 * @param tabellone
 * @param selezione_r
 * @param selezione_c
 * @return Numero totale di mosse disponibili per una pedina.
 */
int numero_mosse_disponibili_pedina(tab_t tabellone, int selezione_r, int selezione_c);

/*  */
/**
 * Funzione che calcola il numero totale di mosse disponibili per il giocatore in un turno.
 * @param tabellone
 * @param giocatore
 * @return Numero totale di mosse disponibili per il giocatore in un turno.
 */
int numero_mosse_disponibili_giocatore(tab_t tabellone, char giocatore);

/*  */
/**
 * Funzione che assegna uno score ad possibile mossa di ogni possibile pedina che può essere effettuata dalla cpu.
 * @param tabellone
 * @param selezione_r
 * @param selezione_c
 * @param cpu_player
 * @param turno
 * @param mossa_r
 * @param mossa_c
 * @param depth
 * @return Lo score più alto.
 */
int cpu_play_minmax(tab_t tabellone, int selezione_r, int selezione_c, char cpu_player, char turno, int mossa_r, int mossa_c, int depth);

/*  */
/**
 * Funzione che fa scegliere alla cpu quale pedina muovere e in quale casella.
 * @param tabellone
 * @param cpu_player
 * @param depth
 * @return Indirizzo di memoria contenente un array contente le coordinate della selezione della pedina e quelle della mossa da effettuare.
 */
int* cpu_strategy(tab_t tabellone, char cpu_player, int depth);

/*  */
/**
 * Funzione per far eseguire una mossa alla cpu.
 * @param tabellone
 * @param giocatore
 * @param depth
 */
void mossa_cpu(tab_t tabellone, char giocatore, int depth);

/*  */
/**
 * Funzione che gestisce i turni nella modalità vs cpu.
 * @param tabellone
 * @param giocatore
 * @param inverso
 * @param depth
 * @return 1, la funzione genera un int solamente per consentirne la ricorsione.
 */
int turno_vs_cpu(tab_t tabellone, char giocatore, int inverso, int depth);

/* --------- MENÙ -------- */

/*  */
/**
 * Funzione che prende una struct selezione_dati e restituisce i dati con i valori inseriti.
 * @param menu_dati
 * @param dim
 * @param altezza
 * @param depth_cpu
 * @param inverso
 */
void creazione_dati(menu_d* menu_dati, int dim, int altezza, int depth_cpu, int inverso);

/* */
/**
 * Funzione che permette di navigare nel menù di gioco.
 * @param dati_menu
 * @return 1, la funzione genera un int solamente per consentirne la ricorsione.
 */
int selezione_menu(menu_d dati_menu);

/*  */
/**
 * Menù di gioco.
 */
void menu(void);


#ifndef MINILASKA_LIBRERIA_MINILASKA_H
#define MINILASKA_LIBRERIA_MINILASKA_H

#endif //MINILASKA_LIBRERIA_MINILASKA_H
