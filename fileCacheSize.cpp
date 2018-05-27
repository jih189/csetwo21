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

int main(int argc, char **argv){

    string filename = "";
    filename += argv[1];
    uint64_t start, end;
    uint64_t sum = 0;
    FILE * file;
    // open the file 
    file = fopen(filename.c_str(), "r");
    uint64_t blocksize = 4*1024*1024;
    uint64_t filesize;
    // get file size
    fseek(file, 0L, SEEK_END);
    filesize = ftell(file);
    cout << "file size is " << filesize << endl;
    // put data of file into ram by reading through it 
    char * inbuf = (char*) malloc(sizeof(char));
    uint64_t step = filesize / blocksize;
    cout << "step: " << step << endl;
    if(file != NULL){
        for(int i = 0; i < step; i++){
            fread(inbuf, 1, 1, file);
            fseek(file, blocksize, SEEK_CUR);
        }
    }
    // close the file
    fclose(file);
    cout << "reopen file\n";
    // open it again and read it 100 times
    file = fopen(filename.c_str(), "r");
    if(file != NULL){
        for(int i = 0; i < 100; i++){
            start = start_timer();
            fread(inbuf, 1, 1, file);
            end = end_timer();
            sum += end - start;
            // read the file head and tail alternatively 
            if(i % 2 == 0)
                fseek(file, 0, SEEK_END);
            else
                fseek(file, 0, SEEK_SET);
        }
        cout << "reading time is " << sum / 100 << endl;
    }
    return 0;
}
