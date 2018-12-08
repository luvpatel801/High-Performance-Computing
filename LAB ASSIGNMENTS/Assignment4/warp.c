#include <stdio.h>
#include <stdlib.h>

FILE* readFile(){
	FILE *fp;
	fp=fopen("download.bmp","r+");
	unsigned char head[54];
	// BMP header is 54 bytes
    fread(head, 1, 54, f);

	return fp;
}
void printFile(FILE *inp){
	FILE *out;
	char ch;
	int fileLen,i;
	out=fopen("out.txt","w");
	//fprintf(out,"Hello\n");
	fseek(inp, 0, SEEK_END);
 	fileLen=ftell(inp);
 	fclose(inp);
 	inp=readFile();
 	for(i=0;i<fileLen;i++){
 		fscanf(inp,"%c",&ch);
 		fprintf(out, "%c", ch);
 	}
	// while(1){
	// 	fscanf(inp,"%c",&ch);
	// 	printf("%c\n",ch );
	// 	if(ch!=-1)
	// 		fprintf(out, "%c", ch);
	// 	else
	// 		break;
	// }
	
}
int main(){
	FILE *fp;
	fp=readFile();
	printFile(fp);
	fclose(fp);
	fp=readFile();
	fprintf(fp, "%d",12 );
}