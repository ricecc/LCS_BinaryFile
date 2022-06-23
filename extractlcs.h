//
// Created by Riccardo on 09/06/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef RICCARDOCECCARANI109327_EXTRACTLCS_H
#define RICCARDOCECCARANI109327_EXTRACTLCS_H

typedef struct str_lcs {
   long bufferLimitFirstFile;
   long bufferLimistSecondFile;
   char* bufferFirstString;
   char* bufferSecondString;
   FILE* secondFile;
   FILE* firstFile;
   FILE* outputFile;
   long buffer_size;
}lcs_str;

typedef struct matrix_LCS{
    int** matrix;
    int row;
    int colum;
    int firstStringLenght;
    int seconfStringLenght;
}LCS_matrix;

/**
 * Alloca in memoria la struct usata per raggruppare le variabili relative ai file di input e output
 * @param firstFile
 * @param secondFile
 * @param outputFile
 * @param buffer_size
 * @return puntatore alla struct allocata
 */
lcs_str* allocStr(FILE* firstFile, FILE* secondFile,FILE* outputFile, long buffer_size);

/**
 * metodo usato per l'apertura dei file di input e output. Passa i paramtri al metodo allocStr().
 * @param firstFIle
 * @param secondFile
 * @param outputFile
 * @param buffer_size
 * @return puntatore alla struct
 */
lcs_str* openFiles(char* firstFIle, char* secondFile,char* outputFile, long buffer_size);

/**
 * Usato
 * @param firstFIle
 * @param secondFile
 * @param outputFile
 */
void controller(char* firstFIle, char* secondFile, char* outputFile);

/**
 * Metodo che da il via all'algoritmo LCS richiamando al suo interno i metodo per inizializzare la matrice,costruire la lcs e stampare la
 * lcs
 * @param lcsStr
 * @param lcsMatrix
 * @param bufferFirst
 * @param bufferSecond
 */
void startLcs(lcs_str* lcsStr,LCS_matrix * lcsMatrix,char* bufferFirst, char* bufferSecond);


/**
 * Creare una tabella di dimensioni n+1*m+1 in cui n e m sono le lunghezze di bufferFirstString e bufferSecondString
 * @param bufferFirstString
 * @param bufferSecondString
 * @return puntatore alla matrice allocata.
 */
LCS_matrix* allocMatrix(char* bufferFirstString, char* bufferSecondString);


/**
 * Inizializza la matrice. La prima riga e la prima colonna sono riempite con zeri.
 * @param matrix
 */
void inizializeMatrix(LCS_matrix* matrix);

/**
 *Costruisce la LCS seguendo la seguente logica. Se il carattere corrispondente alla riga e alla colonna correnti
 * corrispondono. riempire la cella corrente aggiungendo uno all elemento diagonale.Punta una freccia sulla cella diagonale.
 * Altrimenti prendi il valore massimo dalla colonna precedente e dall elemento della riga precedente per riempire la cella
 * corrente. Punta una freccia con la cella con il valore massimo. Il valore dell ultima riga e dell ultima colonna rappresenta
 * la lunghezza della sottosequenza comune pi&ugrave lunga.
 * @param matrix
 * @param bufferFirst
 * @param bufferSecond
 */
void buildLcs(LCS_matrix* matrix, char* bufferFirst, char* bufferSecond);


/**
 * Usata per trovare la sottosequenza comune più lunga, parti dall ultimo elemento e segui la direzione delle freccia
 * @param matrix
 * @param bufferFirst
 * @param bufferSecond
 * @return
 */
char* printLcs(LCS_matrix* matrix, char* bufferFirst, char* bufferSecond);

/**
 * Scrive la LCS nel file di outpu
 * @param lcsStr
 * @param output
 */
void writeToOutput(lcs_str* lcsStr, char* output);
void closeAndFree(lcs_str * lcsStr, LCS_matrix* matrix);
void fillBufferString( FILE* file, char* bufferString, long buffer_size );



#endif //RICCARDOCECCARANI109327_EXTRACTLCS_H
