#include <stdio.h>
#include <stdlib.h>
#include <matrix.h>
#include <imagen.h>
#include <morfologia.h>
#include <convolucion.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <math.h>
#include <canny.h>
#include <string.h>

int main()
{
    int **elemento_x,**elemento_y,**filtro;
    int fase_x,fase_y,fase_filtro;
    int **gx,**gy;
    int **imagen,**imagen_filtrada,**imagen_final;
    int **supresion,**histe;
    int **direccion;
    int maximo;
    char canny[20] = "canny";
    char nombre[20] = "fotodr.bmp";

    ta_ele ta_x,ta_y,ta_filtro;
    Mat ima,ima_filtrada,ima_final,ima_supresion,ima_histeresis;

    char nombre_x[20] = "prewitt_x.txt";
    char nombre_y[20] = "prewitt_y.txt";
    char nombre_filtro[20] = "filtro.txt";

    cvNamedWindow("Imagen",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Imagen filtrada",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Imagen procesada",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Imagen supresion",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Imagen histeresis",CV_WINDOW_AUTOSIZE);

    ima = imread(nombre,CV_LOAD_IMAGE_GRAYSCALE);

    elemento_x = crear_mascara(nombre_x,&ta_x.row,&ta_x.col);
    elemento_y = crear_mascara(nombre_y,&ta_y.row,&ta_y.col);
    filtro = crear_mascara(nombre_filtro,&ta_filtro.row,&ta_filtro.col);

    fase_x = obtener_fase_matrix(ta_x.col);
    fase_y = obtener_fase_matrix(ta_y.col);
    fase_filtro = obtener_fase_matrix(ta_filtro.col);

    imagen = convertir_vector_imagen_a_matrix(ima);
    imagen_filtrada = convolucion_filtro_gauseano(imagen,filtro,fase_filtro,ima.rows,ima.cols,273);


    gx = crear_matrix(ima.rows,ima.cols);
    gy = crear_matrix(ima.rows,ima.cols);

    gx = convolucion_con_mascaras(imagen,elemento_x,fase_x,ima.rows,ima.cols);
    //imprimir_matrix_consola(gx,ima.rows,ima.cols);
    gy = convolucion_con_mascaras(imagen,elemento_y,fase_y,ima.rows,ima.cols);

    direccion = direccion_pixel(gx,gy,ima.rows,ima.cols);
    //imprimir_matrix_consola(direccion,ima.rows,ima.cols);

    imagen_final = suma_matrices(gx,gy,ima.rows,ima.cols,&maximo);
    normalizar_matrix(imagen_final,maximo,255,ima.rows,ima.cols);


    ima_filtrada = crear_imagen(imagen_filtrada,ima.rows,ima.cols);
    ima_final = crear_imagen(imagen_final,ima.rows,ima.cols);

    supresion = supresion_maximos(imagen_final,direccion,ima.rows,ima.cols,fase_x);
    ima_supresion = crear_imagen(supresion,ima.rows,ima.cols);
    //imprimir_matrix_consola(supresion,ima.rows,ima.cols);

    histe = histeresis(supresion,ima.rows,ima.cols,10,30,fase_x);
    ima_histeresis = crear_imagen(histe,ima.rows,ima.cols);
    strcat(canny,nombre);

    imwrite(canny,ima_histeresis);

    imshow("Imagen",ima);
    imshow("Imagen filtrada",ima_filtrada);
    imshow("Imagen procesada",ima_final);
    imshow("Imagen supresion",ima_supresion);
    imshow("Imagen histeresis",ima_histeresis);

    cvWaitKey(0);

    liberar_memoria(elemento_x,ta_x.row);
    liberar_memoria(elemento_y,ta_y.row);
    liberar_memoria(imagen,ima.rows);
    liberar_memoria(gx,ima.rows);
    liberar_memoria(gy,ima.rows);
    liberar_memoria(imagen_final,ima.rows);
    liberar_memoria(supresion,ima.rows);
    liberar_memoria(histe,ima.rows);

    return 0;
}
