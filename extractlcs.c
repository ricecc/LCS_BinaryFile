//
// Created by Riccardo on 09/06/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "extractlcs.h"
#define DEFAULT_BUFFER_SIZE 512



void startLcs(lcs_str* lcsStr,LCS_matrix* matrix,char* bufferFirst, char* bufferSecond ) {
    char *bufferOutput = malloc(lcsStr->buffer_size);
    //inizialize matrix
    inizializeMatrix(matrix);
    //BUILD LCS
    buildLcs(matrix,bufferFirst,bufferSecond);
    //print lcs
    bufferOutput = printLcs(matrix, bufferFirst,bufferSecond);
    //writeToOutputFile
    writeToOutput(lcsStr,bufferOutput);


    printf("First String: %s\n",bufferFirst);
    printf("Second String: %s\n",bufferSecond);
    printf("LCS: %s", bufferOutput);


    free(bufferFirst);
    free(bufferSecond);
    free(bufferOutput);
}


void inizializeMatrix(LCS_matrix* lcsMatrix){
    int i;
    for(i=0; i<=lcsMatrix->seconfStringLenght;i++){
        lcsMatrix->matrix[0][i]=0;
    }

    for(i=0; i<=lcsMatrix->firstStringLenght;i++){
        lcsMatrix->matrix[i][0]=0;
    }
}

void buildLcs(LCS_matrix* lcsMatrix, char* bufferFirst, char* bufferSecond){
    int i,j;
    for (i = 1; i <= lcsMatrix->firstStringLenght; i++)
        for (j = 1; j <= lcsMatrix->seconfStringLenght; j++) {
            if (bufferFirst[i - 1] == bufferSecond[j - 1]) {
                lcsMatrix->matrix[i][j] = lcsMatrix->matrix[i - 1][j - 1] + 1;
            } else if (lcsMatrix->matrix[i - 1][j] >= lcsMatrix->matrix[i][j - 1]) {
                lcsMatrix->matrix[i][j] = lcsMatrix->matrix[i - 1][j];
            } else {
                lcsMatrix->matrix[i][j] = lcsMatrix->matrix[i][j - 1];
            }
        }
}

char* printLcs(LCS_matrix* matrix, char* bufferFirst, char* bufferSecond){
    int index = matrix->matrix[matrix->firstStringLenght][matrix->seconfStringLenght];
    char* output = malloc(index + 1);
    output[index] = '\0';

    while (matrix->firstStringLenght > 0 && matrix->seconfStringLenght > 0) {
        if (bufferFirst[matrix->firstStringLenght - 1] == bufferSecond[matrix->seconfStringLenght - 1]) {
            output[index - 1] = bufferFirst[matrix->firstStringLenght - 1];
            matrix->firstStringLenght--;
            matrix->seconfStringLenght--;
            index--;
        }else if (matrix->matrix[matrix->firstStringLenght - 1][matrix->seconfStringLenght] > matrix->matrix[matrix->firstStringLenght][matrix->seconfStringLenght - 1]) {
            matrix->firstStringLenght--;
        }else {
            matrix->seconfStringLenght--;
        }
    }
    return output;
}

void writeToOutput(lcs_str* lcsStr, char* output){
    int n = strlen(output);
    int dl = fwrite(output,sizeof(output),n,lcsStr->outputFile);
    if(dl == 0){
        perror("Nessuna LCS presente tra le due stringhe");
    }
}

void fillBufferString( FILE* file, char* bufferString , long buffer_size){
    int dl;
    for(;;){
        dl=fread(bufferString,1,buffer_size,file);
        if(dl==0) break;
    }
}

void controller(char* firstFIle,char* secondFile, char* outputFile){
    lcs_str* lcsStr = openFiles(firstFIle,secondFile,outputFile, DEFAULT_BUFFER_SIZE);
    char *bufferFirst = malloc(lcsStr->buffer_size);
    char *bufferSecond = malloc(lcsStr->buffer_size);
    fillBufferString(lcsStr->firstFile, bufferFirst, lcsStr->buffer_size);
    fillBufferString(lcsStr->secondFile, bufferSecond, lcsStr->buffer_size);
    LCS_matrix* matrix = allocMatrix(bufferFirst, bufferSecond);
    startLcs(lcsStr,matrix,bufferFirst,bufferSecond);
    free(bufferFirst);
    free(bufferSecond);
    closeAndFree(lcsStr,matrix);
}

void closeAndFree(lcs_str * lcsStr, LCS_matrix* lcsMatrix) {
    if (lcsStr != NULL) {
        free(lcsStr->bufferFirstString);
        free(lcsStr->bufferSecondString);
        free(lcsMatrix->matrix);
        fclose(lcsStr->firstFile);
        fclose(lcsStr->secondFile);
        fclose(lcsStr->outputFile);
        free(lcsStr);
    }
}


FILE* open_output_file(char *name) {
    FILE* file = fopen(name,"wb");
    if (file == NULL) {
        perror("Errore nell'apertura del file.");
        exit(-1);
    }
    return file;
}



lcs_str* allocStr(FILE* firstFile, FILE* secondFile, FILE* outputFile, long buffer_size){
    lcs_str* lcsStr = malloc(sizeof(lcs_str));
    lcsStr->firstFile=firstFile;
    lcsStr->secondFile= secondFile;
    lcsStr->outputFile = outputFile;
    lcsStr->buffer_size=buffer_size;
    lcsStr->bufferFirstString= malloc(buffer_size);
    lcsStr->bufferSecondString= malloc(buffer_size);
    lcsStr->bufferLimitFirstFile= fread(lcsStr->bufferFirstString,1,lcsStr->buffer_size, lcsStr->firstFile);
    lcsStr->bufferLimistSecondFile= fread(lcsStr->bufferSecondString,1,lcsStr->buffer_size,lcsStr->secondFile);
    if(lcsStr->bufferLimitFirstFile==0 || lcsStr->bufferLimistSecondFile==0){
        perror("Il file è vuoto");
        return NULL;
    }
    fseek(lcsStr->firstFile,0L,SEEK_SET);
    fseek(lcsStr->secondFile,0L,SEEK_SET);
    return lcsStr;
}

LCS_matrix* allocMatrix(char* bufferFirstString, char* bufferSecondString){
    LCS_matrix* lcsMatrix = malloc(sizeof (LCS_matrix));
    lcsMatrix->firstStringLenght = strlen(bufferFirstString);
    lcsMatrix->seconfStringLenght = strlen(bufferSecondString);
    lcsMatrix->row = lcsMatrix->firstStringLenght + 1;
    lcsMatrix->colum= lcsMatrix->seconfStringLenght + 1;
    int i;
    lcsMatrix->matrix=(int**)malloc( lcsMatrix->row *sizeof(int *));
    for( i=0;i<lcsMatrix->row;i++){
        lcsMatrix->matrix[i]= malloc(lcsMatrix->colum *sizeof (int));
    }
    return lcsMatrix;
}


lcs_str* openFiles(char* firstFile,char* secondFile,char* outputFile, long buffer_size){
    FILE* first = fopen(firstFile,"rb");
    FILE* second = fopen(secondFile,"rb");
    FILE* output = fopen(outputFile,"wb");

    if (first == NULL || second == NULL || output == NULL) {
        perror("Errore nell'apertura del file!");
        return NULL;
    }
    return allocStr(first,second,output,buffer_size);
}