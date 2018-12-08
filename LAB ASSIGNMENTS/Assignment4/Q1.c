#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#define true 1
#define false 0
#define filepath1 "image.bmp"
#define filepath2 "outImage.bmp"

typedef struct bitmap{
	unsigned int width, height;
	unsigned char *pixels;
};

struct bitmap* bmp;

int main(){
	bmp = NULL;
	FILE *f = fopen(filepath1, "rb");
	//printf("Hello");
	if (f){
		bmp = malloc(sizeof(struct bitmap));
		bmp->width = 0;
		bmp->height = 0;
		bmp->pixels = NULL;
		
		unsigned char info[54] = {0};	//Holds header of BMP file
		fread(info, sizeof(unsigned char), 54, f);
		bmp->width = *(unsigned int *)&info[18];
		bmp->height = *(unsigned int *)&info[22];
		
		unsigned int size = ((((bmp->width * bmp->height) + 31) & ~31) / 8) * bmp->height;	// total size
		bmp->pixels = malloc(size);	

        fread(bmp->pixels, sizeof(unsigned char), size, f);
        fclose(f); //The entire pixel arra - bmp->pixels

        //Code for morphing
        unsigned char *morph;
        morph=malloc(size);
        int cx=(bmp->height)/2;
        int cy=(bmp->width)/2;
        int row,column;
        float theta=3.14;
        for(row=0;row<bmp->width;row++){
        	for(column=0;column<bmp->height;column++){
        		float x=(column-cx)*(cos(theta))+(row-cy)*(sin(theta))+cx;
        		float y=-(row-cy)*(sin(theta))+(row-cy)*(cos(theta))+cy;
        		*(morph+(int)(y*(bmp->height))+(int)x)=*(bmp->pixels+row*(bmp->height)+column);
        	}
        }

        f=fopen(filepath2, "rb");
        if(f){
	        fwrite(info, sizeof(unsigned char), 54, f); // To write header
	        fwrite(morph,sizeof(unsigned char),size,f);
	   	}
	   	else{
	   		printf("READ ERROR HERE\n");
	   	}
        /*for(int i = 0; i < size; i += 3){	// DON'T KNOW WHAT THIS IS FOR
            unsigned char tmp = bmp->pixels[i];
            bmp->pixels[i] = bmp->pixels[i + 2];
            bmp->pixels[i + 2] = tmp;
        }*/
	}
	else
		printf("READ ERROR\n");
}