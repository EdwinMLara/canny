#ifndef MATRIX
#define MATRIX

#include <stdio.h>
#include <stdlib.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

using namespace cv;
using namespace std;

int** crear_matrix(int filas,int columnas){
    int i,k,**m;
    m = (int**)malloc(filas*sizeof(int*));
    for(i=0;i<filas;i++)
        m[i] = (int*)malloc(columnas*sizeof(int));

    for(i=0;i<filas;i++)
        for(k=0;k<columnas;k++)
            m[i][k] = 0;

    return m;
}

void liberar_memoria (int **m,int filas){
    int i;
    for(i=0;i<filas;i++){
        free(m[i]);
    }
    free(m);
}

int* crear_vector(int ta){
    int *vec,i;
    vec = (int*)malloc(ta*sizeof(int));

    for(i=0;i<ta;i++)
        vec[i]=i;
    return vec;
}

void imprimir_matrix_consola(int **m,int filas,int columnas){
    int i,k;
    for(i=0;i<filas;i++){
        for(k=0;k<columnas;k++){
            printf("%d ",m[i][k]);
        }
        printf("\n");
    }
}

int** convertir_vector_imagen_a_matrix(Mat ima){
    int i,k;
    int **matrix;
    matrix = crear_matrix(ima.rows,ima.cols);
    for(i=0;i<ima.rows;i++)
        for(k=0;k<ima.cols;k++)
        {
            matrix[i][k] = ima.data[ima.cols*i + k];
        }
    return matrix;
}

void normalizar_matrix(int **ma,int maximo,int valor,int row,int col){
    int i,k;
    float aux;
    for(i=0;i<row;i++){
        for(k=0;k<col;k++){
            aux = (float) ma[i][k] / maximo;
            aux = aux*valor;
            ma[i][k] = (int) aux;
        }
    }
}

void llenar_matrix_aleatorios(int **ma,int row,int col){
    int i,k;
    for(i=0;i<row;i++){
        for(k=0;k<col;k++){
            ma[i][k] = rand()%11;
        }
    }
}

#endif // MATRIX

