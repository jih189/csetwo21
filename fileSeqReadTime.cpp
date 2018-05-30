#include <stdio.h>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
unsigned int high, low, id;

static inline uint64_t start_timer(){
    __asm__ volatile ( "cpuid \n\t"
        "rdtsc \n\t"
        "mov %%edx, %0 \n\t"
        "mov %%eax, %1 \n\t"
        : "=r"(high), "=r"(low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
    );
    return ((uint64_t)high << 32)|low;
}

static inline uint64_t end_timer(){
    __asm__ volatile ( 
        "rdtscp \n\t"
        "mov %%edx, %0 \n\t"
        "mov %%eax, %1 \n\t"
        "cpuid \n\t"
        : "=r"(high), "=r"(low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
    );
    return ((uint64_t)high << 32)|low;
}


/**
 the idea of code is
*/ 

int main(int argc, char **argv){

    uint64_t BLOCKSIZE = 3 * 1024 * 1024;

    string filename = "";
    filename += argv[1];
    uint64_t sum = 0;
    FILE * file;
    // open the file 
    file = fopen(filename.c_str(), "r");
    // get file size
    uint64_t filesize;
    fseek(file, 0L, SEEK_END);
    filesize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char * inbuf = (char*) malloc(sizeof(char));
    uint64_t start, end;
    uint64_t step = filesize / BLOCKSIZE;
    cout << "file size " << filesize << endl;
    // put data of file into ram by reading through it 
    if(file != NULL){
        for(int i = 0; i < step; i++){
            fread(inbuf, 1, 1, file);
            fseek(file, BLOCKSIZE - 1, SEEK_CUR);
        }
    }
    // close the file and reopen it
    fclose(file);
    file = fopen(filename.c_str(), "r");
    if(file != NULL){
        for(int i = 0; i < step; i++){
            start = start_timer();
            fread(inbuf, 1, 1, file);
            end = end_timer();
            sum += (end - start);
            fseek(file, BLOCKSIZE - 1, SEEK_CUR);
        }
        cout << "sequential reading time is " << sum / step << endl;
    }
    
    fclose(file);
    free(inbuf);
    return 0;
}
