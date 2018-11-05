#ifndef IMAGEN
#define IMAGEN

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

using namespace cv;
using namespace std;

Mat crear_imagen(int **m,int row,int col){
    Mat frame = cvCreateImage(cvSize(col, row), IPL_DEPTH_8U, 1);
    int *vectorImagne,i,k;

    vectorImagne = (int*)malloc((row*col)*sizeof(int));
    for(i=0;i<row;i++)
        for(k=0;k<col;k++){
            vectorImagne[col*i + k] = m[i][k];
        }

        for(i=0;i<(col*row);i++){
            if(vectorImagne[i]>255){
                frame.data[i] = 255;
            }else{
                frame.data[i] = vectorImagne[i];
            }
        }
   return frame;
}

#endif // IMAGEN

