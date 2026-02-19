#include <stdio.h>
#include <stdlib.h>
#include "file.h"

static int read_int(FILE *f) {
    unsigned char b[4];
    fread(b,1,4,f);
    return (b[0]<<24)|(b[1]<<16)|(b[2]<<8)|b[3];
}

void loadFeatures(const char *filename, float** data, int num) {
    FILE *f=fopen(filename,"rb");
    if(!f){ perror("open image file"); exit(1); }
    int magic=read_int(f);
    int n=read_int(f);
    int rows=read_int(f);
    int cols=read_int(f);
    if(n<num && num!=0) num=n;
    unsigned char *buf=(unsigned char*)malloc(rows*cols);
    for(int i=0;i<num;i++){
        fread(buf,1,rows*cols,f);
        for(int j=0;j<rows*cols;j++)
            data[i][j]=buf[j]/255.0f;
    }
    free(buf);
    fclose(f);
}


void loadLabels(const char *filename, int *labels, int num) {
    FILE *f=fopen(filename,"rb");
    if(!f){ perror("open label file"); exit(1); }
    int magic=read_int(f);
    int n=read_int(f);
    if(n<num && num!=0) num=n;
    unsigned char *buf=(unsigned char*)malloc(n);
    fread(buf,1,n,f);
    for(int i=0;i<num;i++) labels[i]=buf[i];
    free(buf);
    fclose(f);
}



void loadData(const char* featureFile, float** data, const char* labelFile,int* labels,int samples){
	loadFeatures(featureFile,data,samples);
	loadLabels(labelFile,labels,samples);
}
