/*
 * Author:  Arthur Hinds 2013
 * Create a randomly generated binary file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <openssl/rand.h>
#include <math.h>

int characters[256];



void recordChar(unsigned char *buffer){
    int a = *buffer;
    //printf("%i\n", a);
    characters[a]++;


}
void displayChars(){
    int i;
    for (i=0;i<256;i++){
        printf("Ascii[%i]:%i\t\t", i, characters[i]);
        if (i!=0&&i%3==0) printf("\n");
    }

}

void displayStandDev(){
    int i;
    int mean=0;
    //get mean;
    for (i=0;i<256;i++){
        mean += characters[i];
    }
    mean = mean / 256;
    printf("Simple Mean is:%i\n", mean);
    //average these numbers
    int sumsquares=0;
    int temp;
    for (i=0;i<256;i++){
        temp = characters[i] - mean;
        temp = temp*temp;
        
        sumsquares += temp;
    }
    //average of sum of squares
    double deviation = sumsquares/255;
    double dev = sqrt(deviation);
    printf("Standard Deviation: %f\n", dev);

}



int main(int argc, char **argv){

    if (argc < 2) {
        printf("Usage: ./DistributionChecker filename\n");
        return -1;
    }
    
    FILE * fd;
    fd = fopen(argv[1], "rb");

    if (!fd){
        printf("Error Opening File for writing\n");
        return -1;
    }

    unsigned char buffer_char[2];
    int i;

    //Get the filesize in bytes.
    fseek(fd, 0L, SEEK_END);
    unsigned long filesize = ftell(fd);
    fseek(fd, 0L, SEEK_SET);

    for(i=0;i<filesize;i++){
        fread(buffer_char, sizeof(unsigned char), 1, fd);
        recordChar(buffer_char);
    }

    displayChars();
    displayStandDev();
    fclose(fd);
    return 0;

}

