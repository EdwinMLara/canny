#ifndef CANNY
#define CANNY
#define pi 3.14159

#include <stdio.h>
#include <stdlib.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <matrix.h>
#include <imagen.h>
#include <math.h>

int** direccion_pixel(int **gx,int **gy,int row, int col){
    int i,k;
    int **m;
    double aux;
    int aux1,aux2;
    m = crear_matrix(row,col);
    for(i=0;i<row;i++){
        for(k=0;k<col;k++){
            if(gx[i][k]==0){
               m[i][k] = 90;
            }
            else{
                aux1 = gx[i][k];
                aux2 = gy[i][k];
                aux = (double) aux2 / aux1 ;
                aux = atan(aux);
                aux = (aux*180)/pi;
                m[i][k] = aux;
            }
        }
    }
    return m;
}

int** supresion_maximos(int **imagen,int** direccion,int row,int col,int fase){
    int i,k,angulo;
    int **m;
    m = crear_matrix(row,col);
    for(i=fase;i<row-fase;i++){
        for(k=fase;k<col-fase;k++){

            if(direccion[i][k] > 0 && direccion[i][k] <= 23)
                angulo = 0;
            else if(direccion[i][k] > 23 && direccion[i][k] <= 68)
                angulo = 45;
            else if(direccion[i][k] > 68 && direccion[i][k] <= 113)
                angulo = 90;
            else
                angulo = 135;

            switch (angulo){
                case 0:
                    if(imagen[i][k-fase]<imagen[i][k] && imagen[i][k] > imagen[i][k+fase])
                        m[i][k] = imagen[i][k];
                    else
                        m[i][k] = 0;
                    break;
                case 45:
                    if(imagen[i-fase][k+fase]<imagen[i][k] && imagen[i][k] > imagen[i+fase][k-fase])
                        m[i][k] = imagen[i][k];
                    else
                        m[i][k] = 0;
                    break;
                case 90:
                    if(imagen[i-fase][k] < imagen[i][k] && imagen[i][k] > imagen[i+fase][k])
                        m[i][k] = imagen[i][k];
                    else
                        m[i][k] = 0;
                    break;
                case 135:
                    if(imagen[i-fase][k-fase]<imagen[i][k] && imagen[i][k] > imagen[i+fase][k+fase])
                        m[i][k] = imagen[i][k];
                    else
                        m[i][k] = 0;
                    break;
            }

        }
     }
    return m;
}

int** histeresis(int** imagen,int row,int col,int hum_menor,int hum_mayor,int fase){
    int i,k,romper,aux1,aux2;
    int **m;
    m = crear_matrix(row,col);
    romper = 0;
    for(i=fase;i<row-fase;i++){
        for(k=fase;k<col-fase;k++){

            if(imagen[i][k]>hum_menor && imagen[i][k]<hum_mayor)
            {
                for(aux1=i-fase;aux1<=i+fase;aux1++){
                    for(aux2=k-fase;aux2<=k+fase;aux2++){
                        if(imagen[aux1][aux2] > hum_mayor){
                            m[i][k] = 255;
                            romper = 1;
                            break;
                        }
                    }
                    if(romper == 1)
                        break;
                }
            }
            else if(imagen[i][k] > hum_mayor)
                m[i][k] = 255;
        }
    }
    return m;
}

#endif // CANNY

